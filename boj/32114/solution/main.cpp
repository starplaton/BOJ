#include <bits/stdc++.h>
using namespace std;

// 도로 부담을 계산하는 함수
inline long long calculateRoadBurden(long long cars, long long lanes) {
    if (lanes == 0) return 0;  // 차선이 없는 경우, 부담은 0
    long long base = cars / lanes;
    long long extra = cars % lanes;
    return extra * (base + 1) * (base + 1) + (lanes - extra) * base * base;
}

int main() {
    // 빠른 I/O 설정
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    // 도로의 차선 수 입력
    vector<long long> lanes(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> lanes[i];
    }

    // 각 도로를 지나는 차량 수를 기록하기 위한 배열
    // 누적 합을 사용하기 위해 N개의 요소를 사용
    vector<long long> carCount(N, 0);

    // 각 차량 이동 정보 처리
    for (int i = 0; i < M; ++i) {
        int u, v;
        long long x;
        cin >> u >> v >> x;
        // 1-based에서 0-based로 변환
        u--;
        v--;
        carCount[u] += x;
        carCount[v] -= x;
    }

    // 누적합을 통해 각 도로의 실제 차량 수 계산
    for (int i = 1; i < N - 1; ++i) {
        carCount[i] += carCount[i - 1];
    }

    // 결과를 저장할 문자열
    string buffer;
    buffer.reserve((N - 1) * 20);  // 예상 크기 예약 (각 도로 부담이 최대 10^18일 수 있으므로 충분히 큰 값)

    // 각 도로의 도로 부담 계산 및 결과 저장
    for (int i = 0; i < N - 1; i++) {
        long long burden = calculateRoadBurden(carCount[i], lanes[i]);
        buffer += to_string(burden);
        buffer += '\n';
    }

    // 한 번에 출력
    cout << buffer;

    return 0;
}
