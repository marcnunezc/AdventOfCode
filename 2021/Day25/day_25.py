
def pretty_print(sea_map):
    for line in sea_map:
        print(''.join(line))
    print()

def copy_sea_map(sea_map):
    return [[char for char in line] for line in sea_map]

def advance_cucumbers(current_sea_map):
    horitzontal_new_map = copy_sea_map(current_sea_map)
    max_j = len(current_sea_map[0]) - 1
    for i, line in enumerate(current_sea_map):
        for j, char in enumerate(line):
            if char == '>':
                new_j = j+1 if j < max_j else 0
                if current_sea_map[i][new_j] == '.':
                    horitzontal_new_map[i][new_j] = '>'
                    horitzontal_new_map[i][j] = '.'
    vertical_new_map = copy_sea_map(horitzontal_new_map)
    max_i = len(current_sea_map) - 1
    for i, line in enumerate(horitzontal_new_map):
        for j, char in enumerate(line):
            if char == 'v':
                new_i = i+1 if i < max_i else 0
                if horitzontal_new_map[new_i][j] == '.':
                    vertical_new_map[new_i][j] = 'v'
                    vertical_new_map[i][j] = '.'
    return vertical_new_map


if __name__ == '__main__':

    lines_list = open('input.txt').read().splitlines()
    sea_map = [[char for char in line] for line in lines_list]

    are_maps_equal = False
    step = 0
    while not are_maps_equal:
        step += 1
        old_sea_map = copy_sea_map(sea_map)
        sea_map = advance_cucumbers(old_sea_map)
        are_maps_equal = old_sea_map == sea_map
    print("Part 1:", step)

