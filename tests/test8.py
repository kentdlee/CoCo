import disassembler

def main():
    def f(x):
        return x + 1
    
    print(f(2))
    
disassembler.disassemble(main)
    
