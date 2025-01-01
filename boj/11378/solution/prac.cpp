#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Dinic {
    struct Edge {
        int to, rev;
        ll cap;
    };

    vector<vector<Edge>> graph;
    vector<int> level, it;

    Dinic(int n) {
        graph.assign(n, {});
        level.assign(n, -1);
        it.assign(n, 0);
    }

    void addEdge(int u, int v, ll cap) {
        graph[u].push_back({v, (int)graph[v].size(), cap});
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

    ll sendFlow(int u, ll flow, int t) {
        if (!flow) return 0;
        if (u == t) return flow;

        for (int &i = it[u]; i < (int)graph[u].size(); i++) {
            auto &e = graph[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                ll curFlow = min(flow, e.cap);
                ll tempFlow = sendFlow(e.to, curFlow, t);

                if (tempFlow > 0) {
                    e.cap -= tempFlow;
                    graph[e.to][e.rev].cap += tempFlow;
                    return tempFlow;
                }
            }
        }
        return 0;
    }

    ll maxFlow(int s, int t) {
        ll total = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll flow = sendFlow(s, LLONG_MAX, t)) {
                total += flow;
            }
        }
        return total;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    int S = 0;
    int P = 1;
    int T = N + M + 2;

    Dinic dinic(T + 1);

    dinic.addEdge(S, P, K);

    auto emp_idx = [&](int i) { return 2 + (i - 1); };
    auto job_idx = [&](int j) { return 2 + N + (j - 1); };

    for (int i = 1; i <= N; i++) {
        int eIndex = emp_idx(i);
        dinic.addEdge(P, eIndex, K);
        dinic.addEdge(S, eIndex, 1);
    }

    for (int i = 1; i <= N; i++) {
        int c;
        cin >> c;

        while (c--) {
            int job;
            cin >> job;
            int eIndex = emp_idx(i);
            int jIndex = job_idx(job);
            dinic.addEdge(eIndex, jIndex, 1);
        }
    }

    for (int j = 1; j <= M; j++) {
        dinic.addEdge(job_idx(j), T, 1);
    }

    ll ans = dinic.maxFlow(S, T);
    cout << ans << "\n";

    return 0;
}