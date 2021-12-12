from collections import defaultdict
import time

def read_input(filename):
    lines_list = open(filename).read().splitlines()
    caves=defaultdict(set)
    lower_case = set()
    for line in lines_list:
        start, end = line.split('-')
        caves[start].add(end)
        if not start == "start":
            caves[end].add(start)
        if start.islower() and not start == 'start':
            lower_case.add(start)
        if end.islower() and not end == 'end' and not end == 'start':
            lower_case.add(end)
    return caves, lower_case

def next_path(list_of_paths, starting_path, key, caves, lower_case=None):
    if key == 'end':
        list_of_paths.append(starting_path)
        return
    for cave in caves[key]:
        new_path = [cave for cave in starting_path]
        if cave == lower_case:
            if new_path.count(cave) < 2:
                new_path.append(cave)
                next_path(list_of_paths, new_path, cave, caves, lower_case)
        else:
            if not (cave.islower() and cave in new_path):
                new_path.append(cave)
                next_path(list_of_paths, new_path, cave, caves, lower_case)


if __name__ == '__main__':
    caves, lower_case = read_input("input.txt")
    list_of_paths =  []
    for cave in caves["start"]:
        path =["start", cave]
        next_path(list_of_paths, path, cave, caves)
    print("Part 1", len(list_of_paths))
    ini_time = time.time()
    list_of_paths =  []
    for lower in lower_case:
        for cave in caves["start"]:
            path =["start", cave]
            next_path(list_of_paths, path, cave, caves, lower)
    non_duplicate_list = []
    for path in list_of_paths:
        if path not in non_duplicate_list:
            non_duplicate_list.append(path)
    print("Part 2", len(non_duplicate_list), time.time() - ini_time)
