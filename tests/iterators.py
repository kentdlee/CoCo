from disassembler import *

def main():
    x = input("Please enter a list of integers separated by spaces: ")
    lst = x.split()
    
    print("Here are the characters in the string.")
    
    for a in x:
        print(a)
        
    print("Here are the elements of the list after splitting the string.")
    for b in lst:
        print(int(b))
        
    print("Here are the elements of the list using indexing.")
    
    for c in range(len(lst)):
        print(lst[c])
        
    print("Here are the elements backwards using indexing.")
        
    for c in range(len(lst)-1,-1,-1):
        print(lst[c])
        
    product = 1
    sum = 0
    
    for b in lst:
        product = product * int(b)
        sum = sum + int(b)
        
    print("The sum of the integers is", sum, "and the product is", product)
        
disassemble(main)