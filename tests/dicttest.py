import disassembler

def main():
	d = {}
	d["hello"] = "goodbye"
	d["dog!"] = "cat!"
	d["young"] = "old"

	s = "hello young dog!"
	t = s.split()
	for x in t:
		print(x)

	for x in t:
		print(d[x])

	for x in d.keys():
		print(x, d[x])

	for y in d.values():
		print(y)

	print(type(d))
	print(type(type(d)))

main()
#disassembler.disassemble(main)