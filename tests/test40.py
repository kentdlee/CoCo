import disassembler

def main():

    s = input("Please enter some words:")
    lst = s.split()
    for i in range(len(lst)//2):
        tmp = lst[i]
        lst[i] = lst[len(lst)-i-1]
        lst[len(lst)-i-1] = tmp

    print(lst)

#main()
disassembler.disassemble(main)
