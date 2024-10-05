import sys


def solve():
    import sys
    import sys

    def input():
        return sys.stdin.read()

    data = input().split()
    ptr = 0

    N = int(data[ptr])
    ptr += 1

    # Initialize A with 0 padding for 1-based indexing
    A = [[[0] * (N + 1) for _ in range(N + 1)] for __ in range(N + 1)]

    for x in range(1, N + 1):
        for y in range(1, N + 1):
            for z in range(1, N + 1):
                A[x][y][z] = int(data[ptr])
                ptr += 1

    # Compute 3D prefix sums
    P = [[[0] * (N + 1) for _ in range(N + 1)] for __ in range(N + 1)]

    for x in range(1, N + 1):
        for y in range(1, N + 1):
            for z in range(1, N + 1):
                P[x][y][z] = (
                    A[x][y][z]
                    + P[x - 1][y][z]
                    + P[x][y - 1][z]
                    + P[x][y][z - 1]
                    - P[x - 1][y - 1][z]
                    - P[x - 1][y][z - 1]
                    - P[x][y - 1][z - 1]
                    + P[x - 1][y - 1][z - 1]
                )

    Q = int(data[ptr])
    ptr += 1

    results = []
    for _ in range(Q):
        Lx = int(data[ptr])
        ptr += 1
        Rx = int(data[ptr])
        ptr += 1
        Ly = int(data[ptr])
        ptr += 1
        Ry = int(data[ptr])
        ptr += 1
        Lz = int(data[ptr])
        ptr += 1
        Rz = int(data[ptr])
        ptr += 1

        # Handle cases where Lx, Ly, Lz are 1 to avoid negative indices
        sum_val = P[Rx][Ry][Rz]
        if Lx > 1:
            sum_val -= P[Lx - 1][Ry][Rz]
        if Ly > 1:
            sum_val -= P[Rx][Ly - 1][Rz]
        if Lz > 1:
            sum_val -= P[Rx][Ry][Lz - 1]
        if Lx > 1 and Ly > 1:
            sum_val += P[Lx - 1][Ly - 1][Rz]
        if Lx > 1 and Lz > 1:
            sum_val += P[Lx - 1][Ry][Lz - 1]
        if Ly > 1 and Lz > 1:
            sum_val += P[Rx][Ly - 1][Lz - 1]
        if Lx > 1 and Ly > 1 and Lz > 1:
            sum_val -= P[Lx - 1][Ly - 1][Lz - 1]

        results.append(str(sum_val))

    print("\n".join(results))


solve()
