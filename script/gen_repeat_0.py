import sys

head = '''
#ifndef __MACO_REPEAT_0_H__
#define __MACO_REPEAT_0_H__


'''

tail = '''
#define __MACO_repeat_from_0(n, macro, end_macro) __MACO_repeat_0_##n (macro) __MACO_end_macro_0_##n(end_macro)
#define __MACO_simple_repeat_from_0(n, macro) __MACO_repeat_from_0(n, macro, macro)

#endif
'''

def gen_repeat_macro(n):
    macro = ""
    for i in range(n):
        macro = macro + "#define __MACO_repeat_0_{}(macro)".format(i)
        if i > 0:
            macro = macro + " __MACO_repeat_0_{}(macro)".format(i - 1)
        if i > 1:
            macro = macro + " macro({})".format(i - 2)
        macro = macro + "\n"

    return macro

def gen_end_macro(n):
    macro = ""
    for i in range(n):
        macro = macro + "#define __MACO_end_macro_0_{}(macro)".format(i)
        if i > 0:
            macro = macro + " macro({})".format(i - 1)
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
