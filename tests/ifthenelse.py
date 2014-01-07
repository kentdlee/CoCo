import disassembler

def main():
	x = 5
	y = 6
	if x > y:
		z = x
	else:
		z = y

	print(z)

#main()

disassembler.disassemble(main)