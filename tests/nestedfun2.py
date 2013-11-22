# If 1 2 3 4 is entered, and 5 for the second prompt
# then the answer should be [6, 13, 20, 27]
from disassembler import *

def main():
    def g(aVal):
        def f(x):
            return aVal + lstInts[0] + x

        return f
    
    x = input("Please enter a list of integers: ")
    lst = x.split()
    
    lstInts = []
    for y in lst:
        lstInts.append(int(y))
    
    myFun = g(6)
    
    print(myFun(lstInts[2]))

#main()
disassemble(main)
        