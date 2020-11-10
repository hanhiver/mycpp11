# === 1. 添加必要的库 === #
# ctypes是调用.so文件的基本库。
import ctypes

# === 2. 读取指定的.so文件 === #
# 设置so表示读取linux下的.so格式文件方法。
so = ctypes.cdll.LoadLibrary
# 根据文件目录读取相应的.so文件
lib = so('./build/lib/bind_host_py.so')


# === 3. 指定配置文件校验绑定机器 === #
# 如果函数需要传入字符串，则需要先构建一个ctypes的字符串对象。
# 此处因为是python3，所以对应的字符串是utf-8结构。
key_file = ctypes.c_char_p(bytes('./key.conf', 'utf-8'))
# 调用函数校验绑定机器，成功表示运行机器为绑定机器，失败则表示绑定机器不是本机或者秘钥错误。
ret = lib.CheckBindHost(key_file)

if ret:
    print("SUCCESS! ")
else:
    print("FAILED! ")

print('PYTHON TEST DONE!')
