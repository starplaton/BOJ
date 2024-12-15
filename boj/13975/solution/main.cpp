#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;
        // 파일 크기를 저장할 벡터
        vector<ll> files(K);
        for (int i = 0; i < K; i++) cin >> files[i];
        // 최소 힙을 생성
        priority_queue<ll, vector<ll>, greater<ll>> pq(files.begin(), files.end());
        ll total = 0;
        // 힙에 파일이 하나만 남을 때까지 반복
        while (pq.size() > 1) {
            // 가장 작은 두 파일을 꺼냄
            ll a = pq.top();
            pq.pop();
            ll b = pq.top();
            pq.pop();
            ll sum = a + b;
            total += sum;
            // 합친 파일을 다시 힙에 삽입
            pq.push(sum);
        }
        cout << total << "\n";
    }
}
