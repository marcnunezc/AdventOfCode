def read_input(file_name):
    lines_list =open(file_name).read().splitlines()
    tiles_dict = {}
    for line in lines_list:
        if "Tile" in line:
            tile_id = line.split(" ")[1][:-1]
            image = []
            i = 0
        elif not i==10:
            image.append([char for char in line])
            i += 1
        else:
            tiles_dict[tile_id] = image
    tiles_dict[tile_id] = image
    return tiles_dict

def rotate_matrix(m, rottype):
    if rottype == "0":
        return m
    elif rottype == "1":
        return [[m[j][i] for j in range(len(m))] for i in range(len(m[0])-1,-1,-1)]
    else:
        return rotate_matrix([[m[j][i] for j in range(len(m))] for i in range(len(m[0])-1,-1,-1)], str(int(rottype)-1))

def get_row(m,i):
    return m[i]

def flip_matrix(m, fliptype):
    if fliptype == "h":
        return [[m[j][i] for i in range(len(m[0])-1,-1,-1)] for j in range(len(m))]
    elif fliptype == "v":
        return [[m[j][i] for i in range(len(m))] for j in range(len(m[0])-1,-1,-1)]
    else:
        return m
def strip_matrix(m):
    return [[m[j][i] for i in range(1,len(m)-1)] for j in range(1,len(m)-1)]

def get_column(m, j):
    return [m[i][j] for i in range(len(m))]

def matching_edges(m,n):
    edge_col_rows = [0,len(m)-1]
    matching_edges = 0
    orientation = "F"
    for m_edge, n_edge in zip(edge_col_rows, edge_col_rows[::-1]):
        if get_row(m, m_edge) == get_row(n, n_edge):
                if m_edge == 0:
                    return "N"
                else:
                    return "S"
        if get_column(m, m_edge) == get_column(n, n_edge):
                if m_edge == 0:
                    return "W"
                else:
                    return "E"
    return orientation

def get_equivalent_combinations():
    test_matrix = [['a','b','c'],
                ['d','e','f'],
                ['g','h','i']]
    tile_values = test_matrix
    neigh_values = test_matrix
    equivalent_combinations = {}
    for rotation in ["0","1","2","3"]:
        for flipping in ["n", "h", "v"]:
            for neigh_rotation in ["0","1","2","3"]:
                for neigh_flipping in ["n", "h", "v"]:
                    rotated_matrix = rotate_matrix(tile_values, rotation)
                    neigh_rotated_matrix = rotate_matrix(neigh_values, neigh_rotation)
                    flipped_matrix = flip_matrix(rotated_matrix, flipping)
                    neigh_flipped_matrix = flip_matrix(neigh_rotated_matrix, neigh_flipping)
                    key_tuple = (rotation+flipping, neigh_rotation+neigh_flipping)
                    orientation_match = matching_edges(flipped_matrix, neigh_flipped_matrix)
                    if flipped_matrix == neigh_flipped_matrix and not key_tuple[0]==key_tuple[1]:
                        equivalent_combinations[key_tuple[0]] = key_tuple[1]
    sorted_combinations = sorted(equivalent_combinations)
    return sorted_combinations[len(sorted_combinations)//2:]

def find_east_candidates(key_west, current_rotation):
    east_keys = {subkey:key for key, value in matching_info[key_west].items() for subkey, subvalue in value.items() if subvalue == "E"}
    matching_keys_east = [[key,subkey] for key, subkey in east_keys.items() if key[0] == current_rotation]
    return matching_keys_east

def find_south_candidates(key_west, current_rotation):
    south_keys = {subkey:key for key, value in matching_info[key_west].items() for subkey, subvalue in value.items() if subvalue == "S"}
    matching_keys_south = [[key,subkey] for key, subkey in south_keys.items() if key[0] == current_rotation]
    return matching_keys_south

def check_and_return_image(final_image):
    for i in range(1, len(final_image)):
        east_cand = find_east_candidates(final_image[0][i-1][0], final_image[0][i-1][1])
        if len(east_cand)>0:
            final_image[0][i] = [east_cand[0][1], east_cand[0][0][1]]
        else:
            return False, final_image
    for j in range (1, len(final_image)):
        south_cand = find_south_candidates(final_image[j-1][0][0], final_image[j-1][0][1])
        if len(south_cand)>0:
            final_image[j][0] = [south_cand[0][1], south_cand[0][0][1]]
        else:
            return False, final_image
        for i in range(1, len(final_image)):
            east_cand = find_east_candidates(final_image[j][i-1][0], final_image[j][i-1][1])
            if len(east_cand)>0:
                final_image[j][i] = [east_cand[0][1], east_cand[0][0][1]]
            else:
                return False, final_image
    return True, final_image

def get_image_from_corner(corner):
    final_image = [["" for j in range(square_len)] for i in range(square_len)]
    for rotation in ["0","1","2","3"]:
        for flipping in ["n", "h", "v"]:
            final_image[0][0] = [corner, "0n"]
            final_image[0][0][1] = rotation+flipping
            is_found, final_image = check_and_return_image(final_image)
            if is_found:
                return final_image
    return []

def pretty_print_tile(m):
    for row in m:
        for char in row:
            print(char, end="")
        print("")
    print("")
    print("")

def check_if_monster(i,j, this_image):
    for j_m, j_tile in enumerate(monster_list):
        for i_m, monster_tile in enumerate(j_tile):
            if i+i_m >= len(big_image):
                return False
            if j+j_m >= len(big_image):
                return False
            if monster_tile == "#":
                if this_image[j+j_m][i+i_m] != "#":
                    return False
    return True

def count_seats(new_matrix):
    return sum([1 for line in new_matrix for char in line if char=="#"])

if __name__ == "__main__":
    import math
    tiles_dict = read_input("test.txt")

    square_len = int(math.sqrt(len(tiles_dict.keys())))
    matching_info = {}
    equivalent_combinations = get_equivalent_combinations()
    for tile_id, tile_values in tiles_dict.items():
        matching_info[tile_id] = {}
        for neigh_id, neigh_values in tiles_dict.items():
            if not neigh_id==tile_id:
                rotation_dict = {}
                for rotation in ["0","1","2","3"]:
                    for flipping in ["n", "h", "v"]:
                        for neigh_rotation in ["0","1","2","3"]:
                            for neigh_flipping in ["n", "h", "v"]:
                                key_tuple = (rotation+flipping, neigh_rotation+neigh_flipping)
                                if not key_tuple[0] in equivalent_combinations and not key_tuple[1] in equivalent_combinations:
                                    rotated_matrix = rotate_matrix(tile_values, rotation)
                                    neigh_rotated_matrix = rotate_matrix(neigh_values, neigh_rotation)
                                    flipped_matrix = flip_matrix(rotated_matrix, flipping)
                                    neigh_flipped_matrix = flip_matrix(neigh_rotated_matrix, neigh_flipping)
                                    orientation_match = matching_edges(flipped_matrix, neigh_flipped_matrix)
                                    if orientation_match != "F":
                                        rotation_dict[key_tuple] = orientation_match
                neigh_dict = {neigh_id:rotation_dict}
                matching_info[tile_id].update(neigh_dict)
    ## Locate corners:
    multiplication = 1
    corners = []
    for mkey, mvalue in matching_info.items():
        matches = sum([1 for key, values in mvalue.items() if len(values.keys()) > 0])
        if matches == 2:
            multiplication *= int(mkey)
            corners.append(mkey)
    print("Part 1", multiplication)

    final_image = get_image_from_corner(corners[0])
    big_image = [["" for j in range(square_len*8)] for i in range(square_len*8)]
    for j, j_image in enumerate(final_image):
        for i, i_image in enumerate(j_image):
            key = i_image[0]
            rotation = i_image[1][0]
            flip = i_image[1][1]
            tiles = tiles_dict[key]
            actual_tiles = strip_matrix(flip_matrix(rotate_matrix(tiles, rotation), flip))
            for sub_j, j_tile in enumerate(actual_tiles):
                for sub_i, i_tile in enumerate(j_tile):
                    actual_i = sub_i + i*len(actual_tiles)
                    actual_j = sub_j + j*len(actual_tiles)
                    big_image[actual_j][actual_i] = i_tile

    monster_list =open("monster.txt").read().splitlines()

    monster_seats = count_seats(monster_list)
    for rotation in ["0","1","2","3"]:
        for flipping in ["n", "h", "v"]:
            if not rotation+flipping in equivalent_combinations:
                actual_big_image = flip_matrix(rotate_matrix(big_image, rotation), flip)
                number_of_monsters = sum([check for check in [check_if_monster(i,j, actual_big_image) for i,_ in enumerate(actual_big_image) for j,_ in enumerate(actual_big_image)] if check is True])
                image_seats = count_seats(actual_big_image)
                if number_of_monsters > 0:
                    print("Part 2", image_seats - number_of_monsters*monster_seats)
