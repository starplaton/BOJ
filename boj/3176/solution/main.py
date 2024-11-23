import sys
from collections import defaultdict, deque
import math

input = sys.stdin.read
sys.setrecursionlimit(200000)


def preprocess_tree(n, edges):
    graph = defaultdict(list)
    for a, b, c in edges:
        graph[a].append((b, c))
        graph[b].append((a, c))
    return graph


def dfs(node, parent, depth, graph, depths, parents, min_cost, max_cost):
    for neighbor, cost in graph[node]:
        if neighbor != parent:
            depths[neighbor] = depths[node] + 1
            parents[neighbor][0] = node
            min_cost[neighbor][0] = cost
            max_cost[neighbor][0] = cost
            dfs(neighbor, node, depth + 1, graph, depths, parents, min_cost, max_cost)


def prepare_lca(n, graph):
    log_n = math.ceil(math.log2(n)) + 1
    parents = [[-1] * log_n for _ in range(n + 1)]
    min_cost = [[float("inf")] * log_n for _ in range(n + 1)]
    max_cost = [[0] * log_n for _ in range(n + 1)]
    depths = [0] * (n + 1)

    dfs(1, -1, 0, graph, depths, parents, min_cost, max_cost)

    for j in range(1, log_n):
        for i in range(1, n + 1):
            if parents[i][j - 1] != -1:
                parents[i][j] = parents[parents[i][j - 1]][j - 1]
                min_cost[i][j] = min(
                    min_cost[i][j - 1], min_cost[parents[i][j - 1]][j - 1]
                )
                max_cost[i][j] = max(
                    max_cost[i][j - 1], max_cost[parents[i][j - 1]][j - 1]
                )

    return parents, min_cost, max_cost, depths


def query_lca(u, v, parents, min_cost, max_cost, depths):
    if depths[u] < depths[v]:
        u, v = v, u
    diff = depths[u] - depths[v]
    min_res, max_res = float("inf"), 0
    log_n = len(parents[0])

    for i in range(log_n):
        if diff & (1 << i):
            min_res = min(min_res, min_cost[u][i])
            max_res = max(max_res, max_cost[u][i])
            u = parents[u][i]

    if u == v:
        return min_res, max_res

    for i in range(log_n - 1, -1, -1):
        if parents[u][i] != parents[v][i]:
            min_res = min(min_res, min_cost[u][i], min_cost[v][i])
            max_res = max(max_res, max_cost[u][i], max_cost[v][i])
            u = parents[u][i]
            v = parents[v][i]

    min_res = min(min_res, min_cost[u][0], min_cost[v][0])
    max_res = max(max_res, max_cost[u][0], max_cost[v][0])

    return min_res, max_res


def solve():
    data = input().splitlines()
    n = int(data[0])
    edges = []
    for i in range(1, n):
        a, b, c = map(int, data[i].split())
        edges.append((a, b, c))

    graph = preprocess_tree(n, edges)
    parents, min_cost, max_cost, depths = prepare_lca(n, graph)

    k = int(data[n])
    results = []
    for i in range(n + 1, n + 1 + k):
        d, e = map(int, data[i].split())
        min_res, max_res = query_lca(d, e, parents, min_cost, max_cost, depths)
        results.append(f"{min_res} {max_res}")

    sys.stdout.write("\n".join(results) + "\n")


if __name__ == "__main__":
    solve()
