import sys
import math


def find_ith_binary(N, L, I):
    result = ""
    n = N
    l = L
    i = I
    for bit in range(N):
        if n == 0:
            break
        # If we set current bit to 0, how many numbers can we have with remaining bits
        count = 0
        for k in range(0, l + 1):
            if k > n - 1:
                break
            count += math.comb(n - 1, k)
        if i <= count:
            result += "0"
        else:
            result += "1"
            i -= count
            l -= 1
        n -= 1
    return result


def main():
    import sys

    input = sys.stdin.read
    N, L, I = map(int, input().split())
    binary_number = find_ith_binary(N, L, I)
    print(binary_number)


if __name__ == "__main__":
    main()
