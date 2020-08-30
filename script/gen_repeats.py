import sys

def gen_repeat_macro(n):
    all_macros = []
    for i in range(n):
        macro = "#define __MACO_repeat_{}(macro)".format(i)
        if i > 0:
            macro = macro + " __MACO_repeat_{}(macro)".format(i - 1)
        if i > 1:
            macro = macro + " macro({})".format(i - 2)

        all_macros.append(macro + '\n')

    return all_macros

def gen_end_macro(n):
    all_macros = []
    for i in range(n):
        macro = "#define __MACO_end_macro_{}(macro)".format(i)
        if i > 0:
            macro = macro + " macro({})".format(i - 1)

        all_macros.append(macro + '\n')

    return all_macros

def gen_repeat_macro_1(n):
    all_macros = []
    for i in range(n):
        macro = "#define __MACO_repeat__{}(macro)".format(i)
        if i > 0:
            macro = macro + " __MACO_repeat__{}(macro)".format(i - 1)
        if i > 1:
            macro = macro + " macro({})".format(i - 1)

        all_macros.append(macro + '\n')

    return all_macros

def gen_end_macro_1(n):
    all_macros = []
    for i in range(n):
        macro = "#define __MACO_end_macro__{}(macro)".format(i)
        if i > 0:
            macro = macro + " macro({})".format(i)

        all_macros.append(macro + '\n')

    return all_macros

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1]) + 1
    lines = []
    lines.append("#ifndef __MACO_REPEAT_MACRO_DEF_H__\n")
    lines.append("#define __MACO_REPEAT_MACRO_DEF_H__\n")
    lines.append("\n")

    lines = lines + gen_repeat_macro(n)
    lines.append("\n")
    lines = lines + gen_end_macro(n)

    lines.append("\n#define __MACO_repeat(n, macro, end_macro) __MACO_repeat_##n (macro) __MACO_end_macro_##n(end_macro)\n")
    lines.append("#define __MACO_simple_repeat(n, macro) __MACO_repeat(n, macro, macro)\n")
    lines.append("\n")

    lines = lines + gen_repeat_macro_1(n)
    lines.append("\n")
    lines = lines + gen_end_macro_1(n)

    lines.append("\n#define __MACO_repeat_(n, macro, end_macro) __MACO_repeat__##n (macro) __MACO_end_macro__##n(end_macro)\n")
    lines.append("#define __MACO_simple_repeat_(n, macro) __MACO_repeat_(n, macro, macro)\n")
    lines.append("\n")

    lines.append("#endif")

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()
