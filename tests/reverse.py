import disassembler

def reverse(lst):
	if len(lst) == 0:
		return []

	return reverse(lst[1:])+[lst[0]]

def main():

	print(reverse([1,2,3]))

#main()
disassembler.disassemble(reverse)
disassembler.disassemble(main)