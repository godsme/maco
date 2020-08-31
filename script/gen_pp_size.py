import sys

head = '''
#ifndef __MACO_PP_SIZE_H__
#define __MACO_PP_SIZE_H__

#include <maco/basic.h>

#ifdef _MSC_VER

#define __MACO_pp_size_(...)  \\
   __MACO_paste(__MACO_pp_size_i(__VA_ARGS__, \\
'''

middle = ''', __MACO_empty())

#else

#define __MACO_pp_size_(...)     \\
   __MACO_pp_size_i(__VA_ARGS__, \\
'''

end = '''

#endif

#define __MACO_pp_size(...) __MACO_pp_size_(__dummy__, ##__VA_ARGS__)
#define __MACO_pp_size_i( \\
'''

final = '''
   size
   
#endif 
'''

def gen_seq(n):
    seq = ""
    m = 0
    for i in reversed(range(n)):
        seq = seq + "{}, ".format(i)
        m = m+1
        if m % 10 == 0:
            seq = seq + "\\\n      "

    return "      " + seq + ")"


def gen_var_seq(n):
    seq = ""
    m = 0
    for i in range(n):
        seq = seq + "e{}, ".format(i)
        m = m+1
        if m % 10 == 0:
            seq = seq + "\\\n      "

    return "      " + seq + "size, ...) \\"

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1])
    lines = head
    lines = lines + gen_seq(n) + middle + gen_seq(n) + end + gen_var_seq(n) + final
    print(lines)

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()