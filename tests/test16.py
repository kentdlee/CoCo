import disassembler

def main():
    def reverse(L):
        if L == []:
            return []
        elif len(L) > 0:
            h = L[0]
            t = L[1:]
            return reverse(t) + [h]
        else:
            raise Exception("Match Exception")
    

    print(reverse([1,2,3,4]))
    
#main()

disassembler.disassemble(main)