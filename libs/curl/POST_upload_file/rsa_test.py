import Crypto.PublicKey.RSA
import Crypto.Cipher.PKCS1_v1_5
import Crypto.Random
import Crypto.Signature.PKCS1_v1_5
import Crypto.Hash
import json
import base64
import hashlib


src = '''{"cipherText":"DPqP+B3ZucFKpGVd2XBbTu5CQ87N9z+pVeAEKfuaegajFZrZi+0pZE6oAM9+hAZAyefBf234Afptc2+vk0KqGN7MAfF1uLYs7EVEOZZWzMee4HjslU4gkFSOk6b5cqKmL/fPotdI0FsWdsxSfOdJOSke/EIjWeTwjs/b+sloH+Q=","curTime":1602594905,"funcNameList":[{"callCount":11,"funcName":"Func2"},{"callCount":3,"funcName":"Func1"}],"keyInfo":{"keyIndex":"1234-5678-abcd","keyType":"RSA"},"vendorName":"miaoxiu","version":1}'''
print(src)

request = json.loads(src)
_ = request.pop('cipherText')
orig_report = json.JSONEncoder(separators=(',', ':')).encode(request)
print(orig_report)

hash = hashlib.sha384()
hash.update(orig_report.encode('utf-8'))
hash_report = hash.hexdigest()
print(hash_report)

with open("/tmp/pubkey.pem", "rb") as x:
    b = x.read()
    cipher_public = Crypto.Cipher.PKCS1_v1_5.new(Crypto.PublicKey.RSA.importKey(b))
    cipher_text = cipher_public.encrypt(hash_report.encode('utf-8')) # 使用公钥进行加密
    cipherText = base64.b64encode(cipher_text)
    print(cipherText)

"""
with open("a.pem", "rb") as x:
    a = x.read()
    # 如果私钥有密码 则使用相应密码 Crypto.PublicKey.RSA.importKey(a, password)
    cipher_private = Crypto.Cipher.PKCS1_v1_5.new(Crypto.PublicKey.RSA.importKey(a))
    text = cipher_private.decrypt(cipher_text, Crypto.Random.new().read)    # 使用私钥进行解密
assert text == y    # 断言验证
 
with open("c.pem", "rb") as x:
    c = x.read()
    c_rsa = Crypto.PublicKey.RSA.importKey(c)
    signer = Crypto.Signature.PKCS1_v1_5.new(c_rsa)
    msg_hash = Crypto.Hash.SHA256.new()
    msg_hash.update(y)
    sign = signer.sign(msg_hash)    # 使用私钥进行'sha256'签名
with open("d.pem", "rb") as x:
    d = x.read()
    d_rsa = Crypto.PublicKey.RSA.importKey(d)
    verifer = Crypto.Signature.PKCS1_v1_5.new(d_rsa)
    msg_hash = Crypto.Hash.SHA256.new()
    msg_hash.update(y)
    verify = verifer.verify(msg_hash, sign) # 使用公钥验证签名
    print(verify)
"""