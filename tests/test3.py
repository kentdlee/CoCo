import disassembler

def main():
    def f(x):
        
        return x + 1
    
    def g(y):
        z = f(y)
        
        return z
    
    print(g(g(6)))
    
#main()

disassembler.disassemble(main)