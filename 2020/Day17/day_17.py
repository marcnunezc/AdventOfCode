import math, copy

def get_current_z0(pocket):
    return len(pocket)//2
def increase_dimension(pocket):
    for z_slice in pocket:
        current_len = len(z_slice[0])
        for y_slice in z_slice:
            y_slice.insert(0,'.')
            y_slice.append('.')
        z_slice.insert(0, ['.' for _ in range(current_len+2)])
        z_slice.append(['.' for _ in range(current_len+2)])
    pocket.insert(0, [['.' for _ in range(current_len+2)] for _ in range(current_len+2)])
    pocket.append([['.' for _ in range(current_len+2)] for _ in range(current_len+2)])
    return pocket

def pretty_print_pocket(pocket):
    for z, z_slice in enumerate(pocket):
        print("Z = ", z - get_current_z0(pocket))
        for y_slice in z_slice:
            for x_slice in y_slice:
                print(x_slice, end="")
            print("")
        print("")
    print("#################")

def count_cubes(pocket):
    return sum([1 for z_slice in pocket for y_slice in z_slice for x_slice in y_slice if x_slice=="#"])

def check_if_surrounded(i, j, k, lines):
    is_surrounded_list = [check_occup(i+delta_i, j+delta_j, k+delta_k, lines) for delta_i in [-1,0,1] for delta_j in [-1,0,1] for delta_k in [-1,0,1] if not abs(delta_i)+abs(delta_j)+abs(delta_k)==0 and check_range(i+delta_i,j+delta_j,k+delta_k, lines)]
    return is_surrounded_list

check_occup = lambda  i,j,k,lines: lines[k][j][i] == "#"
check_range = lambda  i,j,k,lines: k in range(0, len(lines)) and j in range(0, len(lines[0])) and i in range(0, len(lines[0][0]))

def hyper_increase_dimension(pocket):
    current_len = len(pocket[0][0])
    current_z = len(pocket[0])
    for w_slice in pocket:
        increase_dimension(w_slice)
    pocket.insert(0, [[['.' for _ in range(current_len+2)] for _ in range(current_len+2)] for _ in range(current_z+2)])
    pocket.append([[['.' for _ in range(current_len+2)] for _ in range(current_len+2)] for _ in range(current_z+2)])
    return pocket

def hyper_check_if_surrounded(i, j, k, w, lines):
    is_surrounded_list = [hyper_check_occup(i+delta_i, j+delta_j, k+delta_k, w+delta_w, lines) for delta_i in [-1,0,1] for delta_j in [-1,0,1] for delta_k in [-1,0,1] for delta_w in [-1,0,1] if not abs(delta_i)+abs(delta_j)+abs(delta_k)+abs(delta_w)==0 and hyper_check_range(i+delta_i,j+delta_j,k+delta_k, w+delta_w, lines)]
    return is_surrounded_list

hyper_check_occup = lambda  i,j,k,w,lines: lines[w][k][j][i] == "#"
hyper_check_range = lambda  i,j,k,w,lines: w in range(0, len(lines)) and k in range(0, len(lines[0])) and j in range(0, len(lines[0][0])) and i in range(0, len(lines[0][0][0]))

def hyper_pretty_print_pocket(pocket):
    for w, w_slice in enumerate(pocket):
        for z, z_slice in enumerate(w_slice):
            print("Z = ", z - get_current_z0(w_slice), "W =", w - get_current_z0(pocket))
            for y_slice in z_slice:
                for x_slice in y_slice:
                    print(x_slice, end="")
                print("")
            print("")
        print("#################")

def hyper_count_cubes(pocket):
    return sum([1 for w_slice in pocket for z_slice in w_slice for y_slice in z_slice for x_slice in y_slice if x_slice=="#"])

if __name__ == "__main__":

    lines_list =[list(line) for line in open("input.txt").read().splitlines()]

    pocket = [lines_list]

    iterations = 6
    for iteration in range(iterations):
        pocket = increase_dimension(pocket)
        new_pocket = copy.deepcopy(pocket)
        for z, z_slice in enumerate(pocket):
            for y, y_slice in enumerate(z_slice):
                for x, x_slice in enumerate(y_slice):
                    if x_slice == '#':
                        if len([check for check in check_if_surrounded(x,y,z, pocket) if check is True]) not in [2,3]:
                            new_pocket[z][y][x] = '.'
                    elif x_slice == '.':
                        if len([check for check in check_if_surrounded(x,y,z, pocket) if check is True]) == 3:
                            new_pocket[z][y][x] = '#'
        pocket = copy.deepcopy(new_pocket)

    print("Part 1", count_cubes(pocket))

    pocket = [[lines_list]]
    for iteration in range(iterations):
        pocket = hyper_increase_dimension(pocket)

        new_pocket = copy.deepcopy(pocket)
        for w, w_slice in enumerate(pocket):
            for z, z_slice in enumerate(w_slice):
                for y, y_slice in enumerate(z_slice):
                    for x, x_slice in enumerate(y_slice):
                        if x_slice == '#':
                            if len([check for check in hyper_check_if_surrounded(x,y,z,w,pocket) if check is True]) not in [2,3]:
                                new_pocket[w][z][y][x] = '.'
                        elif x_slice == '.':
                            if len([check for check in hyper_check_if_surrounded(x,y,z,w,pocket) if check is True]) == 3:
                                new_pocket[w][z][y][x] = '#'
        pocket = copy.deepcopy(new_pocket)

    print("Part 2", hyper_count_cubes(pocket))