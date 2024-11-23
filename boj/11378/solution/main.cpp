#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;        // 도착 노드
    int rev;       // 역방향 에지 인덱스
    int capacity;  // 잔여 용량
    int cost;      // 비용
};

class MinCostMaxFlow {
   public:
    int N;
    vector<vector<Edge>> graph;
    MinCostMaxFlow(int nodes) : N(nodes), graph(nodes, vector<Edge>()) {}

    void add_edge(int from, int to, int capacity, int cost) {
        Edge a = {to, (int)graph[to].size(), capacity, cost};
        Edge b = {from, (int)(graph[from].size()), 0, -cost};
        graph[from].push_back(a);
        graph[to].push_back(b);
    }

    // SPFA를 이용한 최소 비용 최대 흐름 계산
    pair<int, int> min_cost_flow(int s, int t, int max_cost) {
        int flow = 0;
        int flow_cost = 0;
        vector<int> prevv(N, -1);
        vector<int> preve(N, -1);
        while (true) {
            // 거리와 인큐 여부 초기화
            vector<int> dist(N, INT32_MAX);
            dist[s] = 0;
            // 0-1 BFS을 위한 deque 사용
            deque<int> dq;
            dq.push_back(s);
            // 부모 노드와 에지 저장
            vector<pair<int, int>> parent(N, {-1, -1});
            while (!dq.empty()) {
                int u = dq.front();
                dq.pop_front();
                for (int i = 0; i < graph[u].size(); ++i) {
                    Edge &e = graph[u][i];
                    if (e.capacity > 0 && dist[e.to] > dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        parent[e.to] = {u, i};
                        if (e.cost == 0)
                            dq.push_front(e.to);
                        else
                            dq.push_back(e.to);
                    }
                }
            }
            if (parent[t].first == -1)
                break;  // 더 이상 경로 없음
            // 흐름 증가량 결정
            int d = max_cost - flow_cost;
            int v = t;
            while (v != s) {
                int u = parent[v].first;
                int idx = parent[v].second;
                d = min(d, graph[u][idx].capacity);
                v = u;
            }
            // 총 비용 초과 시 조정
            // 계산된 d 만큼의 흐름을 보내면 총 비용이 d * path_cost 추가됨
            // 여기서 path_cost는 dist[t]
            if ((long long)(flow_cost) + (long long)(dist[t]) * d > (long long)max_cost) {
                // 최대 가능한 흐름을 보내기 위해 d를 조정
                d = (max_cost - flow_cost) / dist[t];
                if (d == 0)
                    break;
            }
            flow += d;
            flow_cost += d * dist[t];
            // 흐름 보내기
            v = t;
            while (v != s) {
                int u = parent[v].first;
                int idx = parent[v].second;
                graph[u][idx].capacity -= d;
                graph[v][graph[u][idx].rev].capacity += d;
                v = u;
            }
            if (flow_cost == max_cost)
                break;
        }
        return {flow, flow_cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    // 노드 번호:
    // 0: Source
    // 1~N: Employees
    // N+1 ~ N+M: Tasks
    // N+M+1: Sink
    int S = 0;
    int T = N + M + 1;
    MinCostMaxFlow mcmf(N + M + 2);

    // 직원별 처리 가능한 일 입력
    // 입력 형식: 각 직원이 처리할 수 있는 일의 개수와 일 번호
    for (int i = 1; i <= N; i++) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int task;
            cin >> task;
            // 직원 i는 task를 처리할 수 있음
            // 직원 i는 node i, task는 node N + task
            mcmf.add_edge(i, N + task, 1, 0);
        }
    }

    // 소스에서 직원으로의 에지 추가
    for (int i = 1; i <= N; i++) {
        // 기본 처리 능력 (벌점 없이 처리할 수 있는 일 수)
        mcmf.add_edge(S, i, 1, 0);
        // 벌점을 통해 추가로 처리할 수 있는 능력
        if (K > 0) {
            mcmf.add_edge(S, i, K, 1);
        }
    }

    // 일에서 싱크로의 에지 추가
    for (int i = 1; i <= M; i++) {
        mcmf.add_edge(N + i, T, 1, 0);
    }

    // 최소 비용 최대 흐름 계산
    pair<int, int> result = mcmf.min_cost_flow(S, T, K);

    // 최대 할당된 일의 수는 flow
    cout << result.first;
}
