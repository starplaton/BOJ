#include <iostream>
#include <vector>

using namespace std;

int N, L;
int map[101][101];
int visited[101];
int ans = 0;
vector<int> road;

bool Check(int i, int j) {
    if (i >= 0 && i < N && j >= 0 && j < N) return true;
    return false;
}

void Func() {
    for (int i = 0; i < N; i++) {
        int cnt = L;
        bool flag = true;
        fill_n(visited, 101, 0);
        for (int j = 0; j < N - 1; j++) {
            if (map[i][j] != map[i][j + 1]) {
                if (abs(map[i][j] - map[i][j + 1] >= 2)) flag = false;
                if (map[i][j] > map[i][j + 1]) {
                    for (int k = 0; k < L - 1; k++) {
                        if (!Check(i, j + k + 2)) {
                            flag = false;
                            break;
                        }
                        if (visited[j + k + 1] != 0 || visited[j + k + 2] != 0) flag = false;
                        if (map[i][j + k + 1] != map[i][j + k + 2]) {
                            flag = false;
                            break;
                        } else if (k != L - 2) {
                            visited[j + k + 1] = 1;
                        } else if (k == L - 2) {
                            visited[j + k + 1] = visited[j + k + 2] = 1;
                        }
                    }
                    if (L == 1) {
                        if (visited[j + 1] != 0) flag = false;
                        visited[j + 1] = 1;
                    }
                } else if (map[i][j] < map[i][j + 1]) {
                    for (int k = 0; k < L - 1; k++) {
                        if (!Check(i, j - k - 1)) {
                            flag = false;
                            break;
                        }
                        if (visited[j - k] != 0 || visited[j - k - 1] != 0) flag = false;
                        if (map[i][j - k] != map[i][j - k - 1]) {
                            flag = false;
                            break;
                        } else if (k != L - 2) {
                            visited[j - k] = 1;
                        } else if (k == L - 2) {
                            visited[j - k] = visited[j - k - 1] = 1;
                        }
                    }
                    if (L == 1) {
                        if (visited[j] != 0) flag = false;
                        visited[j] = 1;
                    }
                }
            }
        }
        if (flag) {
            //	printf("i : %d\n", i);
            ans++;
        }
    }
}

int main() {
    cin >> N >> L;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    ans = 0;

    Func();
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }
    fill_n(visited, 101, 0);

    Func();

    cout << ans;
}