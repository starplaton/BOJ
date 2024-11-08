#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, M;
vector<string> conditions;
vector<int> filledCounts;

bool checkConfiguration(const string& config) {
    for (int i = 0; i < M; i++) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (conditions[i][j] == '1' && config[j] == '1') {
                count++;
            }
        }
        if (count != filledCounts[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> N >> M;
    conditions.resize(M);
    filledCounts.resize(M);

    for (int i = 0; i < M; i++) {
        cin >> conditions[i] >> filledCounts[i];
    }

    int possibleCount = 0;
    string result;
    for (int i = 0; i < (1 << N); i++) {
        string config = "";
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                config += '1';
            } else {
                config += '0';
            }
        }

        if (checkConfiguration(config)) {
            if (possibleCount == 0) {
                result = config;
            }
            possibleCount++;
        }
    }

    if (possibleCount == 0) {
        cout << "IMPOSSIBLE" << endl;
    } else if (possibleCount > 1) {
        cout << "NOT UNIQUE" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
