import sys

head = '''
#ifndef __MACO_INTERNAL_EVAL__
#define __MACO_INTERNAL_EVAL__

#define __MACO_eval_0(...) 
#define __MACO_eval_1(...) __VA_ARGS__
'''

end = '''

#endif
'''

def gen_eval(n):
    seq = ""
    for i in range(n):
        seq = seq + "#define __MACO_eval_{}(...)   __MACO_eval_{}(__VA_ARGS__)\n".format(i+2, i+1)

    return seq

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1])
    lines = head + gen_eval(n) + end
    print(lines)

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()