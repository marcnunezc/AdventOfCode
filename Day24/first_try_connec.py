lines_list = open("input.txt").read().splitlines()
print(lines_list[0])
# e, se, sw, w, nw, and ne
connectivities = {}
connectivities[1] = [2,3,4,5,6,7]
for key, value in connectivities.items():
    tiles_color[key] = "W"
    for subkey in value:
        tiles_color[subkey] = "W"

print(tiles_color[2])

def validate_and_get_new_tile(ref_tile, pos):
    if connectivities[ref_tile][pos] in connectivities.keys():
        return connectivities[ref_tile][pos]
    else:


def process_tiles(line):
    ref_tile = 1
    i=0
    while (i < len(line)):
        if line[i] == "e":
            ref_tile = validate_and_get_new_tile(ref_tile, 0)
            i += 1
        if line[i] == "s":
            if line[i+1] == "e":
                ref_tile = validate_and_get_new_tile(ref_tile, 1)
                i += 2
            elif line[i+1] == "w":
                ref_tile = validate_and_get_new_tile(ref_tile, 2)
                i += 2
        if line[i] == "w":
            ref_tile = validate_and_get_new_tile(ref_tile, 3)
            i += 1
        if line[i] == "n":
            if line[i+1] == "w":
                ref_tile = validate_and_get_new_tile(ref_tile, 4)
                i += 2
            elif line[i+1] == "e":
                ref_tile = validate_and_get_new_tile(ref_tile, 5)
                i += 2
    return ref_tile

process_tiles("nwwswee")

print(tiles_color)