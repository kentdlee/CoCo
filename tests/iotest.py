import disassembler

def main():

	name = input("Enter your name: ")
	age = int(input("Enter your age: "))
	print(name + ", a year from now you will be", age+1, "years old.")

#main()

disassembler.disassemble(main)