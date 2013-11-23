import disassembler

def main():
    def f(x):
        def g(y):
            return x + y
        return g
    print (f(5)(4))
    
disassembler.disassemble(main)

    