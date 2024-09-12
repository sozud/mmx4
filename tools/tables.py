import re

test = '''
glabel D_800F1640
/* E1E40 800F1640 E4480180 */ .word func_800148E4
/* E1E44 800F1644 EC480180 */ .word func_800148EC
/* E1E48 800F1648 68490180 */ .word func_80014968
.size D_800F1640, . - D_800F1640
'''

def parse_lines(lines):
    glabel_pattern = re.compile(r'glabel\s+(\w+)')
    word_func_pattern = re.compile(r'\.word\s+func_(\w+)')
    
    glabel_name = None

    funcs = []

    out_lines = []


    for line in lines:
        glabel_match = glabel_pattern.match(line)
        word_func_match = word_func_pattern.search(line)

        if glabel_match:
            # Start of a new glabel section
            glabel_name = glabel_match.group(1)
        elif word_func_match:
            func_name = word_func_match.group(0)[6:]
            funcs.append(func_name)
        elif '.size' in line:

            if len(funcs):
                # done
                out_lines.append(f"// {glabel_name}\n")
                for func in funcs:
                    out_lines.append(f"void {func}(void);\n")

                out_lines.append("\n")

                funcs = []

    return out_lines

result = parse_lines(test.split('\n'))
print(result)
def parse_file(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        lines = infile.readlines()
        result = parse_lines(lines)
        for r in result:
            outfile.write(r)


parse_file('asm/us/main/data/DEC0C.data.s', 'funcs.txt')