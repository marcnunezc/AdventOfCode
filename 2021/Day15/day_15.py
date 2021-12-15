def compute_score(max_i, max_j, evaluate_risk):
    score = {(i,j):1e6 if not (i==0 and j == 0) else 0 for i in range(max_i) for j in range(max_j)}
    visited = set()
    visited_neighs = set()
    current_node = (0,0)
    while not current_node == (max_i-1, max_j-1):
        i, j = current_node

        ini_time = time.time()
        neighbors = [(evaluate_risk(m,n), m, n) for m,n in [(i-1,j),(i+1,j),(i,j-1),(i,j+1)] \
                    if 0 <= m < max_i and 0 <= n < max_j  \
                        and not (m,n) in visited]
        for neighbor in neighbors:
            neigh_value, n_i, n_j = neighbor
            distance = score[current_node] + neigh_value
            if distance < score[(n_i,n_j)]:
                score[(n_i,n_j)] = distance
            visited_neighs.add((n_i,n_j))
        visited.add(current_node)
        if current_node in visited_neighs:
            visited_neighs.remove(current_node)
        current_node = min(visited_neighs, key=lambda x: score[x])
    return score

def evaluate_risk_1(i,j):
    return risk_matrix[i][j]

def evaluate_risk_2(i,j):
    value = risk_matrix[i % len(risk_matrix)][j % len(risk_matrix[0])] + (j // len(risk_matrix[0])) + (i // len(risk_matrix[0]))
    if value > 9:
        value = value - 9
    return value

if __name__ == '__main__':
    import time

    risk_matrix = [[int(char) for char in line] for line in open('input.txt').read().splitlines()]
    max_i, max_j = len(risk_matrix), len(risk_matrix[0])

    score = compute_score(max_i, max_j, evaluate_risk_1)
    print("Part 1", score[max_i-1, max_j-1])

    ini_time = time.perf_counter()
    score = compute_score(max_i*5, max_j*5, evaluate_risk_2)
    print("Part 2", score[max_i*5-1, max_j*5-1])
    print("Time:", time.perf_counter() - ini_time)