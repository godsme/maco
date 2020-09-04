import sys

head = '''
#ifndef __MACO_REPEAT_0_H__
#define __MACO_REPEAT_0_H__

#include <maco/basic.h>

'''

tail = '''

#endif
'''

def gen_repeat_macro(n):
    macro = ""
    for i in range(n):
        macro = macro + "#define __MACO_repeat_0_{}(macro, g, ud)".format(i)
        if i > 0:
            macro = macro + " __MACO_repeat_0_{}(macro, g, ud)".format(i - 1)
        if i > 1:
            macro = macro + " __MACO_compose(macro, g, ud, {})".format(i - 2)
        macro = macro + "\n"

    return macro

def gen_end_macro(n):
    macro = ""
    for i in range(n):
        macro = macro + "#define __MACO_end_macro_0_{}(macro, g, ud)".format(i)
        if i > 0:
            macro = macro + " __MACO_compose(macro, g, ud, {})".format(i - 1)
        macro = macro + "\n"

    return macro

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1]) + 1
    lines = head + gen_repeat_macro(n) + "\n" + gen_end_macro(n) + tail

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()
