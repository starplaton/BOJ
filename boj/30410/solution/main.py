# https://www.acmicpc.net/problem/12008
input = __import__("sys").stdin.readline

n = int(input())
block = list(map(int, input().split()))

# [i, dp[i]] sums to block _, or dp[i] == -1
dp = [-1] * n
ans = -1
for x in range(1, 60):
    ndp = [(i if block[i] == x else -1) for i in range(n)]
    for i in range(n):
        if dp[i] == -1 or dp[i] + 1 >= n:
            continue
        ndp[i] = dp[dp[i] + 1]
    ans = x if max(ndp) != -1 else ans
    dp = ndp
print(2 ** (ans - 1))
