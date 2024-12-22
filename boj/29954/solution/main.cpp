#include <bits/stdc++.h>
using namespace std;

/*
 * 문제 요약:
 * 주어진 N개의 소문자 문자열 S_i를 모두 subsequence(부분수열)로 포함하는
 * 가능한 한 짧은 문자열을 만드는 문제.
 *
 * subsequence(부분수열)이란, 문자열에서 몇 개의 문자를 삭제해서 얻을 수 있는 문자열을 의미.
 *
 * 본 문제는 실제로 매우 어려운 최적화 문제이며(일반적으로 NP-hard),
 * 모든 문자열을 부분수열로 포함하는 가장 짧은 문자열(Shortest Common Supersequence, SCS)을 찾는 것은
 * 문자열의 수가 많을 경우나 길이가 길 경우 매우 복잡해진다.
 *
 * 여기서는 예제 코드로, 주어진 문자열들을 순차적으로 두 개씩 합쳐가며
 * 두 문자열에 대한 Shortest Common Supersequence를 구하고,
 * 그 결과를 다음 문자열과 다시 SCS를 구하는 식으로 처리하는 방법을 구현한다.
 *
 * 이 방법은 N개의 문자열에 대해:
 * - 첫 번째 문자열과 두 번째 문자열의 SCS를 구한다.
 * - 그 결과와 세 번째 문자열의 SCS를 구한다.
 * - 이를 N개에 대해 반복.
 *
 * 이 접근은 최적해를 보장하지 않을 수 있으나, 하나의 풀이 예시로 제시한다.
 *
 * DP를 이용한 두 문자열의 SCS 구하기:
 * 두 문자열 A, B가 있을 때,
 * dp[i][j]: A의 첫 i글자와 B의 첫 j글자에 대한 SCS의 길이를 저장.
 *
 * 점화식:
 * - A[i] == B[j]인 경우: dp[i][j] = dp[i-1][j-1] + 1
 * - A[i] != B[j]인 경우: dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1
 *
 * 이를 이용해 길이를 구한 뒤, 역추적을 통해 실제 SCS 문자열을 복원.
 *
 * 복원 과정:
 * - dp테이블을 모두 채운 뒤, (nA, nB)에서부터 시작한다.
 * - A[i-1] == B[j-1]이면 그 문자를 결과에 추가하고 i--, j--
 * - 다르면 dp값이 작아지는 방향으로 이동하며 해당 문자를 결과에 추가.
 *
 * 이 과정을 통해 두 문자열의 SCS를 구한 후, 이를 이용해 N개의 문자열에 대해 순차적으로 SCS를 구한다.
 */

string SCS(string &A, string &B) {
    int n = (int)A.size();
    int m = (int)B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) dp[i][0] = i;
    for (int j = 1; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            }
        }
    }

    // 역추적
    int i = n, j = m;
    string result;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            result.push_back(A[i - 1]);
            i--;
            j--;
        } else {
            if (dp[i - 1][j] < dp[i][j - 1]) {
                result.push_back(A[i - 1]);
                i--;
            } else {
                result.push_back(B[j - 1]);
                j--;
            }
        }
    }
    while (i > 0) {
        result.push_back(A[i - 1]);
        i--;
    }
    while (j > 0) {
        result.push_back(B[j - 1]);
        j--;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> planets(N);
    for (int i = 0; i < N; i++) cin >> planets[i];

    // 순차적으로 SCS를 구해나가며 모든 문자열을 포함하는 문자열 도출
    string current = planets[0];
    for (int i = 1; i < N; i++) {
        current = SCS(current, planets[i]);
    }

    cout << current << "\n";

    return 0;
}
