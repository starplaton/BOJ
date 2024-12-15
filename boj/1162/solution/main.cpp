#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
const long long INF = 1e18;

struct Edge {
    int to;
    long long time;
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        graph[u].push_back({v, t});
        graph[v].push_back({u, t});
    }

    // 최단 거리 테이블: [도시][포장 횟수] = 최소 시간
    vector<vector<long long>> dist(N + 1, vector<long long>(K + 1, INF));
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;

    // 시작점 초기화
    dist[1][0] = 0;
    pq.push({0, 1, 0});  // (현재 시간, 현재 도시, 사용한 포장 횟수)

    while (!pq.empty()) {
        auto [cur_time, cur_city, paved] = pq.top();
        pq.pop();

        // 이미 더 작은 시간으로 처리된 경우 무시
        if (cur_time > dist[cur_city][paved]) continue;

        // 인접 도시 탐색
        for (auto& edge : graph[cur_city]) {
            int next_city = edge.to;
            long long travel_time = edge.time;

            // 1. 포장하지 않고 이동
            if (cur_time + travel_time < dist[next_city][paved]) {
                dist[next_city][paved] = cur_time + travel_time;
                pq.push({dist[next_city][paved], next_city, paved});
            }

            // 2. 포장하여 이동 (포장 가능 횟수가 남아있을 때)
            if (paved < K && cur_time < dist[next_city][paved + 1]) {
                dist[next_city][paved + 1] = cur_time;
                pq.push({dist[next_city][paved + 1], next_city, paved + 1});
            }
        }
    }

    // 도시 N까지의 최소 시간 찾기
    long long answer = INF;
    for (int i = 0; i <= K; i++) {
        answer = min(answer, dist[N][i]);
    }

    cout << answer << endl;

    return 0;
}
