#include <bits/stdc++.h>
using namespace std;

// Union-Find (Disjoint Set Union) 구조체
struct UnionFind {
    vector<int> parent;
    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find_set(int x) {
        return parent[x] == x ? x : parent[x] = find_set(parent[x]);
    }
    void union_set(int x, int y) {
        int fx = find_set(x);
        int fy = find_set(y);
        if (fx != fy) parent[fy] = fx;
    }
};

// 행성 구조체
struct Planet {
    int id;
    long long x, y, z;
};

// 간선 구조체
struct Edge {
    int a, b;
    long long cost;
};

// 메인 함수
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<Planet> planets(N);
    for (int i = 0; i < N; ++i) {
        cin >> planets[i].x >> planets[i].y >> planets[i].z;
        planets[i].id = i;
    }

    vector<Edge> edges;

    // 정렬 기준을 x, y, z 각각에 대해 수행
    for (int dim = 0; dim < 3; ++dim) {
        // 람다 함수를 이용한 정렬
        sort(planets.begin(), planets.end(), [&](const Planet &a, const Planet &b) -> bool {
            if (dim == 0) return a.x < b.x;
            if (dim == 1) return a.y < b.y;
            return a.z < b.z;
        });

        // 인접한 행성들 간의 간선 추가
        for (int i = 0; i < N - 1; ++i) {
            long long cost;
            if (dim == 0) {
                cost = abs(planets[i].x - planets[i + 1].x);
            } else if (dim == 1) {
                cost = abs(planets[i].y - planets[i + 1].y);
            } else {
                cost = abs(planets[i].z - planets[i + 1].z);
            }
            edges.push_back(Edge{planets[i].id, planets[i + 1].id, cost});
        }
    }

    // 간선들을 비용 오름차순으로 정렬
    sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b) -> bool {
        return a.cost < b.cost;
    });

    // Union-Find 초기화
    UnionFind uf(N);

    long long total_cost = 0;
    int edges_used = 0;

    // 크루스칼 알고리즘 적용
    for (auto &edge : edges) {
        if (uf.find_set(edge.a) != uf.find_set(edge.b)) {
            uf.union_set(edge.a, edge.b);
            total_cost += edge.cost;
            edges_used++;
            if (edges_used == N - 1) break;
        }
    }

    cout << total_cost;
}
