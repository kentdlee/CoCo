import disassembler

def funA(x,y):
    z = 0
    while x < y:
        z = z + x
        print(x,y,z)
        x = x + 1
        
    return z

def main():
    x = int(input("Please enter an integer: "))
    y = int(input("Please enter an integer: "))
    
    z = funA(x,y)
    print("The answer is",z)
    
 
def callit():    
    if __name__ == "__main__":
        main()

#callit()

disassembler.disassemble(funA)
disassembler.disassemble(main)
