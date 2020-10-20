import time

# === 1. 添加必要的库 === #
# ctypes是调用.so文件的基本库。
import ctypes


# === 2. 读取指定的.so文件 === #
# 设置so表示读取linux下的.so格式文件方法。
so = ctypes.cdll.LoadLibrary
# 根据文件目录读取相应的.so文件
lib = so('./build/lib/sdk_manager_py.so')


# === 3. 指定配置文件初始化 === #
# 如果函数需要传入字符串，则需要先构建一个ctypes的字符串对象。
# 此处因为是python3，所以对应的字符串是utf-8结构。
config_file = ctypes.c_char_p(bytes('./test.config', 'utf-8'))
# 调用库函数SDKM_Init来完成初始化。
lib.SDKM_Init(config_file)


# === 4. 检查当前是否有合法鉴权 === #
# 设置Auth函数返回格式为bool值。
lib.SDKM_Auth.restype = ctypes.c_bool
# 判断目前是否拥有合法鉴权。res为true表示有，false表示没有。
res = lib.SDKM_Auth()


# === 5. 汇报对应的函数调用量 === #
# 设置函数名称字符串
func_name = ctypes.c_char_p(bytes('python_test3', 'utf-8'))
# 调用函数，汇报相应的调用量。此处为0次调用。
lib.SDKM_Count(func_name, 0)


# 一个小测试循环
for i in range(1000):
    # 调用函数判断现在是否拥有鉴权。
    if lib.SDKM_Auth():
        # 调用函数，汇报相应的调用量。
        lib.SDKM_Count(func_name, 1)
        time.sleep(0.01)
    else:
        print("AUTH ERROR!")


# === 5. 结束鉴权模块运行 === #
# 结束函数库调用。
lib.SDKM_Shutdown()

print('PYTHON TEST DONE!')
