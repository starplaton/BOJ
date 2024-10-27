from collections import deque

# 입력 받기
N = int(input())
mA, fA = map(int, input().split())
mB, fB = map(int, input().split())
mC, fC = map(int, input().split())

# 노드 번호 설정
S = 0  # 소스
T = 7  # 싱크
node_mA = 1
node_mB = 2
node_mC = 3
node_fA = 4
node_fB = 5
node_fC = 6

# 그래프 초기화
graph = [[] for _ in range(8)]
capacity = [[0] * 8 for _ in range(8)]
flow = [[0] * 8 for _ in range(8)]


# 간선 추가 함수
def add_edge(u, v, c):
    graph[u].append(v)
    graph[v].append(u)
    capacity[u][v] = c


# 소스에서 남학생 그룹으로 가는 간선
add_edge(S, node_mA, mA)
add_edge(S, node_mB, mB)
add_edge(S, node_mC, mC)

# 남학생 그룹과 여학생 그룹 간의 간선 (같은 학교 제외)
add_edge(node_mA, node_fB, N)
add_edge(node_mA, node_fC, N)
add_edge(node_mB, node_fA, N)
add_edge(node_mB, node_fC, N)
add_edge(node_mC, node_fA, N)
add_edge(node_mC, node_fB, N)

# 여학생 그룹에서 싱크로 가는 간선
add_edge(node_fA, T, fA)
add_edge(node_fB, T, fB)
add_edge(node_fC, T, fC)


# 최대 유량 계산 (에드몬드-카프 알고리즘)
def max_flow(S, T):
    total_flow = 0
    while True:
        parent = [-1] * 8
        queue = deque()
        queue.append(S)
        while queue:
            u = queue.popleft()
            for v in graph[u]:
                if capacity[u][v] - flow[u][v] > 0 and parent[v] == -1:
                    parent[v] = u
                    queue.append(v)
                    if v == T:
                        break
        if parent[T] == -1:
            break
        increment = float("inf")
        v = T
        while v != S:
            u = parent[v]
            increment = min(increment, capacity[u][v] - flow[u][v])
            v = u
        v = T
        while v != S:
            u = parent[v]
            flow[u][v] += increment
            flow[v][u] -= increment
            v = u
        total_flow += increment
    return total_flow


total_flow = max_flow(S, T)

# 결과 출력
if total_flow == N:
    print(1)
    # mA와 fB, fC 간의 매칭 결과
    x1 = flow[node_mA][node_fB]
    x2 = flow[node_mA][node_fC]
    print(f"{x1} {x2}")
    # mB와 fA, fC 간의 매칭 결과
    x3 = flow[node_mB][node_fA]
    x4 = flow[node_mB][node_fC]
    print(f"{x3} {x4}")
    # mC와 fA, fB 간의 매칭 결과
    x5 = flow[node_mC][node_fA]
    x6 = flow[node_mC][node_fB]
    print(f"{x5} {x6}")
else:
    print(0)
