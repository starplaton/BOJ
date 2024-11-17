import sys
import sys
import sys

sys.setrecursionlimit(1 << 25)


def main():
    import sys
    from functools import lru_cache

    N, A, B = map(int, sys.stdin.readline().split())
    required_bits = set()
    for _ in range(N):
        bit = int(sys.stdin.readline())
        required_bits.add(bit)

    # Precompute min_sum and max_sum for each bit position
    max_bit = 30  # Since bits are up to 30
    min_sum = [0] * (max_bit + 2)
    max_sum_val = [0] * (max_bit + 2)

    # For min_sum: sum of required bits from current to highest
    # For max_sum: sum of all bits from current to highest
    for i in range(max_bit, -1, -1):
        if i in required_bits:
            min_sum[i] = min_sum[i + 1] + (1 << i)
        else:
            min_sum[i] = min_sum[i + 1]
        max_sum_val[i] = max_sum_val[i + 1] + (1 << i)

    # Convert B to binary representation
    bits_B = []
    temp = B
    for i in range(max_bit, -1, -1):
        bits_B.append((B >> i) & 1)

    @lru_cache(maxsize=None)
    def dp(pos, remainder, tight):
        if pos == max_bit + 1:
            return 1 if remainder == 0 else 0
        # Calculate the maximum bit we can set at this position
        limit = bits_B[pos] if tight else 1
        total = 0
        for bit in range(0, limit + 1):
            # If this bit must be set
            if pos in required_bits and bit == 0:
                continue
            # If this bit is not required, it can be either 0 or 1
            new_tight = tight and (bit == limit)
            new_remainder = (remainder * 2 + bit) % A
            # Calculate the current sum based on bit
            current_sum = bit << (max_bit - pos)
            # Prune branches where sum + min_sum[pos+1] > B
            # Since we are processing bits from high to low, the current_sum is part of the sum
            # However, in this implementation, we have already considered the tightness
            # So pruning is implicitly handled
            total += dp(pos + 1, new_remainder, new_tight)
        return total

    # Adjust the bits_B list to match the positions
    bits_B = []
    for i in range(max_bit, -1, -1):
        bits_B.append((B >> i) & 1)

    @lru_cache(maxsize=None)
    def count(pos, remainder, tight):
        if pos == max_bit + 1:
            return 1 if remainder == 0 else 0
        limit = bits_B[pos] if tight else 1
        total = 0
        for bit in range(0, limit + 1):
            if pos in required_bits and bit == 0:
                continue
            new_tight = tight and (bit == limit)
            new_remainder = (remainder * 2 + bit) % A
            total += count(pos + 1, new_remainder, new_tight)
        return total

    # Number of bits to process
    num_bits = max_bit + 1

    # Adjust bits_B to match the position from 0 to max_bit
    bits_B = []
    for i in range(max_bit, -1, -1):
        bits_B.append((B >> i) & 1)

    # DP function
    from functools import lru_cache

    @lru_cache(maxsize=None)
    def G(now, sum_mod, tight):
        if now == num_bits:
            return 1 if sum_mod == 0 else 0
        total = 0
        current_bit = num_bits - now - 1
        max_bit_val = bits_B[now] if tight else 1
        for bit in range(0, max_bit_val + 1):
            # If this bit must be set
            if current_bit in required_bits and bit == 0:
                continue
            new_tight = tight and (bit == max_bit_val)
            new_sum_mod = (sum_mod * 2 + bit) % A
            # Prune if sum + min_sum[now] > B
            # In this implementation, tightness ensures sum <= B
            total += G(now + 1, new_sum_mod, new_tight)
        return total

    result = G(0, 0, True)
    # If N ==0 and 0 is counted, subtract 1
    if N == 0 and A != 0:
        if 0 >= 1 and 0 <= B and 0 % A == 0:
            result -= 1
    print(result)


if __name__ == "__main__":
    main()
