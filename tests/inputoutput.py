import disassembler

def main():
	x = int(input("Please enter an integer: "))
	y = float(input("Please enter a number: "))
	print("The product is", x*y)

#main()

disassembler.disassemble(main)