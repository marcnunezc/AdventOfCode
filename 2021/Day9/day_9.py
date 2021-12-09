import numpy as np
smoke_matrix = [[int(char) for char in line] for line in open('input.txt').read().splitlines()]
risk_level = 0
low_points = set()
for i in range(len(smoke_matrix)):
    for j in range(len(smoke_matrix[i])):
        current = smoke_matrix[i][j]
        if not any(smoke_matrix[m][n] <= current for m,n in [(i-1,j),(i+1,j),(i,j-1),(i,j+1)] \
                if 0 <= m < len(smoke_matrix) and 0 <= n < len(smoke_matrix[i])):
            risk_level += current + 1
            low_points.add((i,j))
print("Part 1", risk_level)

def search_basin(current, i, j, basin_path):
    neighbors = [(smoke_matrix[m][n], m, n) for m,n in [(i-1,j),(i+1,j),(i,j-1),(i,j+1)] \
                if 0 <= m < len(smoke_matrix) and 0 <= n < len(smoke_matrix[i]) \
                and smoke_matrix[m][n] > current and not smoke_matrix[m][n]==9]
    for neighbor in neighbors:
        basin_path.add((neighbor[0],neighbor[1], neighbor[2]))
        basin_path = search_basin(neighbor[0], neighbor[1], neighbor[2], basin_path)
    return basin_path

basins=[len(search_basin(smoke_matrix[i][j], i, j, {(smoke_matrix[i][j], i,j)})) for i,j in low_points]
print("Part 2",np.prod([basin for basin in reversed(sorted(basins))][0:3]))