#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<string> words(N);
    for (int i = 0; i < N; i++) cin >> words[i];

    // 알파벳 가중치를 저장할 배열
    ll alpha_weight[26] = {0};

    // 각 단어에서 알파벳의 가중치를 계산
    for (auto &word : words) {
        int len = word.length();
        for (int i = 0; i < len; i++) {
            char c = word[i];
            alpha_weight[c - 'A'] += pow(10, len - i - 1);
        }
    }

    // 알파벳과 가중치를 벡터에 저장
    vector<pair<char, ll>> alpha_pairs;
    for (int i = 0; i < 26; i++) {
        if (alpha_weight[i] > 0) {
            alpha_pairs.emplace_back(make_pair('A' + i, alpha_weight[i]));
        }
    }

    // 가중치 기준으로 내림차순 정렬
    sort(alpha_pairs.begin(), alpha_pairs.end(), [&](pair<char, ll> a, pair<char, ll> b) -> bool {
        return a.second > b.second;
    });

    // 숫자 할당: 가장 큰 가중치를 가진 알파벳에 9부터 할당
    int digit = 9;
    unordered_map<char, int> alpha_digit_map;
    for (auto &p : alpha_pairs) {
        alpha_digit_map[p.first] = digit;
        digit--;
        if (digit < 0) break;  // 0까지 할당하면 종료
    }

    // 단어들을 숫자로 변환하여 합산
    ll total_sum = 0;
    for (auto &word : words) {
        ll num = 0;
        for (auto &c : word) {
            num = num * 10 + alpha_digit_map[c];
        }
        total_sum += num;
    }

    cout << total_sum;
}
