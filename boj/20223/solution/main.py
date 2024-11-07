from collections import deque
import sys


def solve():
    import sys
    from collections import deque

    def input():
        return sys.stdin.read()

    data = input().split("\n")
    idx = 0
    r, c, k = map(int, data[idx].split())
    idx += 1
    grid = []
    positions = {}
    for i in range(r):
        line = data[idx].strip()
        grid.append(line)
        for j, ch in enumerate(line):
            if ch == "0":
                positions[0] = (i, j)
            elif ch.isdigit():
                num = int(ch)
                if 1 <= num <= k + 1:
                    positions[num] = (i, j)
        idx += 1
    # Check if all positions are found
    required = list(range(0, k + 2))
    for num in required:
        if num not in positions:
            print("impossible")
            return
    # Targets in order: 0,1,2,...,k, k+1
    targets = [positions[num] for num in range(0, k + 2)]
    # State: (x, y, v_x, v_y, target_idx)
    # target_idx starts at 1, meaning next target is targets[1]
    queue = deque()
    visited = set()
    start = targets[0]
    final = targets[-1]
    # Initialize: position, velocity, target_idx, steps
    queue.append((start[0], start[1], 0, 0, 1, 0))
    visited.add((start[0], start[1], 0, 0, 1))
    while queue:
        x, y, vx, vy, target_idx, steps = queue.popleft()
        # If target_idx > k+1, it means all targets have been visited
        if target_idx > k + 1:
            # Now, perform the final jump to come to a stop
            if x == final[0] and y == final[1] and vx == 0 and vy == 0:
                print(steps)
                return
            continue
        # If we've reached the current target, increment target_idx
        if (x, y) == targets[target_idx - 1]:
            if target_idx <= k + 1:
                target_idx += 1
        # Now, try all possible accelerations
        for ax in [-1, 0, 1]:
            for ay in [-1, 0, 1]:
                nvx = vx + ax
                nvy = vy + ay
                # Limit velocities to reasonable bounds
                if abs(nvx) > 50 or abs(nvy) > 50:
                    continue
                # Calculate new position
                # Corrected mapping: positive v_x moves north (decrease x)
                nx = x - nvx
                ny = y + nvy
                # Check bounds
                if 0 <= nx < r and 0 <= ny < c:
                    if grid[nx][ny] != "#":
                        # Determine new_target_idx
                        new_target_idx = target_idx
                        # If the new position is the current target
                        if (
                            new_target_idx <= k + 1
                            and (nx, ny) == targets[new_target_idx - 1]
                        ):
                            new_target_idx += 1
                        # If all targets have been visited, ensure we stop at safe area with zero velocity
                        if new_target_idx > k + 1:
                            if not (
                                nx == final[0]
                                and ny == final[1]
                                and nvx == 0
                                and nvy == 0
                            ):
                                # Only allow states where after all targets, we are moving towards stopping at safe area
                                # But to ensure the last jump is to come to a stop, allow states that can reach final with zero velocity
                                pass
                        state = (nx, ny, nvx, nvy, new_target_idx)
                        if state not in visited:
                            visited.add(state)
                            queue.append((nx, ny, nvx, nvy, new_target_idx, steps + 1))
    print("impossible")


solve()
