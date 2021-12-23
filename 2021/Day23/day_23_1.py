import re
import time
from collections import defaultdict
def pretty_print(room_map):
    for line in room_map:
        print("".join(line))
    print()

forbidden_spots = [[0,3], [0,5], [0,7], [0,9]]
cost = {"A": 1,"B": 10,"C": 100,"D": 1000}
destination_room = {"A": 3,"B": 5,"C": 7,"D": 9}

def is_good_solution(current_room, pos):
    char = current_room[pos[0]][pos[1]]
    # print(len(current_room))
    is_already_good_solution = False
    for i in range(len(current_room)-1, pos[0]-1, -1):
        if char == 'A' and pos[1] == 3:
            if current_room[i][pos[1]] == char:
                is_already_good_solution = True
        elif char == 'B'  and pos[1]==5:
            if current_room[i][pos[1]] == char:
                is_already_good_solution = True
        elif char == 'C'  and pos[1]==7:
            if current_room[i][pos[1]] == char:
                is_already_good_solution = True
        elif char == 'D'  and pos[1]==9:
            if current_room[i][pos[1]] == char:
                is_already_good_solution = True

        if not is_already_good_solution:
            return False
    return True

def move(room_map, ini_pos, destination_pos):
    current_room_map = [[char for char in line] for line in room_map]

    if is_good_solution(current_room_map, ini_pos):
        return None, -1

    if destination_pos in forbidden_spots or current_room_map[destination_pos[0]][destination_pos[1]]=="#":
        return None,-1
        raise(Exception("Cant move to forbidden spot", destination_pos))

    if not current_room_map[destination_pos[0]][destination_pos[1]] == '.':
        return None,-1
        raise(Exception("Occupied destination spot"))

    if ini_pos[0] == 0 and destination_pos[0]==0:
        return None,-1
        raise(Exception("Cant stay in hallway"))

    if ini_pos[1] == destination_pos[1]:
        return None,-1
        raise(Exception("Cant move vertically only"))

    if current_room_map[ini_pos[0]][ini_pos[1]] == '.':
        return None,-1
        raise(Exception("Cant move empty space"))
    else:
        char = current_room_map[ini_pos[0]][ini_pos[1]]

    if destination_pos[0] > 0 and not destination_pos[1] == destination_room[char]:
        return None,-1
        raise(Exception("Cant move to this room"))

    if destination_pos[0] > 0:
        for i in range(destination_pos[0]+1, len(current_room_map)):
            if not current_room_map[i][destination_pos[1]] == char:
                return None,-1
                raise(Exception("Cant move here as bottom is not solved"))

    moves=0
    current_pos = [ini_pos[0], ini_pos[1]]
    # print("Starting pos", current_pos)
    for i in range(abs(ini_pos[0]-0)):
        moves += 1
        current_pos[0] -= 1
        if not current_room_map[current_pos[0]][current_pos[1]] == '.':
            return None, -1

    for i in range(abs(ini_pos[1]-destination_pos[1])):
        moves += 1
        current_pos[1] += 1  if ini_pos[1] < destination_pos[1] else -1
        if not current_room_map[current_pos[0]][current_pos[1]] == '.':
            return None, -1
    for i in range(destination_pos[0]):
        moves += 1
        current_pos[0] += 1
        if not current_room_map[current_pos[0]][current_pos[1]] == '.':
            return None, -1

    current_room_map[destination_pos[0]][destination_pos[1]] = char
    current_room_map[ini_pos[0]][ini_pos[1]] = '.'

    return current_room_map, moves*cost[char]

def compute_candidate_starting_pos(room_map):
    return [aux_point for aux_point in get_available_points(room_map) if room_map[aux_point[0]][aux_point[1]] != '.']

def get_current_landing_points(room_map):
    return [aux_point for aux_point in  get_available_points(room_map) if room_map[aux_point[0]][aux_point[1]] == '.']

def neighbour_maps(current_tupled_map, visited):
    current_map = [list(line) for line in current_tupled_map]
    candidate_starters = compute_candidate_starting_pos(current_map)
    neighbour_list = []
    for starter in candidate_starters:
        for aux_point in get_current_landing_points(current_map):
            new_map, energy = move(current_map, starter, aux_point)
            if energy != -1:
                new_tuple = tuple(tuple(line) for line in new_map)
                if new_tuple not in visited:
                    neighbour_list.append((new_tuple, energy))
    return neighbour_list

def get_available_points(room_map):
    available_points = []
    available_points.extend([[0,i] for i in range(1, 12) if [0,i] not in forbidden_spots])
    available_points.extend([[1,3], [1,5], [1,7], [1,9]])
    available_points.extend([[2,3], [2,5], [2,7], [2,9]])
    if len(room_map) > 3:
        available_points.extend([[3,3], [3,5], [3,7], [3,9]])
        available_points.extend([[4,3], [4,5], [4,7], [4,9]])
    available_points = [tuple(point) for point in available_points]
    return available_points

def solve_dijkstra(room_map):

    score = defaultdict(lambda : 1e6)
    current_node = tuple(tuple(line) for line in room_map)
    score[current_node] = 0
    visited = set()
    visited_neighs = {}
    ideal_map = get_ideal_map(room_map)
    ideal_tuple = tuple(tuple(line) for line in ideal_map)
    while not current_node == ideal_tuple:
        neighbors_list = neighbour_maps(current_node, visited)
        for neighbor, energy in neighbors_list:
            distance = score[current_node] + energy
            if distance < score[neighbor]:
                score[neighbor] = distance
                visited_neighs[neighbor] =  distance
        visited.add(current_node)
        if current_node in visited_neighs.keys():
            del visited_neighs[current_node]
        values = list( visited_neighs.values() )
        keys = list( visited_neighs.keys() )
        min_value = min( values )
        current_node=  keys[ values.index( min_value ) ]

    return score[ideal_tuple]

def get_ideal_map(room_map):
    ideal_map = [[char for char in line] for line in room_map[0:2]]
    ideal_map[1][3] = 'A'
    ideal_map[1][5] = 'B'
    ideal_map[1][7] = 'C'
    ideal_map[1][9] = 'D'
    ideal_map.append(ideal_map[1])
    if len(room_map) > 3:
        ideal_map.append(ideal_map[1])
        ideal_map.append(ideal_map[1])
    return ideal_map

if __name__=="__main__":

    start_time = time.time()

    lines_list = open("input.txt").read().splitlines()

    room_map = [ [char for char in line] for line in lines_list[1:3]]
    room_map.append(['#']*2+[char for char in lines_list[3][2:]]+['#']*2)

    print("Part 1", solve_dijkstra(room_map))
    print("Time", time.time()-start_time)
