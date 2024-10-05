#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main() {
    int u, v;
    cin >> u >> v;

    string A, B;
    cin >> A >> B;

    int N = A.size();

    if (N >= 22) {
        // 진법이 다르면 비교하거나, 동일 진법이면 문자열을 직접 비교
        if (u > v) {
            cout << "ras" << endl;
        } else if (u < v) {
            cout << "auq" << endl;
        } else {
            if (A > B) {
                cout << "ras" << endl;
            } else if (A < B) {
                cout << "auq" << endl;
            } else {
                cout << "rasauq" << endl;
            }
        }
    } else {
        // 진법 변환 후 숫자로 비교
        auto convert_to_decimal = [](const string &num, int base) {
            long long result = 0;
            for (char c : num) {
                result = result * base + (c - '0');
            }
            return result;
        };

        long long a = convert_to_decimal(A, u);
        long long b = convert_to_decimal(B, v);

        if (a > b) {
            cout << "ras" << endl;
        } else if (a < b) {
            cout << "auq" << endl;
        } else {
            cout << "rasauq" << endl;
        }
    }

    return 0;
}
