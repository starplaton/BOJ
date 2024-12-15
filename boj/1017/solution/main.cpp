#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// 소수 판별을 위한 에라토스테네스의 체
const int MAX = 2000;
bool isPrime[MAX + 1];

// 소수 판별 테이블 생성
void sieve() {
    fill(isPrime, isPrime + MAX + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAX; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

// DFS를 사용한 이분 매칭
bool dfs(int u, vector<vector<int>>& adj, vector<int>& match, vector<bool>& visited) {
    for (int v : adj[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        if (match[v] == -1 || dfs(match[v], adj, match, visited)) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    sieve();  // 소수 판별 테이블 생성

    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    int first = numbers[0];
    vector<int> candidates(numbers.begin() + 1, numbers.end());

    vector<int> result;

    // 첫 번째 숫자를 다른 숫자와 짝지음
    for (int i = 0; i < candidates.size(); ++i) {
        if (!isPrime[first + candidates[i]]) continue;

        // 그래프 초기화
        vector<vector<int>> adj(candidates.size());
        for (int j = 0; j < candidates.size(); ++j) {
            if (i == j) continue;
            for (int k = 0; k < candidates.size(); ++k) {
                if (j != k && isPrime[candidates[j] + candidates[k]]) {
                    adj[j].push_back(k);
                }
            }
        }

        // 이분 매칭 수행
        vector<int> match(candidates.size(), -1);
        bool possible = true;
        for (int j = 0; j < candidates.size(); ++j) {
            if (j == i) continue;
            vector<bool> visited(candidates.size(), false);
            if (!dfs(j, adj, match, visited)) {
                possible = false;
                break;
            }
        }

        // 모든 숫자가 매칭되면 결과 저장
        if (possible) {
            result.push_back(candidates[i]);
        }
    }

    // 결과 출력
    if (result.empty()) {
        cout << -1 << endl;
    } else {
        sort(result.begin(), result.end());
        for (int num : result) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
