# pkcs1公钥
#-----BEGIN RSA PUBLIC KEY-----
#-----END RSA PUBLIC KEY-----
# pkcs1私钥
#-----BEGIN RSA PRIVATE KEY-----
#-----END RSA PRIVATE KEY-----

# pkcs8公钥
#-----BEGIN PUBLIC KEY-----
#-----END PUBLIC KEY-----
# pkcs8私钥
#-----BEGIN PRIVATE KEY-----
#-----END PRIVATE KEY-----

# 生成1024位的私钥pkcs1
openssl genrsa -out pri.pem 1024

# 从私钥生成公钥pkcs1
openssl rsa -in pri.pem -pubout -out pub.pem

# 使用pkcs8对私钥进行编码
openssl pkcs8 -topk8 -inform PEM -in pri.pem -outform pem -nocrypt -out ppri.pem

#openssl rsa -RSAPublicKey_in -in pub.pem -pubout -out ppub.pem

# 使用pkcs8私钥生成pkcs8的公钥
openssl rsa -in ppri.pem -pubout -out ppub.pem

