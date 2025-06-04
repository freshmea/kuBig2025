from collections.abc import Iterable


class SimpleIter:
    def __init__(self, start, end):
        self.current = start
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.current >= self.end:
            raise StopIteration
        value = self.current
        self.current += 1
        return value


def main():
    iter_a = SimpleIter(1, 10)

    for i in iter_a:
        print(i)
    li = list()
    dict_a = dict()
    if isinstance(li, Iterable):
        print("li 은 Iterable 하다.")
    if isinstance(dict_a, Iterable):
        print("dict_a 은 Iterable 하다.")
    if isinstance(iter_a, Iterable):
        print("iter_a 은 Iterable 하다.")
        # 두 메소드만 정의 해도 상속된 것처럼 행동한다.


if __name__ == "__main__":
    main()
