def print_n_times(*args, **kwargs):
    print(type(args))  # tuple
    print(type(kwargs))  # dict
    print(args)
    for k, v in kwargs.items():
        n = kwargs.get("n")
        if n:
            for _ in range(n):
                print(f"{k} : {v}")


def main():
    print_n_times("hi", 123, 3.145, a=3, b=4, n=2, abc="hihihi")


if __name__ == "__main__":
    main()
