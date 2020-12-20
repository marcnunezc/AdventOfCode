
import math
lines_list =open("input.txt").read().splitlines()

tiles_dict = {}

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

def get_column(m, j):
    return [m[i][j] for i in range(len(m))]

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

edge_col_rows = [0,9]
def matching_edges(m,n):
    matching_edges = 0
    for m_edge, n_edge in zip(edge_col_rows, edge_col_rows[::-1]):
        if get_row(m, m_edge) == get_row(n, n_edge):
                # print("row match",m_edge, n_edge, get_column(m, m_edge), get_column(n, n_edge) )
                matching_edges += 1
        if get_column(m, m_edge) == get_column(n, n_edge):
                # print("column match",m_edge, n_edge, get_column(m, m_edge), get_column(n, n_edge) )
                matching_edges += 1
    return matching_edges

matching_info = {}


square_len = int(math.sqrt(len(tiles_dict.keys())))
def pretty_print_tile(m):
    for row in m:
        for char in row:
            print(char, end="")
        print("")
    print("")
    print("")

final_image = [["" for j in range(square_len)] for i in range(square_len)]
for tile_id, tile_values in tiles_dict.items():
    matching_info[tile_id] = {}
    # print("Tile original")
    # pretty_print_tile(tile_values)

    for neigh_id, neigh_values in tiles_dict.items():
        if not neigh_id==tile_id:
            rotation_dict = {}
            for neigh_rotation in ["0","1","2","3"]:
                for neigh_flipping in ["n", "h", "v"]:
                    for rotation in ["0","1","2","3"]:
                        for flipping in ["n", "h", "v"]:
                            rotated_matrix = rotate_matrix(tile_values, rotation)
                            neigh_rotated_matrix = rotate_matrix(neigh_values, neigh_rotation)
                            flipped_matrix = flip_matrix(rotated_matrix, flipping)
                            neigh_flipped_matrix = flip_matrix(neigh_rotated_matrix, neigh_flipping)
                            # print("Tile: ", rotation, flipping)
                            # pretty_print_tile(flipped_matrix)
                            # print(tile_id, rotation+flipping, neigh_id, neigh_rotation+neigh_flipping)
                            # pretty_print_tile(flipped_matrix)
                            # pretty_print_tile(neigh_flipped_matrix)

                            # print(rotate_matrix)
                            key_tuple = (rotation+flipping, neigh_rotation+neigh_flipping)
                            rotation_dict[key_tuple] = matching_edges(flipped_matrix, neigh_flipped_matrix)
            neigh_dict = {neigh_id:rotation_dict}
            matching_info[tile_id].update(neigh_dict)
print(matching_info.keys())
for mkey, mvalue in matching_info.items():
    for key, values in mvalue.items():
        # if key =="2311" or mkey == "2311":
        if mkey == "3079":
            print(mkey,key, [str(subkey)+": "+str(subvalue) for subkey, subvalue in values.items() if subvalue != 0])

## Locate corners:
multiplication = 1
for mkey, mvalue in matching_info.items():
    matches = 0
    for key, values in mvalue.items():
        if sum([1 for subvalue in values.values() if subvalue != 0]) > 0:
            matches += 1
    if matches == 2:
        multiplication *= int(mkey)
print("Part 1", multiplication)