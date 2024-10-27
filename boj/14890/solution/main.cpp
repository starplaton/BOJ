#include <algorithm>  // abs 함수 사용을 위해 추가
#include <iostream>
#include <vector>

using namespace std;

int N, L;
int map_grid[101][101];
int visited[101];
int ans = 0;

void Func() {
    for (int i = 0; i < N; i++) {
        bool flag = true;
        fill_n(visited, N, 0);  // N으로 수정
        for (int j = 0; j < N - 1; j++) {
            if (map_grid[i][j] != map_grid[i][j + 1]) {
                if (abs(map_grid[i][j] - map_grid[i][j + 1]) >= 2) {  // 괄호 수정
                    flag = false;
                    break;
                }
                if (map_grid[i][j] > map_grid[i][j + 1]) {
                    // 내리막 경사로 설치
                    for (int k = 1; k <= L; k++) {
                        if (j + k >= N || map_grid[i][j + k] != map_grid[i][j + 1] || visited[j + k] == 1) {
                            flag = false;
                            break;
                        }
                        visited[j + k] = 1;
                    }
                    if (!flag) break;
                    j += L - 1;
                } else if (map_grid[i][j] < map_grid[i][j + 1]) {
                    // 오르막 경사로 설치
                    for (int k = 0; k < L; k++) {
                        if (j - k < 0 || map_grid[i][j - k] != map_grid[i][j] || visited[j - k] == 1) {
                            flag = false;
                            break;
                        }
                        visited[j - k] = 1;
                    }
                    if (!flag) break;
                }
            }
        }
        if (flag) {
            ans++;
        }
    }
}

int main() {
    cin >> N >> L;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map_grid[i][j];

    ans = 0;

    Func();
    // 지도 전치 (행과 열을 바꿈)
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            swap(map_grid[i][j], map_grid[j][i]);
        }
    }

    Func();

    cout << ans;
}
