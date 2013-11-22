from disassembler import *

def factorial(n):
    if n==0:
        return 1
    
    return n*factorial(n-1)

def main():
    print(type(factorial))
    
disassemble(factorial)
disassemble(main)
