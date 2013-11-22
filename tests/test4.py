import disassembler

def g(aVal):
    def inc():
        x[0] = x[0] + 1
        
    x = [aVal]
    
    inc()
    return x[0]
    
def main():
    y = g(6)
    print(y)
    
#main()

disassembler.disassemble(g)
disassembler.disassemble(main)

        
    