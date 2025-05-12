# matplotlib
# pip install matplotlib
# sudo python3 -m pip install matplotlib
# uniform -> 균등 , gauss, normal.. -> 정규...
# uniform -> 정규분포 만들기.( 중심 극한 정리...)
import math
import random

import matplotlib.pyplot as plt


def main():
    n_samples = 10000
    sample_size = 30
    a = 0
    b = 1

    means = []

    # uniform 균등 분포 결과 테스트
    for _ in range(n_samples):
        sample = [random.uniform(a, b) for _ in range(sample_size)]
        mean = sum(sample) / sample_size
        means.append(mean)

    plt.hist(means, bins=sample_size)

    mu = (a + b) / 2
    sigma = math.sqrt((b - a) ** 2 / (12 * sample_size))  # 표준 편차

    # x = [mu - 4 * sigma + i * (8 * sigma / 100) for i in range(100)]
    # y = [random.gauss(mu, sigma) for t in x]

    # plt.plot(x, y)
    plt.show()


if __name__ == "__main__":
    main()
