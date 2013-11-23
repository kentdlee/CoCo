import disassembler

def main():
    zero = 0
    
    def fib(n):
        i = zero
        current = 0
        next = 1
        
        while i < n:
            tmp = next + current
            current = next
            next = tmp
            i=i+1
            
        return current
        
        
    x = int(input("Please enter an integer: "))
    
    r = fib(x)
    
    print("Fib("+str(x)+") is", r)
    
#main()
disassembler.disassemble(main)