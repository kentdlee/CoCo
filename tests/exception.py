import disassembler

def main():
	try:
		x = float(input("Enter a number: "))
		y = float(input("Enter a number: "))
		z = x / y

		print(x,"/",y,"=",z)
	except Exception as ex:
		print(ex)

#main()
disassembler.disassemble(main)
