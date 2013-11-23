import disassembler

def main():
    x = 5
    y = 4

    if x > y:
      z = x
    else:
      z = y

    print(z)


disassembler.disassemble(main)
