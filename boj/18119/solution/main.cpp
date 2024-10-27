#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    // 자음 별로 단어의 인덱스를 저장하는 벡터
    vector<vector<int>> consonant_to_words(26, vector<int>());

    // 각 단어가 잊어버린 자음의 수
    vector<int> forgotten_count(N, 0);
    int total_known = N;

    // 모음
    vector<bool> is_vowel(26, false);
    is_vowel['a' - 'a'] = is_vowel['e' - 'a'] = is_vowel['i' - 'a'] = is_vowel['o' - 'a'] = is_vowel['u' - 'a'] = true;

    // 단어 처리
    for (int word_idx = 0; word_idx < N; ++word_idx) {
        string word;
        cin >> word;
        unordered_set<int> unique_consonants;
        for (char c : word) {
            if (!is_vowel[c - 'a']) {
                unique_consonants.insert(c - 'a');
            }
        }
        for (auto c : unique_consonants) {
            consonant_to_words[c].push_back(word_idx);
        }
    }

    // 쿼리 처리
    for (int q = 0; q < M; ++q) {
        int o;
        char x;
        cin >> o >> x;
        if (is_vowel[x - 'a']) {
            // 모음은 무시
            cout << total_known << "\n";
            continue;
        }
        int c = x - 'a';
        if (o == 1) {
            // 잊는 경우
            for (auto &word : consonant_to_words[c]) {
                if (forgotten_count[word] == 0) {
                    forgotten_count[word]++;
                    total_known--;
                } else {
                    forgotten_count[word]++;
                }
            }
        } else {
            // 기억해내는 경우
            for (auto &word : consonant_to_words[c]) {
                if (forgotten_count[word] == 1) {
                    forgotten_count[word]--;
                    total_known++;
                } else {
                    forgotten_count[word]--;
                }
            }
        }
        cout << total_known << "\n";
    }
}
