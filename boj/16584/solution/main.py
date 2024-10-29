import sys


def main():
    import sys

    input = sys.stdin.read
    data = input().split()

    K = int(data[0])
    S = data[1]
    N = len(S)

    dp = [float("inf")] * (N + 1)
    dp[0] = 0

    # Log: 초기 상태
    print(f"초기 상태: K = {K}, S = {S}, N = {N}")
    print(f"초기 DP 테이블: {dp}")

    for idx, bit in enumerate(S):
        bit_val = int(bit)
        # Log: 현재 비트 정보
        print(f"\n비트 인덱스: {idx}, 비트 값: {bit_val}")

        for j in range(min(idx + 1, N), -1, -1):
            if j == 0 and bit_val == 0:
                # Log: 첫 비트를 0으로 설정할 수 없어서 건너뜀
                print(
                    f"  j = {j}, bit_val = {bit_val}, 첫 비트를 0으로 설정할 수 없어서 건너뜀"
                )
                continue
            if j == 1 and bit_val == 0:
                # Log: 첫 선택 비트는 반드시 '1'이어야 함
                print(
                    f"  j = {j}, bit_val = {bit_val}, 첫 선택 비트는 반드시 '1'이어야 함"
                )
                continue
            if j > 0 and dp[j - 1] != float("inf"):
                new_val = dp[j - 1] * 2 + bit_val
                if new_val <= K and new_val < dp[j]:
                    dp[j] = new_val
                    # Log: DP 테이블 업데이트
                    print(f"  DP 업데이트: dp[{j}] = {new_val}")

    # Log: 최종 DP 테이블
    print(f"\n최종 DP 테이블: {dp}")

    max_j = -1
    for j in range(N, 0, -1):
        if dp[j] <= K:
            max_j = j
            break

    if max_j == -1:
        print(-1)
    else:
        bits_removed = N - max_j
        print(bits_removed)

    # Log: 최종 결과
    print(
        f"최대 j 값: {max_j}, 제거된 비트 수: {bits_removed if max_j != -1 else 'N/A'}"
    )


if __name__ == "__main__":
    main()
