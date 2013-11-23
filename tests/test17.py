import disassembler

def main():
    print((lambda x: x**2)(6))

disassembler.disassemble(main)
