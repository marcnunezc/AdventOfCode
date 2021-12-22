from itertools import product
import re

def check_outside(ranges):
    return ranges[0] < -50 or ranges[1] > 50 or ranges[2] < -50 or ranges[3] > 50 or ranges[4] < -50 or ranges[5] > 50

# lines_list = open('test2.txt').read().splitlines()
# cube_on = set()
# for line in lines_list:
#     status = line.split()[0]
#     ranges =[int(value) for value in re.findall(r'-?\d+', line.split()[1])]
#     if check_outside(ranges):
#         continue
#     print("Setting status to:", status, ranges)
#     for x in range(ranges[0], ranges[1]+1):
#         for y in range(ranges[2], ranges[3]+1):
#             for z in range(ranges[4], ranges[5]+1):
#                     if status == 'on':
#                         cube_on.add((x,y,z))
#                     else:
#                         cube_on.discard((x,y,z))

# print("Part 1", len(cube_on))


def split_cube_in_eight(cube_range, cube_status):
    split_cube = {}
    split_x_ranges = [[cube_range[0], cube_range[0]+(cube_range[1]-cube_range[0])/2], [cube_range[0]+(cube_range[1]-cube_range[0])/2, cube_range[1]]]
    split_y_ranges = [[cube_range[2], cube_range[2]+(cube_range[3]-cube_range[2])/2], [cube_range[2]+(cube_range[3]-cube_range[2])/2, cube_range[3]]]
    split_z_ranges = [[cube_range[4], cube_range[4]+(cube_range[5]-cube_range[4])/2], [cube_range[4]+(cube_range[5]-cube_range[4])/2, cube_range[5]]]
    for i, j, k in product([0, 1], repeat=3):
        split_cube[tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k])] = cube_status
    return split_cube

def check_inside(key1, key2, to_check1, to_check_2):
    return key1 < to_check1 < key2 and key1 < to_check_2 < key2

def check_intersect(key1, key2, to_check1, to_check_2):
    return (key1 < to_check1 < key2) ^ (key1 < to_check_2 < key2)

def check_inside_cubes(this_cubes, cubes_to_check, key):
    cubes = set()
    someone_inside = False

    for cube_range in this_cubes:
        is_x_inside = check_inside(cube_range[0], cube_range[1], key[0], key[1])
        is_y_inside = check_inside(cube_range[2], cube_range[3], key[2], key[3])
        is_z_inside = check_inside(cube_range[4], cube_range[5], key[4], key[5])
        if is_x_inside or is_y_inside or is_z_inside:
            new_cubes = split_cube_in_eight(cube_range, 'on')
            for new_range, new_status in new_cubes.items():
                cubes.add(new_range)
            someone_inside = True
        else:
            cubes.add(cube_range)
    return someone_inside, cubes

def check_inside_cube_to_check(this_cubes, cubes_to_check, key):
    for cube_range in this_cubes:
        is_x_inside = check_inside(key[0], key[1], cube_range[0], cube_range[1])
        is_y_inside = check_inside(key[2], key[3], cube_range[2], cube_range[3])
        is_z_inside = check_inside(key[4], key[5], cube_range[4], cube_range[5])
        if is_x_inside or is_y_inside or is_z_inside:
            new_cubes = split_cube_in_eight(key, cubes_to_check[key])
            del cubes_to_check[key]
            for new_range, new_status in new_cubes.items():
                cubes_to_check[new_range] = new_status
            return True, cubes_to_check
    return False, cubes_to_check

def get_ranges_from_intersecting_cubes(range0, range1):
    if range0[0] <= ranges1[0] <= range0[1]:
        split_x_ranges =  [[range0[0], ranges1[0]], [range0[1], ranges1[1]]]
    else:
        split_x_ranges =  [[ranges1[0], range0[0]], [ranges1[1], range0[1]]]

    if range0[2] <= ranges1[2] <= range0[3]:
        split_y_ranges =  [[range0[2], ranges1[2]], [range0[3], ranges1[3]]]
    else:
        split_y_ranges =  [[ranges1[2], range0[2]], [ranges1[3], range0[3]]]

    if range0[4] <= ranges1[4] <= range0[5]:
        split_z_ranges =  [[range0[4], ranges1[4]], [range0[5], ranges1[5]]]
    else:
        split_z_ranges =  [[ranges1[4], range0[4]], [ranges1[5], range0[5]]]
    return split_x_ranges, split_y_ranges, split_z_ranges

def check_intersecting(cubes, ranges_to_check, status_to_check):
    new_cubes = set()
    is_intersecting = False
    for cube_ranges in cubes:
        is_x_intersecting = check_intersect(cube_ranges[0], cube_ranges[1], ranges_to_check[0], ranges_to_check[1])
        is_y_intersecting = check_intersect(cube_ranges[2], cube_ranges[3], ranges_to_check[2], ranges_to_check[3])
        is_z_intersecting = check_intersect(cube_ranges[4], cube_ranges[5], ranges_to_check[4], ranges_to_check[5])

        if is_x_intersecting and is_y_intersecting and is_z_intersecting:
            split_x_ranges, split_y_ranges, split_z_ranges = get_ranges_from_intersecting_cubes(cube_ranges, ranges_to_check)
            for i, j, k in product([0, 1], repeat=3):
                if i*j*k == 0 or status_to_check == 'on':
                    new_cubes.add(tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k]))
            if status_to_check=='on':
                split_x_ranges, split_y_ranges, split_z_ranges = get_ranges_from_intersecting_cubes(ranges_to_check, cube_ranges)
                for i, j, k in product([0, 1], repeat=3):
                    new_cubes.add(tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k]))
            is_intersecting = True
    return is_intersecting, new_cubes


lines_list = open('test3.txt').read().splitlines()
cubes = set()
cubes_to_check = {}
for line in lines_list:
    status = line.split()[0]
    ranges = [int(value) for value in re.findall(r'-?\d+', line.split()[1])]
    cubes_to_check[tuple(ranges)] = status

while len(cubes_to_check.keys()) > 0:
    this_key = next(iter(cubes_to_check.keys()))
    print("this key", len(cubes_to_check))
    is_any_cube_inside, cubes = check_inside_cubes(cubes, cubes_to_check, this_key)
    if is_any_cube_inside:
        print("cube cube inside", len(cubes))
        continue
    is_cube_to_check_inside, cubes_to_check = check_inside_cube_to_check(cubes, cubes_to_check, this_key)
    if is_cube_to_check_inside:
        print("cube to check inside", len(cubes_to_check))
        continue
    is_intersecting, new_cubes = check_intersecting(cubes, this_key , cubes_to_check[this_key])
    to_check_status = cubes_to_check[this_key]
    if is_intersecting:
        print("is intersecting", this_key)
        cubes_to_check.remove(this_key)
    elif to_check_status == 'on':
        print("not intersecting, adding key", this_key)
        cubes.add(this_key)



# for cube_range_to_check in cubes_to_check.keys():
#      is_this_inside(cube_range_to_check, cubes):

#     elif is_him_inside(cube_range_to_check, cubes):
#     is_intersecting(cubes, cube_range, cubes_to_check[cube_range])

# print("Part 2", len(cubes))


#     print(ranges)
