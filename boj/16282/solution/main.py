import math


def min_splits(n):
    # m: 필요한 세그먼트 수 (1, 2, 4, 8, ...)
    m = math.ceil(math.log2(n + 1))

    # k: 최소 분리 횟수
    k = math.ceil((m - 1) / 2)

    # 예외 케이스 처리
    # 예를 들어, n=4일 때 k=1로 계산되지만 실제로는 k=2가 필요함
    # 이는 m=3일 때 n=4가 2^3 -1=7보다 작으므로 추가 분리 필요
    if m > 1:
        max_coverage = (2**m) - 1
        if n > (2 ** (m - 1)) - 1:
            # 추가적인 분리가 필요
            k += 1
    return k


def main():
    import sys

    input = sys.stdin.read
    n = int(input().strip())
    print(min_splits(n))


if __name__ == "__main__":
    main()
