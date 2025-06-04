# import math # 모듈 명 명시 해야 함.
# from math import * # 귀찮으면 이렇게 함.
# pip install numpy
# sudo python3 -m pip install numpy
from math import e, pi, sin, tau  # 단위로 쓸 수 있음.

import numpy as np


def main():
    # pi = 10
    print(np.pi)
    print(pi, e, tau)
    print(sin(30 / 180 * pi))  # sin 30도-> 라디안


if __name__ == "__main__":
    main()
