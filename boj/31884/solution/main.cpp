#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;

    // x좌표를 키로, y좌표를 값으로 하는 맵
    unordered_map<long long, long long> height_map;

    while (Q--) {
        int type;
        long long i;
        cin >> type >> i;

        if (type == 1) {
            // 가로 블록: x=i부터 x=i+3까지
            long long max_y = 0;
            // 최대 y좌표 찾기
            for (long long x = i; x <= i + 3; x++) {
                if (height_map.find(x) != height_map.end()) {
                    if (height_map[x] > max_y) {
                        max_y = height_map[x];
                    }
                }
            }
            // 새로운 y좌표는 max_y +1
            long long new_y = max_y + 1;
            for (long long x = i; x <= i + 3; x++) {
                height_map[x] = new_y;
            }
        } else if (type == 2) {
            // 세로 블록: x=i
            long long current_y = 0;
            if (height_map.find(i) != height_map.end()) {
                current_y = height_map[i];
            }
            height_map[i] = current_y + 4;
        } else if (type == 3) {
            // y좌표 출력
            if (height_map.find(i) != height_map.end()) {
                cout << height_map[i] << "\n";
            } else {
                cout << "0\n";
            }
        }
    }

    return 0;
}
