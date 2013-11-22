from disassembler import *

def sumFirstN(n):
    total = 0
    
    for i in range(1,n+1):
        total = total + i
        
    return total

def main():
    x = int(input("Please enter an integer: "))
    sumTotal = sumFirstN(x)
    print("The sum of 1 to",x,"is",sumTotal)

disassemble(sumFirstN)
disassemble(main)