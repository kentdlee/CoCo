# If 1 2 3 4 is entered, and 5 for the second prompt
# then the answer should be [6, 13, 20, 27]
from disassembler import *

def main():
    def g(aVal):
        def f():
            result = []
            count = 0
            
            for x in lstInts:
                result.append(x + aVal * count + fVal)
                count = count + 1
                
            return result
        
        fVal = int(input("Please enter another integer: "))

        return f
    
    x = input("Please enter a list of integers: ")
    lst = x.split()
    
    lstInts = []
    for y in lst:
        lstInts.append(int(y))
        
    fVal = 0
    
    myFun = g(6)
    
    print(myFun())

disassemble(main)
#main()       
