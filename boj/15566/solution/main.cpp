#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

struct Frog {
    array<int, 4> interests;      // 음식, 취미, 가족, 철학 흥미도
    vector<int> preferredLilies;  // 선호 연꽃 번호
};

struct Log {
    int lily1, lily2, topic;  // 연결된 연꽃과 대화 주제
};

int N, M;
vector<Frog> frogs;
vector<Log> logs;
vector<int> lilyToFrog;  // 연꽃에 배치된 개구리 번호

bool isValidPlacement() {
    for (const auto& log : logs) {
        int frog1 = lilyToFrog[log.lily1];
        int frog2 = lilyToFrog[log.lily2];
        int topic = log.topic - 1;  // 주제는 0-based로 변환
        if (frogs[frog1].interests[topic] != frogs[frog2].interests[topic])
            return false;
    }
    return true;
}

bool assignFrogs(int lilyIndex) {
    if (lilyIndex == N) {
        return isValidPlacement();
    }

    for (int i = 0; i < N; i++) {
        if (find(frogs[i].preferredLilies.begin(), frogs[i].preferredLilies.end(), lilyIndex + 1) != frogs[i].preferredLilies.end() &&
            find(lilyToFrog.begin(), lilyToFrog.end(), i) == lilyToFrog.end()) {
            lilyToFrog[lilyIndex] = i;  // 개구리를 배치
            if (assignFrogs(lilyIndex + 1)) return true;
            lilyToFrog[lilyIndex] = -1;  // 배치 취소
        }
    }
    return false;
}

int main() {
    cin >> N >> M;

    frogs.resize(N);
    logs.resize(M);
    lilyToFrog.assign(N, -1);

    // 개구리 흥미도 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> frogs[i].interests[j];
        }
    }

    // 개구리 선호 연꽃 입력
    for (int i = 0; i < N; i++) {
        int A, B;
        cin >> A >> B;
        frogs[i].preferredLilies.push_back(A);
        if (A != B) frogs[i].preferredLilies.push_back(B);
    }

    // 통나무 정보 입력
    for (int i = 0; i < M; i++) {
        cin >> logs[i].lily1 >> logs[i].lily2 >> logs[i].topic;
        logs[i].lily1--;  // 0-based index로 변환
        logs[i].lily2--;
    }

    if (assignFrogs(0)) {
        cout << "YES\n";
        for (int i = 0; i < N; i++) {
            cout << lilyToFrog[i] + 1 << " ";  // 1-based index로 출력
        }
        cout << "\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
