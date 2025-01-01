#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 1000;

// '모든 d'에 대해 '길이 n'짜리 bitset을 준비.
// isMultiple[d][i] = ( i+1 가 d의 배수인가? )  (i는 0부터, 실제 인덱스+1이 숫자)
bitset<MAXN> isMultiple[1001];  // d가 1~1000이므로 크기 1001

// s가 전부 숫자인지?
bool isAllDigits(const string &s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

// s가 전부 알파벳 소문자인지?
bool isLowerAlpha(const string &s) {
    for (char c : s)
        if (c < 'a' || c > 'z') return false;
    return true;
}

// s가 i를 (leading zero 없이) 정확히 나타내는지?
bool isPureNumber(int i, const string &s) {
    // 1) 숫자만으로 구성?
    if (!isAllDigits(s)) return false;
    // 2) 맨 앞 '0'이고 길이가 1보다 크면 X
    if (s.size() > 1 && s[0] == '0') return false;
    // 3) stoi(s) == i ?
    return (stoi(s) == i);
}

int checkK0(const vector<string> &L) {
    int n = (int)L.size();
    for (int i = 1; i <= n; i++) {
        if (!isPureNumber(i, L[i - 1])) {
            return i - 1;
        }
    }
    return n;
}

int checkK1(const vector<string> &L) {
    int n = (int)L.size();
    // possibleD[d] = true면 "d" 가능
    vector<bool> possibleD(n + 1, true);
    // s1이 아직 결정 안됐으면 "", 결정 후에는 바뀌지 않음
    string s1 = "";

    // d=0은 무효
    possibleD[0] = false;

    for (int i = 1; i <= n; i++) {
        const string &token = L[i - 1];
        bool isNum = isPureNumber(i, token);
        bool isFourAlpha = (token.size() == 4 && isLowerAlpha(token));

        // 숫자도 아니고 4알파벳도 아니면 즉시 끝
        if (!isNum && !isFourAlpha) {
            return i - 1;
        }

        // 이번 i에서 가능성 제거
        for (int d = 1; d <= n; d++) {
            if (!possibleD[d]) continue;

            if (isNum) {
                // i가 d 배수면 안 됨
                if (isMultiple[d][i - 1]) {
                    possibleD[d] = false;
                }
            } else {
                // 4글자 => i는 d의 배수여야 함
                if (!isMultiple[d][i - 1]) {
                    possibleD[d] = false;
                } else {
                    // s1이 아직 미정이면 이번에 정함
                    if (s1.empty()) {
                        s1 = token;
                    }
                    // 이미 정했는데 다르면 모순
                    else if (s1 != token) {
                        possibleD[d] = false;
                    }
                }
            }
        }

        // 이번 i 처리 후 가능한 d가 없다면 i-1
        if (!any_of(possibleD.begin() + 1, possibleD.end(), [](bool b) { return b; })) {
            return i - 1;
        }
    }
    // 여기 도달했으면 끝까지 가능
    return n;
}

// k=2용 구조체
struct Info {
    int d1, d2;
    bool valid;
    string s1, s2;  // 길이 4짜리 혹은 ""(미정)
};

int checkK2(const vector<string> &L) {
    int n = (int)L.size();
    // (d1,d2) 후보를 전부 생성
    // 최대 (1000*999)/2 = 499500 개
    // bitset 사용으로 % 연산을 대폭 줄여 성능을 끌어올린다.
    vector<Info> candidates;
    candidates.reserve(n * (n - 1) / 2);

    for (int d1 = 1; d1 <= n; d1++) {
        for (int d2 = d1 + 1; d2 <= n; d2++) {
            Info obj;
            obj.d1 = d1;
            obj.d2 = d2;
            obj.valid = true;
            obj.s1 = "";
            obj.s2 = "";
            candidates.push_back(obj);
        }
    }

    // i=1..n
    for (int i = 1; i <= n; i++) {
        const string &token = L[i - 1];

        bool isNum = isPureNumber(i, token);
        bool is4 = (token.size() == 4 && isLowerAlpha(token));
        bool is8 = (token.size() == 8 && isLowerAlpha(token));

        // 이도저도 아니면 i-1에서 끝
        if (!isNum && !is4 && !is8) {
            return i - 1;
        }

        int aliveCount = 0;
        for (auto &c : candidates) {
            if (!c.valid) continue;

            bool mul1 = isMultiple[c.d1][i - 1];
            bool mul2 = isMultiple[c.d2][i - 1];

            if (!mul1 && !mul2) {
                // 숫자여야
                if (!isNum) {
                    c.valid = false;
                }
            } else if (mul1 && !mul2) {
                // s1(4글자)
                if (!is4) {
                    c.valid = false;
                } else {
                    // s1이 미정이면 지금 정함
                    if (c.s1.empty()) {
                        c.s1 = token;
                    } else if (c.s1 != token) {
                        c.valid = false;
                    }
                }
            } else if (!mul1 && mul2) {
                // s2(4글자)
                if (!is4) {
                    c.valid = false;
                } else {
                    if (c.s2.empty()) {
                        c.s2 = token;
                    } else if (c.s2 != token) {
                        c.valid = false;
                    }
                }
            } else {
                // mul1 && mul2 => s1+s2(8글자)
                if (!is8) {
                    c.valid = false;
                } else {
                    // token[0..3] vs s1, token[4..7] vs s2
                    string left4 = token.substr(0, 4);
                    string right4 = token.substr(4, 4);

                    // s1, s2 각각 미정인지 체크
                    if (c.s1.empty() && c.s2.empty()) {
                        c.s1 = left4;
                        c.s2 = right4;
                    } else if (c.s1.empty() && !c.s2.empty()) {
                        if (c.s2 != right4) {
                            c.valid = false;
                        } else {
                            c.s1 = left4;
                        }
                    } else if (!c.s1.empty() && c.s2.empty()) {
                        if (c.s1 != left4) {
                            c.valid = false;
                        } else {
                            c.s2 = right4;
                        }
                    } else {
                        // 둘 다 정해졌으면 둘 다 맞아야
                        if (c.s1 != left4 || c.s2 != right4) {
                            c.valid = false;
                        }
                    }
                }
            }

            if (c.valid) {
                aliveCount++;
            }
        }

        // 남은 후보가 없으면 i-1
        if (aliveCount == 0) {
            return i - 1;
        }
    }
    // 끝까지 가능
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // isMultiple[d][i] 미리 채우기
    // i는 0-based, 실제 값은 i+1
    // d가 (i+1)의 약수인지?
    for (int d = 1; d <= 1000; d++) {
        for (int i = 0; i < 1000; i++) {
            int val = i + 1;
            if (val % d == 0) {
                isMultiple[d].set(i, true);
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        if (cin.peek() == '\n') cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int n;
        cin >> n;
        vector<string> L(n);
        for (int i = 0; i < n; i++) {
            cin >> L[i];
        }

        // k=0,1,2 각각 체크
        int ans0 = checkK0(L);
        int ans1 = checkK1(L);
        int ans2 = checkK2(L);

        cout << max({ans0, ans1, ans2}) << "\n";
    }
    return 0;
}
