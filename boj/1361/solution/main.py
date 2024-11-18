def split_star(s):
    """문자열을 '*' 기준으로 분리하여 앞부분과 뒷부분을 반환"""
    idx = s.find("*")
    return s[:idx], s[idx + 1 :]


def get_superstring(s1, s2):
    """두 문자열의 최소 공통 슈퍼스트링을 반환"""
    # 한 문자열이 다른 문자열의 접두사인 경우
    if s1.startswith(s2):
        return s1
    if s2.startswith(s1):
        return s2

    # s1의 접미사와 s2의 접두사가 겹치는 최대 k 찾기
    max_k = min(len(s1), len(s2))
    for k in range(max_k, 0, -1):
        if s1[-k:] == s2[:k]:
            return s1 + s2[k:]

    # s2의 접미사와 s1의 접두사가 겹치는 최대 k 찾기
    for k in range(max_k, 0, -1):
        if s2[-k:] == s1[:k]:
            return s2 + s1[k:]

    # 겹침이 없으면 단순히 두 문자열을 이어붙임
    return s1 + s2


def solve(S1, S2):
    A1, B1 = split_star(S1)
    A2, B2 = split_star(S2)

    P = get_superstring(A1, A2)
    Q = get_superstring(B1, B2)

    candidates = set()
    max_k = min(len(P), len(Q))

    for k in range(max_k, -1, -1):
        if k == 0 or P[-k:] == Q[:k]:
            S = P + Q[k:]

            # S1: A1 + R1 + B1 = S
            if len(S) < len(A1) + len(B1):
                continue
            R1 = S[len(A1) : len(S) - len(B1)] if len(S) - len(B1) >= len(A1) else ""
            S1_prime = A1 + R1 + B1

            # S2: A2 + R2 + B2 = S
            if len(S) < len(A2) + len(B2):
                continue
            R2 = S[len(A2) : len(S) - len(B2)] if len(S) - len(B2) >= len(A2) else ""
            S2_prime = A2 + R2 + B2

            if S1_prime == S and S2_prime == S:
                candidates.add(S)

    if not candidates:
        return -1
    else:
        # 최소 길이의 문자열을 반환
        return min(candidates, key=lambda x: len(x))


# 입력 받기
import sys


def main():
    S1 = sys.stdin.readline().strip()
    S2 = sys.stdin.readline().strip()

    result = solve(S1, S2)
    print(result)


if __name__ == "__main__":
    main()
