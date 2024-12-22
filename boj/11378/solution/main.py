from collections import defaultdict, deque


def maximum_matching(N, M, K, tasks):
    graph = defaultdict(list)
    for i, task_list in enumerate(tasks, 1):
        for task in task_list:
            graph[i].append(task)

    def bfs():
        for i in range(1, N + 1):
            if pair_u[i] == 0:
                queue.append(i)
                dist[i] = 0
            else:
                dist[i] = float("inf")
        dist[0] = float("inf")
        while queue:
            u = queue.popleft()
            if dist[u] < dist[0]:
                for v in graph[u]:
                    if dist[pair_v[v]] == float("inf"):
                        dist[pair_v[v]] = dist[u] + 1
                        queue.append(pair_v[v])
        return dist[0] != float("inf")

    def dfs(u):
        if u != 0:
            for v in graph[u]:
                if dist[pair_v[v]] == dist[u] + 1:
                    if dfs(pair_v[v]):
                        pair_u[u] = v
                        pair_v[v] = u
                        return True
            dist[u] = float("inf")
            return False
        return True

    # Pairings for bipartite matching
    pair_u = [0] * (N + 1)
    pair_v = [0] * (M + 1)
    dist = [0] * (N + 1)
    queue = deque()

    max_match = 0
    while bfs():
        for i in range(1, N + 1):
            if pair_u[i] == 0:
                if dfs(i):
                    max_match += 1

    return max_match


# Input parsing
N, M, K = map(int, input().split())
tasks = []
for _ in range(N):
    line = list(map(int, input().split()))
    tasks.append(line[1:])

# Calculate the result
result = maximum_matching(N, M, K, tasks)
print(result)
