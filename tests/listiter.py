from disassembler import *

def main():
    x = input("Enter a list: ")
    lst = x.split()
    
    for b in lst:
        print(b)
        
disassemble(main)