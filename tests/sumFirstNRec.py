
from disassembler import *

def sumFirstN(n):
    if n == 0:
    	return 0

    return n + sumFirstN(n-1)

def main():
    x = int(input("Please enter an integer: "))
    sumTotal = sumFirstN(x)
    print("The sum of 1 to",x,"is",sumTotal)

disassemble(sumFirstN)
disassemble(main)