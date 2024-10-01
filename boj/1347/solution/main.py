def construct_maze(movement_length, movement_instructions):
    # Define direction vectors: North, East, South, West
    directions = ["N", "E", "S", "W"]
    dx = {"N": 0, "E": 1, "S": 0, "W": -1}
    dy = {"N": -1, "E": 0, "S": 1, "W": 0}

    # Initial position and direction
    x, y = 0, 0
    dir_idx = 2  # Starts facing South
    visited = set()
    visited.add((x, y))

    for move in movement_instructions:
        if move == "F":
            x += dx[directions[dir_idx]]
            y += dy[directions[dir_idx]]
            visited.add((x, y))
        elif move == "L":
            dir_idx = (dir_idx - 1) % 4
        elif move == "R":
            dir_idx = (dir_idx + 1) % 4
        # Ignoring invalid characters as per problem constraints

    # Determine maze boundaries
    min_x = min(pos[0] for pos in visited)
    max_x = max(pos[0] for pos in visited)
    min_y = min(pos[1] for pos in visited)
    max_y = max(pos[1] for pos in visited)

    # Construct maze grid
    maze_rows = []
    for y_coord in range(min_y, max_y + 1):
        row = ""
        for x_coord in range(min_x, max_x + 1):
            if (x_coord, y_coord) in visited:
                row += "."
            else:
                row += "#"
        maze_rows.append(row)

    return maze_rows


movement_length_5 = int(input())
movement_instructions_5 = input().strip()
maze_5 = construct_maze(movement_length_5, movement_instructions_5)
print("\n".join(maze_5))
