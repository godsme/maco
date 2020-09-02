import sys

head = '''
#ifndef __MACO_INT_PREV_H__
#define __MACO_INT_PREV_H__

#include <maco/basic.h>

'''

end = '''
#define __MACO_prev(n)  __MACO_concat(__MACO_prev_, n)

#endif
'''

def gen_seq(n):
    seq = ""
    for i in range(n):
        seq = seq + "#define __MACO_prev_{} ".format(i+1) + "  {}\n".format(i)

    return seq

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1])
    lines = head + gen_seq(n) + end
    print(lines)

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()