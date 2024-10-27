import sys

sys.setrecursionlimit(10**6)


# DFS 함수 정의
def dfs(node, parent):
    dp[node][0] = 0  # node가 얼리 어답터가 아닌 경우
    dp[node][1] = 1  # node가 얼리 어답터인 경우

    for child in graph[node]:
        if child != parent:
            dfs(child, node)
            dp[node][0] += dp[child][
                1
            ]  # node가 얼리 어답터가 아닌 경우, 자식은 얼리 어답터여야 함
            dp[node][1] += min(
                dp[child][0], dp[child][1]
            )  # node가 얼리 어답터인 경우, 자식은 얼리 어답터일 수도 아닐 수도 있음


# 입력 처리
input = sys.stdin.read
data = input().split()

N = int(data[0])  # 첫 번째 값은 N
graph = [[] for _ in range(N + 1)]
dp = [[0] * 2 for _ in range(N + 1)]

# 친구 관계 트리 입력
index = 1
for _ in range(N - 1):
    u = int(data[index])
    v = int(data[index + 1])
    graph[u].append(v)
    graph[v].append(u)
    index += 2

# DFS로 트리 순회하며 DP 계산
dfs(1, -1)

# 루트 노드에서 얼리 어답터일 때와 아닐 때 중 최소값 출력
print(min(dp[1][0], dp[1][1]))
