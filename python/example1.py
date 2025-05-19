# 파이썬으로 구구단 출력하기 2단 -> 9단
def main():
    dan = "23456789"
    for i in dan:
        print(f"{i} 단 입니다.")
        for j in dan:
            print(i, "*", j, "=", int(i) * int(j))


if __name__ == "__main__":
    main()
