from itertools import product
import re

def check_outside(ranges):
    return ranges[0] < -50 or ranges[1] > 50 or ranges[2] < -50 or ranges[3] > 50 or ranges[4] < -50 or ranges[5] > 50

def check_inside(key1, key2, to_check1, to_check_2):
    return key1 <= to_check1 <= key2 and key1 <= to_check_2 <= key2

def check_intersect(key1, key2, to_check1, to_check_2):
    return (key1 <= to_check1 <= key2) or (key1 <= to_check_2 <= key2) or (to_check1 <= key1 <= to_check_2)

def check_cube_completely_inside(base, to_check):
    is_x_inside = check_inside(base[0], base[1], to_check[0], to_check[1])
    is_y_inside = check_inside(base[2], base[3], to_check[2], to_check[3])
    is_z_inside = check_inside(base[4], base[5], to_check[4], to_check[5])
    return is_x_inside and is_y_inside and is_z_inside

def append_split(split_axis, a, b, c, d):

    if not a==b:
        split_axis.append(tuple([a,b-1]))
    split_axis.append(tuple([b,c]))
    split_axis.append(tuple([c+1,d]))


def get_axis_ranges(range0, range1):
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

    return split_axis

def get_ranges_from_intersecting_cubes(range0, range1):
    split_x_ranges = get_axis_ranges(range0[0:2], range1[0:2])
    split_y_ranges = get_axis_ranges(range0[2:4], range1[2:4])
    split_z_ranges = get_axis_ranges(range0[4:6], range1[4:6])
    ranges = []
    ranges.append(list(range(0, len(split_x_ranges))))
    ranges.append(list(range(0, len(split_y_ranges))))
    ranges.append(list(range(0, len(split_z_ranges))))

    return split_x_ranges, split_y_ranges, split_z_ranges, ranges

def check_intersecting(cubes, ranges_to_check, status_to_check):
    new_cubes = set()
    is_intersecting = False
    cubes_to_delete = set()
    for cube_ranges in cubes:
        is_x_intersecting = check_intersect(cube_ranges[0], cube_ranges[1], ranges_to_check[0], ranges_to_check[1]) or check_inside(cube_ranges[0], cube_ranges[1], ranges_to_check[0], ranges_to_check[1]) or check_inside(ranges_to_check[0], ranges_to_check[1], cube_ranges[0], cube_ranges[1])
        is_y_intersecting = check_intersect(cube_ranges[2], cube_ranges[3], ranges_to_check[2], ranges_to_check[3]) or check_inside(cube_ranges[2], cube_ranges[3], ranges_to_check[2], ranges_to_check[3]) or check_inside(ranges_to_check[2], ranges_to_check[3], cube_ranges[2], cube_ranges[3])
        is_z_intersecting = check_intersect(cube_ranges[4], cube_ranges[5], ranges_to_check[4], ranges_to_check[5]) or check_inside(cube_ranges[4], cube_ranges[5], ranges_to_check[4], ranges_to_check[5]) or check_inside(ranges_to_check[4], ranges_to_check[5], cube_ranges[4], cube_ranges[5])

        if is_x_intersecting and is_y_intersecting and is_z_intersecting:
            split_x_ranges, split_y_ranges, split_z_ranges, ranges = get_ranges_from_intersecting_cubes(cube_ranges, ranges_to_check)
            for i, j, k in product(*ranges):
                cube_to_add = tuple(split_x_ranges[i] + split_y_ranges[j] + split_z_ranges[k])

                if status_to_check == 'on':
                    is_in_base = check_cube_completely_inside(cube_ranges, cube_to_add)
                    if is_in_base:
                        new_cubes.add(cube_to_add)
                elif status_to_check == 'off':
                    is_in_base = check_cube_completely_inside(cube_ranges, cube_to_add)
                    is_in_candidate = check_cube_completely_inside(ranges_to_check, cube_to_add)
                    if is_in_base and not is_in_candidate:
                        new_cubes.add(cube_to_add)
            cubes_to_delete.add(cube_ranges)
            return True, new_cubes, cubes_to_delete
    return False, new_cubes,set()

def check_completely_inside(cubes, key):
    for cube_range in cubes:
        is_x_inside = check_inside(cube_range[0], cube_range[1], key[0], key[1])
        is_y_inside = check_inside(cube_range[2], cube_range[3], key[2], key[3])
        is_z_inside = check_inside(cube_range[4], cube_range[5], key[4], key[5])
        if is_x_inside and is_y_inside and is_z_inside:
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
            any_inside = True
            pass
        else:
            new_cubes.add(cube_range)

    return any_inside, new_cubes

def compute_volume(cube):
    return len(range(cube[0], cube[1]+1))* len(range(cube[2], cube[3]+1))*len(range(cube[4], cube[5]+1))

if __name__ == '__main__':
    import time
    start_time = time.time()

    lines_list = open('input.txt').read().splitlines()
    cube_on = set()
    for line in lines_list:
        status = line.split()[0]
        ranges =[int(value) for value in re.findall(r'-?\d+', line.split()[1])]
        if check_outside(ranges):
            continue
        for x in range(ranges[0], ranges[1]+1):
            for y in range(ranges[2], ranges[3]+1):
                for z in range(ranges[4], ranges[5]+1):
                        if status == 'on':
                            cube_on.add((x,y,z))
                        else:
                            cube_on.discard((x,y,z))
    volume_1 = len(cube_on)
    print("Part 1", len(cube_on))

    lines_list = open('input.txt').read().splitlines()
    cubes = set()
    cubes_to_check = {}
    for line in lines_list:
        status = line.split()[0]
        ranges = [int(value) for value in re.findall(r'-?\d+', line.split()[1])]
        cubes_to_check[tuple(ranges)] = status

    while len(list(cubes_to_check.keys())) > 0:
        volume = sum([len(range(cube[0], cube[1]+1))+ len(range(cube[2], cube[3]+1))+len(range(cube[4], cube[5]+1)) for cube in cubes])

        list_of_keys = list(cubes_to_check.keys())
        this_key = list_of_keys.pop(0)
        to_check_status = cubes_to_check[this_key]
        if to_check_status == 'on':
            is_this_key_completely_inside = check_completely_inside(cubes, this_key)
            if is_this_key_completely_inside:
                del cubes_to_check[this_key]
                continue
        is_any_cube_completely_inside_this_key, cubes = check_any_completely_inside(cubes, this_key)
        if is_any_cube_completely_inside_this_key:
            continue

        is_intersecting, new_cubes, cube_to_delete = check_intersecting(cubes, this_key , cubes_to_check[this_key])
        if is_intersecting:
            old_volume = 0
            for old_cube in cube_to_delete:
                cubes.remove(old_cube)
                old_volume += compute_volume(old_cube)
            new_volume = 0
            for new_cube in new_cubes:
                cubes.add(new_cube)
                new_volume += compute_volume(new_cube)
        if not is_intersecting:
            del cubes_to_check[this_key]
            if to_check_status == 'on':
                cubes.add(this_key)


    volume = sum([compute_volume(cube) for cube in cubes])
    print("Part 2", volume)
    print("Time", time.time() - start_time)