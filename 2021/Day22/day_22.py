from itertools import product
import re

def check_outside(ranges):
    return ranges[0] < -50 or ranges[1] > 50 or ranges[2] < -50 or ranges[3] > 50 or ranges[4] < -50 or ranges[5] > 50

lines_list = open('input.txt').read().splitlines()
# lines_list= lines_list[0:-2]
cube_on = set()
for line in lines_list:
    status = line.split()[0]
    ranges =[int(value) for value in re.findall(r'-?\d+', line.split()[1])]
    if check_outside(ranges):
        continue
    # print("Setting status to:", status, ranges)
    for x in range(ranges[0], ranges[1]+1):
        for y in range(ranges[2], ranges[3]+1):
            for z in range(ranges[4], ranges[5]+1):
                    if status == 'on':
                        cube_on.add((x,y,z))
                    else:
                        cube_on.discard((x,y,z))
    # print("current volume", len(cube_on))
volume_1 = len(cube_on)
print("Part 1", len(cube_on))

def split_cube_in_eight(cube_range, cube_status):
    split_cube = {}
    split_x_ranges = [[cube_range[0], cube_range[0]+(cube_range[1]-cube_range[0])/2], [cube_range[0]+(cube_range[1]-cube_range[0])/2, cube_range[1]]]
    split_y_ranges = [[cube_range[2], cube_range[2]+(cube_range[3]-cube_range[2])/2], [cube_range[2]+(cube_range[3]-cube_range[2])/2, cube_range[3]]]
    split_z_ranges = [[cube_range[4], cube_range[4]+(cube_range[5]-cube_range[4])/2], [cube_range[4]+(cube_range[5]-cube_range[4])/2, cube_range[5]]]
    for i, j, k in product([0, 1], repeat=3):
        split_cube[tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k])] = cube_status
    return split_cube

def split_cube_in_half(cube_range, cube_status, x_range, y_range, z_range, is_x, is_y, is_z):
    split_cube = {}
    if is_x:
        split_x_ranges = [[cube_range[0], cube_range[0]+(cube_range[1]-cube_range[0])/2], [cube_range[0]+(cube_range[1]-cube_range[0])/2, cube_range[1]]]
    elif is_y:
        split_y_ranges = [[cube_range[2], cube_range[2]+(cube_range[3]-cube_range[2])/2], [cube_range[2]+(cube_range[3]-cube_range[2])/2, cube_range[3]]]
    elif is_z:
        split_z_ranges = [[cube_range[4], cube_range[4]+(cube_range[5]-cube_range[4])/2], [cube_range[4]+(cube_range[5]-cube_range[4])/2, cube_range[5]]]
    for i, j, k in product([0, 1], repeat=3):
        split_cube[tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k])] = cube_status
    return split_cube


def print_corners_from_range(cube_range):

    print(cube_range[0], cube_range[2], cube_range[4])
    print(cube_range[0], cube_range[3], cube_range[4])
    print(cube_range[0], cube_range[3], cube_range[5])
    print(cube_range[0], cube_range[2], cube_range[5])
    print(cube_range[1], cube_range[2], cube_range[4])
    print(cube_range[1], cube_range[3], cube_range[4])
    print(cube_range[1], cube_range[2], cube_range[5])
    print(cube_range[1], cube_range[3], cube_range[5])

def check_inside(key1, key2, to_check1, to_check_2):
    return key1 <= to_check1 <= key2 and key1 <= to_check_2 <= key2

def check_intersect(key1, key2, to_check1, to_check_2):
    return (key1 <= to_check1 <= key2) or (key1 <= to_check_2 <= key2) or (to_check1 <= key1 <= to_check_2)

def check_cube_inside(base, to_check):
    is_x_inside = check_inside(base[0], base[1], to_check[0], to_check[1])
    is_y_inside = check_inside(base[2], base[3], to_check[2], to_check[3])
    is_z_inside = check_inside(base[4], base[5], to_check[4], to_check[5])
    return is_x_inside or is_y_inside or is_z_inside

def check_cube_completely_inside(base, to_check):
    is_x_inside = check_inside(base[0], base[1], to_check[0], to_check[1])
    is_y_inside = check_inside(base[2], base[3], to_check[2], to_check[3])
    is_z_inside = check_inside(base[4], base[5], to_check[4], to_check[5])
    return is_x_inside and is_y_inside and is_z_inside

# def get_axis_ranges(range0, range1):
#     print(range0, range1, check_inside(range0[0], range0[1], range1[0], range1[1]), check_intersect(range0[0], range0[1], range1[0], range1[1]))
#     if check_inside(range0[0], range0[1], range1[0], range1[1]):
#         if range0[0] == range1[0] and range0[1] == range1[1]:
#             split_axis =  [[range0[0], range0[1]]]
#         elif range0[1] == range1[0] == range1[1]:
#             split_axis =  [[range0[0], range0[1]], [range1[0], range1[1]]]
#         elif range0[1] == range1[0]:
#             split_axis =  [[range0[0], range0[1]], [range1[0], range1[1]]]
#         elif range0[1] == range1[1]:
#             split_axis =  [[range0[0], range1[0]],[range1[0]+1, range1[1]]]
#         else:
#             split_axis =  [[range0[0], range1[0]],[range1[0]+1, range1[1]], [range1[1]+1, range0[1]]]
#     elif range0[0] <= range1[0] < range0[1]:
#         split_axis =  [[range0[0], range1[0]], [range1[0], range0[1]]]
#     elif range0[0] <= range1[1] < range0[1]:
#         split_axis =  [[range0[0], range1[1]], [range1[1], range0[1]]]
#     elif range0[1] == range1[0]:
#         split_axis =  [[range0[0], range1[0]], [range1[0], range1[1]]]
#     elif range1[1] == range0[1]:
#         split_axis =  [[range1[0], range0[0]], [range0[0], range0[1]]]
#     else:
#         #should be inside but reversed
#         aux=range0
#         range0=range1
#         range1=aux
#         if not check_inside(range0[0], range0[1], range1[0], range1[1]):
#             raise(Exception("rarito"))
#         if range0[0] == range1[0] and range0[1] == range1[1]:
#             split_axis =  [[range0[0], range0[0]]]
#         elif range0[1] == range1[1]:
#             split_axis =  [[range0[0], range1[0]],[range1[0]+1, range1[1]]]
#         else:
#             split_axis =  [[range0[0], range1[0]],[range1[0]+1, range1[1]], [range1[1]+1, range0[1]]]
#     print(split_axis)
#     return split_axis

# def get_axis_ranges(range0, range1):
#     print(range0, range1, check_inside(range0[0], range0[1], range1[0], range1[1]), check_intersect(range0[0], range0[1], range1[0], range1[1]))
#     sorted_list = sorted(range0+ range1)
#     split_axis =[]
#     if sorted_list[0] != sorted_list[1]:
#         split_axis.append(tuple([sorted_list[0], sorted_list[0]+sorted_list[1]-sorted_list[0]-1]))
#     else:
#         split_axis.append(tuple([sorted_list[0], sorted_list[1]]))
#         sorted_list[1]+=1

#     if sorted_list[1] != sorted_list[2]:
#         split_axis.append(tuple([sorted_list[1], sorted_list[1]+sorted_list[2]-sorted_list[1]-1]))
#     else:
#         split_axis.append(tuple([sorted_list[1], sorted_list[1]+sorted_list[2]-sorted_list[1]]))
#         sorted_list[2]+=1
#     if sorted_list[2] != sorted_list[3]:
#         split_axis.append(tuple([sorted_list[2], sorted_list[2]+sorted_list[3]-sorted_list[2]-1]))
#         split_axis.append(tuple([sorted_list[2]+sorted_list[3]-sorted_list[2], sorted_list[2]+sorted_list[3]-sorted_list[2]]))
#     else:
#         split_axis.append(tuple([sorted_list[2], sorted_list[2]+sorted_list[3]-sorted_list[2]]))



#         # raise(Exception("do somthing here"))
#     split_axis = list(dict.fromkeys(split_axis))

#     # split_axis = [[sorted_list[0], sorted_list[1]], [sorted_list[1], sorted_list[2]], [sorted_list[2], sorted_list[3]]]
#     print("split axis",split_axis)
#     return split_axis

def append_split(split_axis, a, b, c, d):

    if not a==b:
        split_axis.append(tuple([a,b-1]))
    split_axis.append(tuple([b,c]))
    split_axis.append(tuple([c+1,d]))


def get_axis_ranges(range0, range1):
    # print(range0, range1, check_inside(range0[0], range0[1], range1[0], range1[1]), check_intersect(range0[0], range0[1], range1[0], range1[1]))
    split_axis =[]
    if range0[0] <= range1[0] <= range0[1] <= range1[1]:
        append_split(split_axis, range0[0], range1[0], range0[1], range1[1])
    elif range1[0] <= range0[0] <= range1[1] <= range0[1]:
        append_split(split_axis, range1[0], range0[0], range1[1], range0[1])
    elif range0[0] <= range1[0] <= range1[1] <= range0[1]:
        append_split(split_axis, range0[0], range1[0], range1[1], range0[1])
    elif range1[0] <= range0[0] <= range0[1] <= range1[1]:
        append_split(split_axis, range1[0], range0[0], range0[1], range1[1])


    split_axis = list(dict.fromkeys(split_axis))
    # print("split axis",split_axis)


    return split_axis

def get_ranges_from_intersecting_cubes(range0, range1):
    split_x_ranges = get_axis_ranges(range0[0:2], range1[0:2])
    split_y_ranges = get_axis_ranges(range0[2:4], range1[2:4])
    split_z_ranges = get_axis_ranges(range0[4:6], range1[4:6])
    ranges = []
    ranges.append(list(range(0, len(split_x_ranges))))
    ranges.append(list(range(0, len(split_y_ranges))))
    ranges.append(list(range(0, len(split_z_ranges))))
    # print("ranges", ranges)
    return split_x_ranges, split_y_ranges, split_z_ranges, ranges

def check_intersecting(cubes, ranges_to_check, status_to_check):
    new_cubes = set()
    is_intersecting = False
    cubes_to_delete = set()
    for cube_ranges in cubes:
        is_x_intersecting = check_intersect(cube_ranges[0], cube_ranges[1], ranges_to_check[0], ranges_to_check[1]) or check_inside(cube_ranges[0], cube_ranges[1], ranges_to_check[0], ranges_to_check[1]) or check_inside(ranges_to_check[0], ranges_to_check[1], cube_ranges[0], cube_ranges[1])
        is_y_intersecting = check_intersect(cube_ranges[2], cube_ranges[3], ranges_to_check[2], ranges_to_check[3]) or check_inside(cube_ranges[2], cube_ranges[3], ranges_to_check[2], ranges_to_check[3]) or check_inside(ranges_to_check[2], ranges_to_check[3], cube_ranges[2], cube_ranges[3])
        is_z_intersecting = check_intersect(cube_ranges[4], cube_ranges[5], ranges_to_check[4], ranges_to_check[5]) or check_inside(cube_ranges[4], cube_ranges[5], ranges_to_check[4], ranges_to_check[5]) or check_inside(ranges_to_check[4], ranges_to_check[5], cube_ranges[4], cube_ranges[5])
        # print(cube_ranges, ranges_to_check)
        # print(is_x_intersecting, is_y_intersecting, is_z_intersecting)
        if is_x_intersecting and is_y_intersecting and is_z_intersecting:
            split_x_ranges, split_y_ranges, split_z_ranges, ranges = get_ranges_from_intersecting_cubes(cube_ranges, ranges_to_check)
            for i, j, k in product(*ranges):
                cube_to_add = tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k])
                # print(i,j, k)
                if status_to_check == 'on':
                    is_in_base = check_cube_completely_inside(cube_ranges, cube_to_add)
                    is_in_candidate = check_cube_completely_inside(ranges_to_check, cube_to_add)
                    # print("cube_to_add", cube_to_add,  compute_volume(cube_to_add), is_in_base, is_in_candidate)

                    if is_in_base:
                        # print("cube_to_add", cube_to_add,  compute_volume(cube_to_add))
                        new_cubes.add(cube_to_add)
                elif status_to_check == 'off':
                    is_in_base = check_cube_completely_inside(cube_ranges, cube_to_add)
                    is_in_candidate = check_cube_completely_inside(ranges_to_check, cube_to_add)
                    if is_in_base and is_in_candidate:
                        # print("in base and in candidate(off), doing nothing")
                        pass
                    if not (is_in_base or is_in_candidate):
                        pass
                        # raise(Exception("Cube to add", cube_to_add, "is not in", cube_ranges, "or", ranges_to_check))
                    if is_in_base and not is_in_candidate:
                        # print("cube_to_add2", cube_to_add, is_in_base)
                        new_cubes.add(cube_to_add)
                    # if is_in_candidate:
                    #     print("cube_notadded", cube_to_add, is_in_base,is_in_candidate)

            # stop
            # if status_to_check=='on':
            #     split_x_ranges, split_y_ranges, split_z_ranges, ranges = get_ranges_from_intersecting_cubes(ranges_to_check, cube_ranges)
            #     # print("base", cube_ranges)
            #     for i, j, k in product(*ranges):
            #         cube_to_add = tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k])
            #         is_in_base = check_cube_completely_inside(cube_ranges, cube_to_add)
            #         # print(cube_to_add, "is_in_base", is_in_base)
            #         if not is_in_base:
            #             new_cubes.add(cube_to_add)
            # print("candidate", ranges_to_check)
            # print("new cubes", new_cubes)
            cubes_to_delete.add(cube_ranges)
            # print("cubes to delete", cubes_to_delete)
            return True, new_cubes, cubes_to_delete
    return False, new_cubes,set()

def check_completely_inside(cubes, key):
    for cube_range in cubes:
        is_x_inside = check_inside(cube_range[0], cube_range[1], key[0], key[1])
        is_y_inside = check_inside(cube_range[2], cube_range[3], key[2], key[3])
        is_z_inside = check_inside(cube_range[4], cube_range[5], key[4], key[5])
        if is_x_inside and is_y_inside and is_z_inside:
            # print('This', key, "is inside of ", cube_range)
            return True
    return False


def check_any_completely_inside(cubes, key):
    new_cubes = set()
    any_inside = False
    for cube_range in cubes:
        is_x_inside = check_inside(key[0], key[1], cube_range[0], cube_range[1])
        is_y_inside = check_inside(key[2], key[3], cube_range[2], cube_range[3])
        is_z_inside = check_inside(key[4], key[5], cube_range[4], cube_range[5])
        if is_x_inside and is_y_inside and is_z_inside:
            # print('This', cube_range, "is inside of ", key)
            any_inside = True
            pass
        else:
            new_cubes.add(cube_range)

    return any_inside, new_cubes

def compute_volume(cube):
    return len(range(cube[0], cube[1]+1))* len(range(cube[2], cube[3]+1))*len(range(cube[4], cube[5]+1))

lines_list = open('input.txt').read().splitlines()
# lines_list = lines_list[0:-2]
cubes = set()
cubes_to_check = {}
for line in lines_list:
    status = line.split()[0]
    ranges = [int(value) for value in re.findall(r'-?\d+', line.split()[1])]
    cubes_to_check[tuple(ranges)] = status

# print(list_of_keys)
# print(list_of_keys)
# stop
iters = 0
while len(list(cubes_to_check.keys())) > 0:
    volume = sum([len(range(cube[0], cube[1]+1))+ len(range(cube[2], cube[3]+1))+len(range(cube[4], cube[5]+1)) for cube in cubes])

    # print("current_volume", volume)
    iters += 1
    # if iters==4:
    #     stop
    if iters % 1000 == 0:
        print("Len cubes:", len(cubes), "Len cubes to check", len(cubes_to_check))
    # print("Len list", len(list_of_keys))
    list_of_keys = list(cubes_to_check.keys())
    this_key = list_of_keys.pop(0)
    to_check_status = cubes_to_check[this_key]
    # print("after pop list", len(list_of_keys))
    if to_check_status == 'on':
        is_this_key_completely_inside = check_completely_inside(cubes, this_key)
        if is_this_key_completely_inside:
            # print("This key is completely inside", this_key, len(cubes_to_check))
            del cubes_to_check[this_key]
            continue
    is_any_cube_completely_inside_this_key, cubes = check_any_completely_inside(cubes, this_key)
    if is_any_cube_completely_inside_this_key:
        # print("Some cube is completely inside", this_key, len(cubes_to_check))
        continue

    # is_any_cube_inside, cubes = check_inside_cubes(cubes, cubes_to_check, this_key)
    # if is_any_cube_inside:
    #     print("cube cube inside", this_key)
    #     print("current cubes", cubes)
    #     continue
    # is_cube_to_check_inside, cubes_to_check = check_inside_cube_to_check(cubes, cubes_to_check, this_key)
    # if is_cube_to_check_inside:
    #     list_of_keys = list(cubes_to_check.keys())
    #     print("cube to check inside", this_key)
    #     continue
    is_intersecting, new_cubes, cube_to_delete = check_intersecting(cubes, this_key , cubes_to_check[this_key])
    if is_intersecting:
        # list_of_cubes = sorted([cube for cube in cubes], key=lambda x:x[0])

        # for cube in list_of_cubes:
        old_volume = 0
        for old_cube in cube_to_delete:
            cubes.remove(old_cube)
            # print("removing", old_cube)
            old_volume += compute_volume(old_cube)
        #     print(cube, compute_volume(cube))
        new_volume = 0
        for new_cube in new_cubes:
            cubes.add(new_cube)
            new_volume += compute_volume(new_cube)
            # print("adding", new_cube)

        # print("old volume", old_volume, "new volume", new_volume)

        # print("is intersecting", this_key)
        # print("number of cubes outputed", len(new_cubes))
        pass
    if not is_intersecting:
        del cubes_to_check[this_key]
        if to_check_status == 'on':
            # print("not intersecting, adding key", this_key)
            cubes.add(this_key)


for line in lines_list:
    status = line.split()[0]
    ranges = [int(value) for value in re.findall(r'-?\d+', line.split()[1])]
    cubes_to_check[tuple(ranges)] = status

list_of_cubes = list(cubes_to_check.keys())
# print(list_of_cubes[0])
# print(list_of_cubes[1])
# for cube in cubes:
#     print(cube)
#     if not (check_cube_inside(list_of_cubes[0], cube) or check_cube_inside(list_of_cubes[1], cube)):
#         print("Not inside", cube, compute_volume(cube))
#     if check_completely_inside(list_of_cubes, cube):
#         print("completely inside", cube, compute_volume(cube))


# print(len(cubes))

volume = sum([compute_volume(cube) for cube in cubes])
# print([compute_volume(cube) for cube in cubes])
print("Part 1", volume_1)
print("Part 2", volume)

# for cube_range_to_check in cubes_to_check.keys():
#      is_this_inside(cube_range_to_check, cubes):

#     elif is_him_inside(cube_range_to_check, cubes):
#     is_intersecting(cubes, cube_range, cubes_to_check[cube_range])

# print("Part 2", len(cubes))


#     print(ranges)
