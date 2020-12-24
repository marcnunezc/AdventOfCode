from collections import defaultdict
import copy
def process_tiles(line):
    ref_tile = [0.0, 0.0]
    i=0
    while (i < len(line)):
        if line[i] == "e":
            ref_tile[0] += 1.0
            i += 1
        elif line[i] == "s":
            ref_tile[1] += -0.5
            if line[i+1] == "e":
                ref_tile[0] += 0.5
                i += 2
            elif line[i+1] == "w":
                ref_tile[0] += -0.5
                i += 2
        elif line[i] == "w":
            ref_tile[0] += -1.0
            i += 1
        elif line[i] == "n":
            ref_tile[1] += 0.5
            if line[i+1] == "w":
                ref_tile[0] += -0.5
                i += 2
            elif line[i+1] == "e":
                ref_tile[0] += 0.5
                i += 2
    return ref_tile

def count_black(tiles_color):
    return len([value for value in tiles_color.values() if value == "B"])

def get_delta_list():
        return [
        [1.0 , 0.0],
        [-1.0 , 0.0],
        [0.5, 0.5],
        [0.5, -0.5],
        [-0.5, 0.5],
        [-0.5, -0.5]
    ]

def get_neigh_coord_list(tiles_color, tile_coord):
    ref_tile = list(tile_coord)
    neighbouring_list = get_delta_list()
    return [[ref_tile[0]+neighbour[0], ref_tile[1]+neighbour[1]] for neighbour in neighbouring_list]

def check_tile(dict_to_edit, ref_dict, tile_coord):
    if tile_coord in checked_tiles:
        return dict_to_edit, []
    neigh_coord_list = get_neigh_coord_list(ref_dict, tile_coord)
    neigh_color_list = [ref_dict[tuple(coords)] for coords in neigh_coord_list]
    b_len = len([neigh for neigh in neigh_color_list if neigh=="B"])
    if ref_dict[tile_coord] == "B":
        if not b_len in [1,2]:
            dict_to_edit[tile_coord] = "W"
    else:
        if b_len == 2:
            dict_to_edit[tile_coord] = "B"
    checked_tiles.add(tile_coord)
    return dict_to_edit, [neigh_coord for neigh_coord in neigh_coord_list if not tuple(neigh_coord) in checked_tiles]

# e, se, sw, w, nw, and ne
lines_list = open("input.txt").read().splitlines()
tiles_color = defaultdict(lambda: "W")
flip = {
    "W" : "B",
    "B" : "W"
}
for line in lines_list:
    flip_tile = tuple(coord for coord in process_tiles(line))
    tiles_color[flip_tile] = flip[tiles_color[flip_tile]]
print("Part 1", count_black(tiles_color))

def check_neighbours(this_tile_dict, aux_dict, neighbour_list):
    new_neigh_list = []
    for neigh_coord in neighbour_list:
        this_tile_dict, neigh_coord_list = check_tile(this_tile_dict, aux_dict, tuple(neigh_coord))
        new_neigh_list.extend(neigh_coord_list)
    return this_tile_dict, new_neigh_list

days = 100

for day in range(days):
    checked_tiles = set()
    this_tile_dict = copy.deepcopy(tiles_color)
    neighbour_list = []
    aux_dict = copy.deepcopy(tiles_color)
    for tile_coord, color in tiles_color.items():
        this_tile_dict, neigh_coord_list = check_tile(this_tile_dict, aux_dict, tile_coord)
        neighbour_list.extend([coord for coord in neigh_coord_list if not tuple(coord) in checked_tiles])
    all_white = False
    while(not all_white):
        this_tile_dict, neighbour_list = check_neighbours(this_tile_dict, aux_dict, neighbour_list)
        all_white = True
        for neigh in neighbour_list:
            if tiles_color[tuple(neigh)] == "B":
                all_white = False

    tiles_color = copy.deepcopy(this_tile_dict)
    print("Day", day+1, count_black(tiles_color))
print("Part 2", count_black(tiles_color))