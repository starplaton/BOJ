import sys


def main():
    import sys

    input = sys.stdin.read
    data = input().split()

    K = int(data[0])
    S = data[1]
    N = len(S)

    dp = [float("inf")] * (N + 1)
    dp[0] = 0

    for idx, bit in enumerate(S):
        bit_val = int(bit)
        for j in range(min(idx + 1, N), -1, -1):
            if j == 0 and bit_val == 0:
                continue
            if j == 1 and bit_val == 0:
                continue
            if j > 0 and dp[j - 1] != float("inf"):
                new_val = dp[j - 1] * 2 + bit_val
                if new_val <= K and new_val < dp[j]:
                    dp[j] = new_val

    # 가능한 최대 j를 찾기
    max_j = -1
    for j in range(N, 0, -1):
        if dp[j] <= K:
            max_j = j
            break

    if max_j == -1:
        print(-1)
    else:
        bits_removed = N - max_j
        print(bits_removed)


if __name__ == "__main__":
    main()
