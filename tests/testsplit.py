import disassembler

def main():

  x = input("Please enter a string: ")
  for a in x.split():
    print(a)

disassembler.disassemble(main) 
