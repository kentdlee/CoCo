import disassembler

def main():
    try:

        raise Exception("hi there")

    except Exception as ex:
        print(ex)

#main()
disassembler.disassemble(main)
