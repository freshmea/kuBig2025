def main():
    print(1234567)  # C에서는 '\n' 줄바꿈
    print(1_234_567)  # 1'234'567
    print("choi su gil")
    print(3.141592)

    print("this is", "python", "class!!")
    print(10, 20, 30, "hi", "fifty")
    print()  # 줄바꿈

    print("this is", "python", "class!!", sep="*", end="")
    print("this is", "python", "class!!", sep="-")


if __name__ == "__main__":
    main()
