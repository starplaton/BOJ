def solve():
    import sys

    input = sys.stdin.readline

    # 1) 문자 구분자 개수
    N = int(input().strip())
    # 2) 문자 구분자들
    char_delims = input().split()  # 예: ['a', 'b', 'c', ...]

    # 3) 숫자 구분자 개수
    M = int(input().strip())
    # 4) 숫자 구분자들
    num_delims = input().split()  # 예: ['1', '3', '9', ...]

    # 5) 병합자 개수
    K = int(input().strip())
    # 6) 병합자들
    merges = input().split()  # 예: ['a', '1', ...]

    # 7) 문자열 길이 (문제에서는 사용하지 않아도 무방)
    S = int(input().strip())

    # 8) 실제 기준 문자열
    line = input().rstrip("\n")

    # -------------------------
    # 병합자는 '구분자로 취급하지 않는다'고 했으므로,
    # 구분자 세트에서 병합자에 해당하는 부분을 제외해야 한다.
    # 공백(' ')은 문제에서 무조건 구분자로 취급된다고 했으므로
    # 병합자에 공백이 주어지지 않는다는 점(문제 조건)을 이용한다.
    # -------------------------
    set_merges = set(merges)

    # 최종적으로 사용할 구분자 집합
    # (단, 병합자에 해당하는 것들은 제거)
    set_char_delims = set(ch for ch in char_delims if ch not in set_merges)
    set_num_delims = set(ch for ch in num_delims if ch not in set_merges)

    # 이제 ' '(공백) 또는 위에서 정한 char_delims, num_delims에 속하는 글자를 만나면
    # 토큰을 끊어주고, 그렇지 않다면 같은 토큰에 이어붙인다.

    result = []
    current_token = []

    for ch in line:
        # 1) ch가 병합자이면, 무조건 구분자가 아니다.
        if ch in set_merges:
            current_token.append(ch)
        # 2) ch가 공백이거나 char_delims 혹은 num_delims에 속해 있으면 → 구분자
        elif ch == " " or ch in set_char_delims or ch in set_num_delims:
            # 지금까지 모았던 토큰이 비어있지 않다면 결과에 추가
            if current_token:
                result.append("".join(current_token))
                current_token.clear()
            # 구분자를 만나면 해당 구분자는 버리고 넘어간다(토큰에 추가 안 함)
        else:
            # 구분자가 아니면 토큰에 추가
            current_token.append(ch)

    # 마지막에 남아 있는 토큰이 있으면 결과에 추가
    if current_token:
        result.append("".join(current_token))

    # 문제에서 "빈 문자열로 결과가 주어지는 경우는 없다" 라고 했지만
    # 혹시 모를 상황에 대비해 빈 문자열은 거른다.
    for token in result:
        if token:
            print(token)


if __name__ == "__main__":
    solve()
