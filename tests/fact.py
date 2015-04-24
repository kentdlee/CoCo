import disassembler

def factorial(n):
    if n==0:
        return 1
    
    return n*factorial(n-1)

def main():
	print(factorial(5))

#main()
disassembler.disassemble(factorial)
disassembler.disassemble(main)