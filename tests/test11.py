import disassembler

def main():
    def anon_f0(x):
        return x + 1
    
    anon_f0(6)

 
#main()   
disassembler.disassemble(main)