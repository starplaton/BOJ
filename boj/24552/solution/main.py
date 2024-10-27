import sys

input = sys.stdin.readline

S = input().strip()
N = len(S)

# 왼쪽에서 오른쪽으로의 누적 균형과 최소값 계산
left_balance = [0] * (N + 1)
left_min = [0] * (N + 1)
for i in range(N):
    if S[i] == "(":
        left_balance[i + 1] = left_balance[i] + 1
    else:
        left_balance[i + 1] = left_balance[i] - 1
    left_min[i + 1] = min(left_min[i], left_balance[i + 1])

# 오른쪽에서 왼쪽으로의 누적 균형과 최소값 계산
right_balance = [0] * (N + 1)
right_min = [0] * (N + 1)
for i in range(N - 1, -1, -1):
    if S[i] == "(":
        right_balance[i] = right_balance[i + 1] - 1
    else:
        right_balance[i] = right_balance[i + 1] + 1
    right_min[i] = min(right_min[i + 1], right_balance[i])

result = 0
# print(left_balance)
# print(right_balance)
for i in range(N):
    if S[i] == "(":
        delta = -1
    else:
        delta = 1

    total_balance = left_balance[i] - right_balance[i + 1]
    min_balance = min(right_min[i + 1], left_min[i], left_balance[i] + right_min[i + 1])

    if total_balance == 0 and min_balance >= 0:
        result += 1

print(result)
