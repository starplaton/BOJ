import sys
from array import array


def main():
    import sys

    input = sys.stdin.read().split()
    ptr = 0

    N = int(input[ptr])
    M = int(input[ptr + 1])
    ptr += 2

    vowels = set(["a", "e", "i", "o", "u"])
    # 자음 별로 단어의 인덱스를 저장하는 리스트
    consonant_to_words = [[] for _ in range(26)]

    forgotten_count = array("B", [0] * N)  # 각 단어가 잊어버린 자음의 수
    total_known = N  # 현재 완전히 알고 있는 단어의 수

    for word_idx in range(N):
        word = input[ptr]
        ptr += 1
        unique_consonants = set()
        for c in word:
            if c not in vowels:
                unique_consonants.add(ord(c) - ord("a"))
        for c in unique_consonants:
            consonant_to_words[c].append(word_idx)

    for _ in range(M):
        o = input[ptr]
        x = input[ptr + 1]
        ptr += 2

        if x in vowels:
            # 모음은 절대 잊지 않으므로, 상태 변화 없음
            print(total_known)
            continue

        c = ord(x) - ord("a")

        words = consonant_to_words[c]
        if o == "1":
            # 잊는 경우
            for word in words:
                if forgotten_count[word] == 0:
                    forgotten_count[word] = 1
                    total_known -= 1
                else:
                    forgotten_count[word] += 1
        elif o == "2":
            # 기억해내는 경우
            for word in words:
                if forgotten_count[word] == 1:
                    forgotten_count[word] = 0
                    total_known += 1
                else:
                    forgotten_count[word] -= 1

        print(total_known)


if __name__ == "__main__":
    main()
