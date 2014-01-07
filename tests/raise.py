import disassembler

def main():
    try:
        raise Exception("Hello World!")
    except Exception as ex:
        print(ex)

#main()
disassembler.disassemble(main)
