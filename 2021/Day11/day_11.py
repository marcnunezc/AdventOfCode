
def pretty_print(matrix):
    for line in matrix:
        print("".join([str(value) if value < 10 else '\033[95m'+str(value)+'\033[0m' for value in line]))
    print("")

def mark_to_flash(matrix):
    return [[-1 if matrix[i][j] > 9 else matrix[i][j] for j in range(len(matrix[i]))] for i in range(len(matrix))]

def increase_neighbours(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] > 0:
                all_neighbours = [(i-1,j),(i+1,j),(i,j-1),(i,j+1), (i-1,j-1),(i+1,j-1),(i-1,j+1),(i+1,j+1)]
                neighbours = [(m,n) for m,n in all_neighbours if 0 <= m < len(matrix) and 0 <= n < len(matrix[i])]
                for m,n in neighbours:
                    if matrix[m][n] == -1:
                        matrix[i][j] += 1
    return matrix

def count_marked(matrix):
    return sum([sum([matrix[i][j] == -1 for j in range(len(matrix[i]))]) for i in range(len(matrix))])

def reset_flashed(matrix):
    return [[0 if matrix[i][j] == -1 else matrix[i][j] for j in range(len(matrix[i]))] for i in range(len(matrix))]

def count_flashes(matrix):
    return sum([sum([matrix[i][j] == 0 for j in range(len(matrix[i]))]) for i in range(len(matrix))])

def advance_step(matrix):
    matrix = [[value+1 for value in line] for line in matrix]
    matrix = mark_to_flash(matrix)
    marked_octopus = count_marked(matrix)
    while marked_octopus>0:
        matrix = mark_to_flash(reset_flashed(increase_neighbours(matrix)))
        marked_octopus = count_marked(matrix)
    matrix = reset_flashed(matrix)
    return matrix

if __name__ == "__main__":
    filename = "input.txt"
    octo_matrix = [[int(value) for value in line] for line in open(filename).read().splitlines()]
    steps = 100

    total_of_flashes = 0
    for step in range(steps):
        octo_matrix = advance_step(octo_matrix)
        total_of_flashes += count_flashes(octo_matrix)
    print("Part 1", total_of_flashes)


    octo_matrix = [[int(value) for value in line] for line in open(filename).read().splitlines()]
    step=0
    while not count_flashes(octo_matrix) == len(octo_matrix)*len(octo_matrix[0]):
        octo_matrix = advance_step(octo_matrix)
        step += 1
    print("Part 2", step)
