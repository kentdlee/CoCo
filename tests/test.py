def f(x):
    def g(y):
        x = x + 1
        return x + y

    return g(x) + x

def main():
    print(f(3))

main()

