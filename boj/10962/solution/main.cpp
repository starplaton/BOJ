#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // 플레이어는 1부터 n까지 번호가 매겨짐
    // 인접 리스트로 그래프 표현
    vector<vector<int>> adj(n + 1, vector<int>());

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // DSATUR 알고리즘을 위한 자료구조
    // 색칠된 노드 여부
    vector<int> color(n + 1, 0);  // color[0] unused
    // 각 노드의 현재 차수 포화도
    vector<int> sat_degree(n + 1, 0);
    // 각 노드의 차수
    vector<int> degree(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        degree[i] = adj[i].size();
    }

    // 우선순위 큐: (차수 포화도, 차수, 노드 번호)
    // 높은 차수 포화도, 높은 차수, 낮은 노드 번호 순으로 정렬
    // max heap
    auto cmp = [&](const tuple<int, int, int> &a, const tuple<int, int, int> &b) -> bool {
        if (get<0>(a) != get<0>(b)) return get<0>(a) < get<0>(b);  // 포화도 높은 순
        if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b);  // 차수 높은 순
        return get<2>(a) > get<2>(b);                              // 노드 번호 낮은 순
    };
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> pq(cmp);

    // 초기 모든 노드를 우선순위 큐에 삽입
    for (int i = 1; i <= n; ++i) {
        pq.emplace(sat_degree[i], degree[i], i);
    }

    while (!pq.empty()) {
        // 가장 높은 우선순위를 가진 노드 선택
        auto current = pq.top();
        pq.pop();
        int sat = get<0>(current);
        int deg = get<1>(current);
        int node = get<2>(current);

        if (color[node] != 0) {
            continue;  // 이미 색칠된 노드
        }

        // 인접 노드들이 사용한 색상 확인
        vector<bool> used_colors;
        // 색상은 1부터 시작
        // 최대 색상 수는 n
        used_colors.assign(n + 1, false);
        for (auto &neighbor : adj[node]) {
            if (color[neighbor] != 0) {
                used_colors[color[neighbor]] = true;
            }
        }
        // 가장 작은 사용하지 않은 색상 찾기
        int assigned_color = 1;
        while (assigned_color <= n && used_colors[assigned_color]) {
            assigned_color++;
        }
        color[node] = assigned_color;

        // 인접 노드들의 차수 포화도 갱신
        for (auto &neighbor : adj[node]) {
            if (color[neighbor] == 0) {
                // 만약 아직 색칠되지 않았다면, 해당 노드의 포화도를 증가시킨다.
                // 포화도는 인접 노드들이 사용한 색상 수
                // 색을 새로 추가했으므로, 포화도를 증가시킨다.
                sat_degree[neighbor]++;
                pq.emplace(sat_degree[neighbor], degree[neighbor], neighbor);
            }
        }
    }

    // 색깔별로 플레이어 그룹화
    // 최대 색상 수 찾기
    int max_color = 0;
    for (int i = 1; i <= n; ++i) {
        if (color[i] > max_color) {
            max_color = color[i];
        }
    }

    // 팀별 플레이어 리스트
    vector<vector<int>> teams(max_color + 1, vector<int>());
    for (int i = 1; i <= n; ++i) {
        teams[color[i]].push_back(i);
    }

    // 출력
    cout << max_color << "\n";
    for (int c = 1; c <= max_color; ++c) {
        for (int i = 0; i < teams[c].size(); ++i) {
            if (i > 0) cout << " ";
            cout << teams[c][i];
        }
        cout << "\n";
    }

    return 0;
}
