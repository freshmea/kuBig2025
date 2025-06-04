# indentation 주의!!
# string정의 "string.. 안녕하세요." + 'string.. 안녕하세요' <- 같다.
def main():
    input_var = input("숫자를 입력하세요! : ")
    print(type(input_var), input_var)
    if input_var.isdigit():
        print("input_var + 100 : ", int(input_var) + 100)
    else:
        print(input_var, "은 숫자가 아닙니다.", sep="")


if __name__ == "__main__":
    main()
