class A:
    def __init__(self) -> None:
        self.__a = 1

def main():
    a = A()
    print(a.__a)  # Accessing the protected member _a directly
    # Note: In Python, this is allowed, but it's a convention to indicate that it should not be accessed directly.


if __name__ == "__main__":
    main()
