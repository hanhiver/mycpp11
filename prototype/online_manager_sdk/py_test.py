import time
import ctypes

so = ctypes.cdll.LoadLibrary
lib = so('./build/lib/sdk_manager_py.so')

config_file = ctypes.c_char_p(bytes('./test.config', 'utf-8'))
lib.SDKM_Init(config_file)

func_name = ctypes.c_char_p(bytes('python_test3', 'utf-8'))

lib.SDKM_Auth.restype = ctypes.c_bool
res = Auth_FUNC()
res = lib.SDKM_Auth()
print("RES: ", type(res), res)


for i in range(10):
    if lib.SDKM_Auth():
        lib.SDKM_Count(func_name, 1)
        time.sleep(0.03)
    else:
        print("AUTH ERROR!")

lib.SDKM_Shutdown()
print('PYTHON TEST DONE!')
