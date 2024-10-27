#include <bits/stdc++.h>
using namespace std;

// BFS를 이용하여 도달 가능한 노드의 수를 반환하는 함수
int bfs(int start, const vector<vector<int>> &graph, int N) {
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int count = 0;

    while(!q.empty()) {
        int current = q.front(); q.pop();
        for(auto &neighbor : graph[current]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                count++;
                q.push(neighbor);
            }
        }
    }

    return count;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M;
    cin >> N >> M;
    
    // 그래프와 역방향 그래프 초기화
    vector<vector<int>> G(N + 1, vector<int>());   // 직접 그래프
    vector<vector<int>> R(N + 1, vector<int>());   // 역방향 그래프
    
    // 대결 결과 입력
    for(int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        G[A].push_back(B);   // A가 B를 이겼음
        R[B].push_back(A);   // B에게 A가 이겼음을 역방향 그래프에 추가
    }
    
    int result = 0;
    
    // 각 소에 대해 순위가 정확히 결정되는지 확인
    for(int i = 1; i <= N; i++) {
        // i가 이길 수 있는 소의 수
        int win = bfs(i, G, N);
        // i에게 질 수 있는 소의 수
        int lose = bfs(i, R, N);
        
        // 순위가 정확히 결정되려면, win + lose == N - 1
        if(win + lose == N - 1){
            result++;
        }
    }
    
    cout << result;
}
