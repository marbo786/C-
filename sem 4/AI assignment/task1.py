import heapq

def get_heuristic(pos, goal):
    return abs(pos[0] - goal[0]) + abs(pos[1] - goal[1])

def a_star(grid, start, goal):
    num_rows, num_cols = len(grid), len(grid[0])
    pq = []
    heapq.heappush(pq, (get_heuristic(start, goal), start))
    
    parent_map = {}
    g_costs = {start: 0}
    nodes_visited = 0

    while pq:
        current_f, current_pos = heapq.heappop(pq)
        nodes_visited += 1

        if current_pos == goal:
            return rebuild_path(parent_map, goal), g_costs[goal], nodes_visited

        r, c = current_pos
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            neighbor = (r + dr, c + dc)

            if 0 <= neighbor[0] < num_rows and 0 <= neighbor[1] < num_cols:
                if grid[neighbor[0]][neighbor[1]] == 1:
                    continue
                
                new_g = g_costs[current_pos] + 1
                
                if neighbor not in g_costs or new_g < g_costs[neighbor]:
                    parent_map[neighbor] = current_pos
                    g_costs[neighbor] = new_g
                    f_score = new_g + get_heuristic(neighbor, goal)
                    heapq.heappush(pq, (f_score, neighbor))

    return None, None, nodes_visited

def rebuild_path(parents, current):
    path = [current]
    while current in parents:
        current = parents[current]
        path.append(current)
    return path[::-1]

def display_grid(grid, path):
    path_coords = set(path) if path else set()
    for r in range(len(grid)):
        row = []
        for c in range(len(grid[0])):
            if (r, c) in path_coords: row.append("*")
            elif grid[r][c] == 1: row.append("#")
            else: row.append(".")
        print(" ".join(row))

grid = [
    [0,0,0,0,1,0,0,0],
    [0,1,1,0,1,0,1,0],
    [0,0,0,0,0,0,1,0],
    [0,1,0,1,1,0,0,0],
    [0,1,0,0,0,1,1,0],
    [0,0,0,1,0,0,0,0],
    [1,1,0,1,0,1,0,1],
    [0,0,0,0,0,0,0,0]
]

start, goal = (0, 0), (7, 7)
path, cost, count = a_star(grid, start, goal)

if path:
    print(f"Path: {path}")
    print(f"Cost: {cost}")
    print(f"Nodes Expanded: {count}")
    display_grid(grid, path)
else:
    print("No path found.")