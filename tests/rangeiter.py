from disassembler import *

def main():
    x = input("Enter a list: ")
    lst = x.split()
       
    for i in range(len(lst)-1,-1,-1):
        print(lst[i])
        
disassemble(main)