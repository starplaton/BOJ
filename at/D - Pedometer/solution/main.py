def solve():
    import sys
    import sys
    import sys

    def input():
        return sys.stdin.read()

    data = input().split()
    N = int(data[0])
    M = int(data[1])
    A = list(map(int, data[2 : 2 + N]))

    prefix_sum = [0] * (N + 1)
    for i in range(1, N + 1):
        prefix_sum[i] = (prefix_sum[i - 1] + A[i - 1]) % M

    # Count s < t pairs
    freq_lt = [0] * M
    result_s_lt_t = 0
    for j in range(N):
        c = prefix_sum[j]
        result_s_lt_t += freq_lt[c]
        freq_lt[c] += 1

    # Count s > t pairs
    S = prefix_sum[N] % M
    freq_gt = [0] * M
    result_s_gt_t = 0
    for j in range(N):
        c = prefix_sum[j]
        target = (c - S) % M
        result_s_gt_t += freq_gt[target]
        freq_gt[c] += 1

    total = result_s_lt_t + result_s_gt_t
    print(total)


if __name__ == "__main__":
    solve()
