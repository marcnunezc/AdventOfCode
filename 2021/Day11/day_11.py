
def pretty_print(matrix):
    for line in matrix:
        print("".join([str(value) if value < 10 else '\033[95m'+str(value)+'\033[0m' for value in line]))
    print("")

def find_flashed(matrix):
    flashed = set()
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] > 9:
                flashed.add((i,j))
                matrix[i][j] = -1
    return flashed, matrix

def increase_neighbours(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            for m,n in [(i-1,j),(i+1,j),(i,j-1),(i,j+1), (i-1,j-1),(i+1,j-1),(i-1,j+1),(i+1,j+1)]:
                if 0 <= m < len(matrix) and 0 <= n < len(matrix[i]):
                    if matrix[m][n] == -1 and  matrix[i][j] > 0:
                        matrix[i][j] += 1
    return matrix

def reset_flashed(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] == -1:
                matrix[i][j] = 0
    return matrix

def count_flashes(matrix):
    count = 0
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if octo_matrix[i][j] == 0:
                count +=1
    return count

def advance_step(matrix):
    matrix = [[value+1 for value in line] for line in matrix]
    new_flashed, matrix = find_flashed(matrix)
    total_flashes = len(new_flashed)
    while len(new_flashed)>0:
        matrix = increase_neighbours(matrix)
        matrix = reset_flashed(matrix)
        new_flashed, matrix = find_flashed(matrix)
        total_flashes += len(new_flashed)
    matrix = reset_flashed(matrix)
    return matrix, total_flashes

if __name__ == "__main__":
    filename = "input.txt"
    octo_matrix = [[int(value) for value in line] for line in open(filename).read().splitlines()]
    steps = 100

    total_of_flashes = 0
    for step in range(steps):
        octo_matrix, step_flashes = advance_step(octo_matrix)
        total_of_flashes += step_flashes
    print("Part 1", total_of_flashes)


    octo_matrix = [[int(value) for value in line] for line in open(filename).read().splitlines()]
    step=0
    while not count_flashes(octo_matrix) == len(octo_matrix)*len(octo_matrix[0]):
        octo_matrix, _ = advance_step(octo_matrix)
        step += 1
    print("Part 2", step)
