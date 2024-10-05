N, M, X = map(int, input().split())
A, B, S, T = zip(*[tuple(map(int, input().split())) for _ in range(M)])

event = sorted([(S[i], 1, i) for i in range(M)] + [(T[i], 0, i) for i in range(M)])

ans = [0] * M
ans[0] = X

station = [0] * (N + 1)
for t, f, i in event:
    if f:
        # Departure: departs after the latest train arriving at station A[i] arrives (except for train 1)
        if i:
            ans[i] = max(0, station[A[i]] - t)
    else:
        # Arrival: update the latest train arriving at station B[i]
        station[B[i]] = max(station[B[i]], t + ans[i])

print(*ans[1:])
