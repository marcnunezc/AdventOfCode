file_lines = [line[:-1] for line in  open("input.txt").readlines()]

# def GetTrees(file_lines, delta_i, delta_j):
#     current_i = 0 
#     current_j = 0
#     n_trees = 0
#     while(current_i < len(file_lines)):
#         current_j = current_j % len(file_lines[0])
#         if file_lines[current_i][current_j] == '#':
#             n_trees += 1 
#         current_i += delta_i
#         current_j += delta_j
#     return n_trees

def GetTrees(file_lines, delta_i, delta_j):
    current_j = 0
    n_trees = 0
    for line in file_lines[::delta_i]:
        current_j = current_j % len(line)
        if line[current_j] == '#':
            n_trees += 1 
        current_j += delta_j
    return n_trees

print("Number of trees", GetTrees(file_lines, 1, 3))

slopes = [
          [1,1],
          [1,3],
          [1,5],
          [1,7],
          [2,1]
          ]

multiplication = 1.0

for slope in slopes:
    multiplication *= GetTrees(file_lines, slope[0], slope[1])
print("Multiplication", multiplication)