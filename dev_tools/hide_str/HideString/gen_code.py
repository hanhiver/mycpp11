import sys

if len(sys.argv) != 2:
    print("Usage: ", sys.argv[0], " <input_file>")
    exit(-1)

input_file_name = sys.argv[1]
output_file_name = input_file_name.rsplit('.', maxsplit = 1)[0]

with open(input_file_name, 'r') as input_file:
    str_list = input_file.readlines()


gen_code = ""
for str in str_list:
    for char in str.rstrip('\n'):
        gen_code += "('" + char + "')"
    gen_code += "('\\n')"

output_str = "DEFINE_ESTRING({}, 0x1e, {})\n\n".format(output_file_name, gen_code)

with open(output_file_name + '.h', 'w') as output_file:
    output_file.write('#include "estring.h"\n')
    output_file.write(output_str)

print(output_str)