risk_matrix = [[int(char) for char in line] for line in open('test.txt').read().splitlines()]
risk_level = 0
def pretty_print(matrix, current_path=[]):
    for i, line in enumerate(matrix):
        for j, value in enumerate(line):
            if (value, i, j) in current_path:
                print('*', end='')
            else:
                print(value, end='')
        print()
def compute_score(starting_position, matrix):
    score = {(i,j):1e6 if not (i==0 and j == 0) else 0 for i in range(len(matrix)) for j in range(len(matrix[i]))}
    visited = set()
    current_node = starting_position
    while not current_node == (len(matrix)-1, len(matrix[0])-1):
        i, j = current_node
        if i % 99 == 0 and j % 99 == 0:
            print(current_node)
        neighbors = [(matrix[m][n], m, n) for m,n in [(i-1,j),(i+1,j),(i,j-1),(i,j+1)] \
                    if 0 <= m < len(matrix) and 0 <= n < len(matrix[i]) \
                    and not current_node in visited]
        for neighbor in neighbors:
            neigh_value, n_i, n_j = neighbor
            distance = score[current_node] + neigh_value
            if distance < score[(n_i,n_j)]:
                score[(n_i,n_j)] = distance
        visited.add(current_node)
        current_node = min(score.items(), key=lambda x: x[1] if not x[0] in visited else 1e6)[0]
    return score
score = compute_score((0,0), risk_matrix)
print("Part 1", score[(len(risk_matrix)-1, len(risk_matrix[0])-1)])
new_risk_matrix = [[0 for _ in range(len(risk_matrix[0])*5)] for i in range(len(risk_matrix)*5)]

for i in range(len(new_risk_matrix)):
    for j in range(len(new_risk_matrix)):
        new_risk_matrix[i][j] = risk_matrix[i % len(risk_matrix)][j % len(risk_matrix[0])] + (j // len(risk_matrix[0])) + (i // len(risk_matrix[0]))
        if new_risk_matrix[i][j] > 9:
            new_risk_matrix[i][j] = new_risk_matrix[i][j] - 9

print("Part 2", compute_score((0,0), new_risk_matrix)[(len(new_risk_matrix)-1, len(new_risk_matrix[0])-1)])

