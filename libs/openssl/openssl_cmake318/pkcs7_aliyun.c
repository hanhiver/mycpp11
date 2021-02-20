
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>

const char certificate[] = "\
-----BEGIN CERTIFICATE----- \n\
MIIDdzCCAl+gAwIBAgIEZmbRhzANBgkqhkiG9w0BAQsFADBsMRAwDgYDVQQGEwdV \n\
bmtub3duMRAwDgYDVQQIEwdVbmtub3duMRAwDgYDVQQHEwdVbmtub3duMRAwDgYD \n\
VQQKEwdVbmtub3duMRAwDgYDVQQLEwdVbmtub3duMRAwDgYDVQQDEwdVbmtub3du \n\
MB4XDTE4MDIyMzAxMjkzOFoXDTM4MDIxODAxMjkzOFowbDEQMA4GA1UEBhMHVW5r \n\
bm93bjEQMA4GA1UECBMHVW5rbm93bjEQMA4GA1UEBxMHVW5rbm93bjEQMA4GA1UE \n\
ChMHVW5rbm93bjEQMA4GA1UECxMHVW5rbm93bjEQMA4GA1UEAxMHVW5rbm93bjCC \n\
ASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAIJwy5sbZDiNyX4mvdP32pqM \n\
YMK4k7+5lRnVR2Fky/5uwyGSPbddNXaXzwEm+u4wIsJiaAN3OZgJpYIoCGik+9lG \n\
5gVAIr0+/3rZ61IbeVE+vDenDd8g/m/YIdYBfC2IbzgS9EVGAf/gJdtDODXrDfQj \n\
Fk2rQsvpftVOUs3Vpl9O+jeCQLoRbZYm0c5v7jP/L2lK0MjhiywPF2kpDeisMtnD \n\
/ArkSPIlg1qVYm3F19v3pa6ZioM2hnwXg5DibYlgVvsIBGhvYqdQ1KosNVcVGGQa \n\
HCUuVGdS7vHJYp3byH0vQYYygzxUJT2TqvK7pD57eYMN5drc7e19oyRQvbPQ3kkC \n\
AwEAAaMhMB8wHQYDVR0OBBYEFAwwrnHlRgFvPGo+UD5zS1xAkC91MA0GCSqGSIb3 \n\
DQEBCwUAA4IBAQBBLhDRgezd/OOppuYEVNB9+XiJ9dNmcuHUhjNTnjiKQWVk/YDA \n\
v+T2V3t9yl8L8o61tRIVKQ++lDhjlVmur/mbBN25/UNRpJllfpUH6oOaqvQAze4a \n\
nRgyTnBwVBZkdJ0d1sivL9NZ4pKelJF3Ylw6rp0YMqV+cwkt/vRtzRJ31ZEeBhs7 \n\
vKh7F6BiGCHL5ZAwEUYe8O3akQwjgrMUcfuiFs4/sAeDMnmgN6Uq8DFEBXDpAxVN \n\
sV/6Hockdfinx85RV2AUwJGfClcVcu4hMhOvKROpcH27xu9bBIeMuY0vvzP2VyOm \n\
DoJeqU7qZjyCaUBkPimsz/1eRod6d4P5qxTj \n\
-----END CERTIFICATE----- \n\
";

const char message[] = "{\"zone-id\":\"cn-zhangjiakou-c\",\"serial-number\":\"4453b924-c169-45a7-9478-0dcdd94628b3\",\"instance-id\":\"i-8vb9b97xf7msxi4k6tgx\",\"region-id\":\"cn-zhangjiakou\",\"private-ipv4\":\"11.160.137.194\",\"owner-account-id\":\"1900050632443592\",\"mac\":\"00:16:3e:0b:5c:f8\",\"image-id\":\"m-8vbipaljoi4ep0rcxght\",\"instance-type\":\"ecs.gn6v-c8g1.8xlarge\",\"audience\":\"abc\"}";
 
static int
x509_store_callback(int ok, X509_STORE_CTX *ctx)
{
	/* Pretend the certificate issuer is valid... */
	return 1;
}
 
static void
fatal(const char *msg)
{
	warnx("%s", msg);
	ERR_print_errors(BIO_new_fd(STDERR_FILENO, 0));
	exit(1);
}
 
static void
message_compare(const char *out, size_t len)
{
	if (len != sizeof(message)) {
		fprintf(stderr, "FAILURE: length mismatch (%zu != %zu)\n",
		    len, sizeof(message));
		exit(1);
	}
	if (memcmp(out, message, len) != 0) {
		fprintf(stderr, "FAILURE: message mismatch\n");
		fprintf(stderr, "Got:\n%s\n", out);
		fprintf(stderr, "Want:\n%s\n", message);
		exit(1);
	}
}
 
int
main(int argc, char **argv)
{
	BIO *bio_in, *bio_content, *bio_out, *bio_cert, *bio_pkey;
	STACK_OF(X509) *certs;
	const EVP_CIPHER *cipher;
	EVP_PKEY *pkey;
	X509_STORE *store;
	X509 *cert;
	PKCS7 *p7;
	size_t len;
	char *out;
	int flags;
 
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
 
	/*
	 * A bunch of setup...
	 */
	cipher = EVP_aes_256_cbc();
	if (cipher == NULL)
		fatal("cipher");
 
	certs = sk_X509_new_null();
	if (certs == NULL)
		fatal("sk_X509_new_null");
 
	bio_cert = BIO_new_mem_buf((char *)certificate, sizeof(certificate));
	if (bio_cert == NULL)
		fatal("BIO_new_mem_buf certificate");
 
	cert = PEM_read_bio_X509_AUX(bio_cert, NULL, NULL, NULL);
	if (cert == NULL)
		fatal("PEM_read_bio_X509_AUX");
	sk_X509_push(certs, cert);
 
	store = X509_STORE_new();
	if (store == NULL)
		fatal("X509_STORE_new");
	X509_STORE_set_verify_cb(store, x509_store_callback);
 
	bio_pkey = BIO_new_mem_buf((char *)private_key, sizeof(private_key));
	if (bio_pkey == NULL)
		fatal("BIO_new_mem_buf private_key");
 
	pkey = PEM_read_bio_PrivateKey(bio_pkey, NULL, NULL, NULL);
	if (pkey == NULL)
		fatal("PEM_read_bio_PrivateKey");
 
	bio_content = BIO_new_mem_buf((char *)message, sizeof(message));
	if (bio_content == NULL)
		fatal("BIO_new_mem_buf message");
 
	/*
	 * Encrypt and then decrypt.
	 */
	if (BIO_reset(bio_content) != 1)
		fatal("BIO_reset");
	bio_out = BIO_new(BIO_s_mem());
	if (bio_out == NULL)
		fatal("BIO_new");
 
	p7 = PKCS7_encrypt(certs, bio_content, cipher, 0);
	if (p7 == NULL)
		fatal("PKCS7_encrypt");
	if (PEM_write_bio_PKCS7(bio_out, p7) != 1)
		fatal("PEM_write_bio_PKCS7");
	PKCS7_free(p7);
 
	bio_in = bio_out;
	bio_out = BIO_new(BIO_s_mem());
	if (bio_out == NULL)
		fatal("BIO_new");
 
	p7 = PEM_read_bio_PKCS7(bio_in, NULL, NULL, NULL);
	if (p7 == NULL)
		fatal("PEM_read_bio_PKCS7");
	if (PKCS7_decrypt(p7, pkey, cert, bio_out, 0) != 1)
		fatal("PKCS7_decrypt");
 
	len = BIO_get_mem_data(bio_out, &out);
	message_compare(out, len);
 
	BIO_free(bio_out);
 
	/*
	 * Sign and then verify.
	 */
	if (BIO_reset(bio_content) != 1)
		fatal("BIO_reset");
	bio_out = BIO_new(BIO_s_mem());
	if (bio_out == NULL)
		fatal("BIO_new");
 
	p7 = PKCS7_sign(cert, pkey, certs, bio_content, 0);
	if (p7 == NULL)
		fatal("PKCS7_sign");
	if (PEM_write_bio_PKCS7(bio_out, p7) != 1)
		fatal("PEM_write_bio_PKCS7");
	PKCS7_free(p7);
 
	bio_in = bio_out;
	bio_out = BIO_new(BIO_s_mem());
	if (bio_out == NULL)
		fatal("BIO_new");
 
	p7 = PEM_read_bio_PKCS7(bio_in, NULL, NULL, NULL);
	if (p7 == NULL)
		fatal("PEM_read_bio_PKCS7");
	if (PKCS7_verify(p7, certs, store, NULL, bio_out, 0) != 1)
		fatal("PKCS7_verify");
 
	len = BIO_get_mem_data(bio_out, &out);
	message_compare(out, len);
 
	BIO_free(bio_in);
	BIO_free(bio_out);
 
	/*
	 * Sign and then verify with a detached signature.
	 */
	if (BIO_reset(bio_content) != 1)
		fatal("BIO_reset");
	bio_out = BIO_new(BIO_s_mem());
	if (bio_out == NULL)
		fatal("BIO_new");
 
	flags = PKCS7_DETACHED|PKCS7_PARTIAL;
	p7 = PKCS7_sign(NULL, NULL, NULL, bio_content, flags);
	if (p7 == NULL)
		fatal("PKCS7_sign");
	if (PKCS7_sign_add_signer(p7, cert, pkey, NULL, flags) == NULL)
		fatal("PKCS7_sign_add_signer");
	if (PKCS7_final(p7, bio_content, flags) != 1)
		fatal("PKCS7_final");
	if (PEM_write_bio_PKCS7(bio_out, p7) != 1)
		fatal("PEM_write_bio_PKCS7");
	PKCS7_free(p7);
 
	/* bio_out contains only the detached signature. */
	bio_in = bio_out;
	if (BIO_reset(bio_content) != 1)
		fatal("BIO_reset");
 
	bio_out = BIO_new(BIO_s_mem());
	if (bio_out == NULL)
		fatal("BIO_new");
 
	p7 = PEM_read_bio_PKCS7(bio_in, NULL, NULL, NULL);
	if (p7 == NULL)
		fatal("PEM_read_bio_PKCS7");
	if (PKCS7_verify(p7, certs, store, bio_content, bio_out, flags) != 1)
		fatal("PKCS7_verify");
 
	len = BIO_get_mem_data(bio_out, &out);
	message_compare(out, len);
 
	BIO_free(bio_in);
	BIO_free(bio_out);
	BIO_free(bio_content);
 
	return 0;
}
