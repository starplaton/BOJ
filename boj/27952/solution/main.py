import sys


def main():
    import sys
    import math

    input = sys.stdin.readline

    N, X = map(int, input().split())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    W = 0  # 초기 몸무게
    total_k = 0  # 총 루틴 횟수

    for i in range(N):
        W += B[i]
        if W < A[i]:
            print(-1)
            return

    total_k = (W - A[N - 1]) / X
    print(int(total_k))


main()
