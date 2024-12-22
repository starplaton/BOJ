#include <bits/stdc++.h>
using namespace std;

/*
    BOJ 11378 (열혈강호 4)

    - N명의 직원 (1 ~ N)
    - M개의 일 (1 ~ M)
    - 벌점 합 K (1 <= K <= N)

    네트워크 플로우 (Dinic) 구현:
    노드 구성:
      S (source) = 0
      P (pool)   = 1
      직원 i     = 2 + (i-1)          // i in [1..N]
      일 j       = 2 + N + (j-1)      // j in [1..M]
      T (sink)   = 2 + N + M

    용량:
      S -> P : K
      P -> E_i : K
      S -> E_i : 1
      E_i -> J_j : 1 (직원 i가 일 j를 할 수 있을 때)
      J_j -> T : 1
*/

struct Dinic {
    struct Edge {
        int to, rev;  // rev: 역방향 간선 인덱스
        long long cap;
    };

    vector<vector<Edge>> graph;
    vector<int> level, it;  // level: 레벨 그래프, it: 현재 탐색 중인 간선 인덱스

    Dinic(int n) {
        graph.assign(n, {});
        level.assign(n, -1);
        it.assign(n, 0);
    }

    void addEdge(int u, int v, long long cap) {
        // 정방향 간선
        graph[u].push_back({v, (int)graph[v].size(), cap});
        // 역방향 간선
        graph[v].push_back({u, (int)graph[u].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &e : graph[u]) {
                if (level[e.to] == -1 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long sendFlow(int u, long long flow, int t) {
        if (!flow) return 0;
        if (u == t) return flow;

        for (int &i = it[u]; i < (int)graph[u].size(); i++) {
            auto &e = graph[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                long long curFlow = min(flow, e.cap);
                long long tempFlow = sendFlow(e.to, curFlow, t);

                if (tempFlow > 0) {
                    e.cap -= tempFlow;
                    graph[e.to][e.rev].cap += tempFlow;
                    return tempFlow;
                }
            }
        }
        return 0;
    }

    long long maxFlow(int s, int t) {
        long long total = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (long long flow = sendFlow(s, LLONG_MAX, t))
                total += flow;
        }
        return total;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    // 노드 인덱스 매핑
    // source: S = 0
    // pool:   P = 1
    // employees: 2..(N+1)
    // jobs: (N+2)..(N+M+1)
    // sink: T = N+M+2
    int S = 0;
    int P = 1;
    int T = N + M + 2;

    Dinic dinic(T + 1);

    // 1) S -> P (capacity = K)
    dinic.addEdge(S, P, K);

    // 직원 노드 시작 인덱스
    auto emp_idx = [&](int i) { return 2 + (i - 1); };
    // 일 노드 시작 인덱스
    auto job_idx = [&](int j) { return 2 + N + (j - 1); };

    // 2) P -> E_i (capacity = K)
    // 3) S -> E_i (capacity = 1)
    for (int i = 1; i <= N; i++) {
        int eIndex = emp_idx(i);
        dinic.addEdge(P, eIndex, K);  // P->E_i
        dinic.addEdge(S, eIndex, 1);  // S->E_i
    }

    // 입력을 받아 직원이 할 수 있는 일 정보를 간선으로 연결(E_i -> J_j)
    for (int i = 1; i <= N; i++) {
        int c;  // i번 직원이 할 수 있는 일의 개수
        cin >> c;

        while (c--) {
            int job;
            cin >> job;
            int eIndex = emp_idx(i);
            int jIndex = job_idx(job);
            // 4) E_i -> J_j (capacity = 1)
            dinic.addEdge(eIndex, jIndex, 1);
        }
    }

    // 5) J_j -> T (capacity = 1)
    for (int j = 1; j <= M; j++) {
        dinic.addEdge(job_idx(j), T, 1);
    }

    // 최대 유량 계산 = 최대 할당 가능한 일의 수
    long long ans = dinic.maxFlow(S, T);
    cout << ans << "\n";

    return 0;
}
