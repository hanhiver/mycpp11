# 字符串隐藏预处理程序
# 请搭配配套的estring.h一块用
# 如果需要加密的文本文件是abc.txt
# 运行python gen_code.py abc.txt会自动生成abc.h
# 在代码中#include "abc.h"
# 程序中通过GetEstring_abc()函数就能够获取到文本中的字符串。
# 注意，文本中所有的空行，每一行前后所有的前后空白字符空行非打印字符都会被去除。不支持转义字符。
import sys

SEC_CODE = "0x1e"

if len(sys.argv) < 2:
    print("Usage: ", sys.argv[0], " <input_file>")
    exit(-1)

for input_file_name in sys.argv[1:]:
    print("Generate estring head file from: ", input_file_name)
    output_file_name = input_file_name.rsplit('.', maxsplit = 1)[0]

    with open(input_file_name, 'r') as input_file:
        str_list = input_file.readlines()

    output_str = ""
    gen_code = ""
    line_index = 0

    for str_item in str_list:
        # 去除字符串前后的空格换行等
        str_effective = str_item.strip()
        # 如果是空行，则跳过。
        if len(str_effective) == 0:
            continue

        for char in str_effective:
            if char == '\\':
                gen_code += "('\\\\')"
            else:
                gen_code += "('" + char + "')"
        gen_code += "('\\n')"

        output_str += "DEFINE_ESTRING({}, {}, {})\n".format(output_file_name + str(line_index), SEC_CODE, gen_code)
        gen_code = ""
        line_index += 1

    output_str += "#define {} {}\n".format(output_file_name + "_length", str(line_index))
    output_str += 'std::string GetEstring_{}()\n'.format(output_file_name)
    output_str += '{\n\tstd::string pub_str = "";\n'
    for index in range(line_index):
        output_str += '\tpub_str += std::string(GetEstring_{}());\n'.format(output_file_name + str(index))

    output_str += '\treturn pub_str;\n}\n'

    with open(output_file_name + '.h', 'w') as output_file:
        output_file.write('#include <string>\n')
        output_file.write('#include "estring.h"\n')
        output_file.write(output_str)

    #print(output_str, '\n\n\n')
