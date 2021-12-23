import re
import copy
from collections import defaultdict
def pretty_print(room_map):
    for line in room_map:
        print("".join(line))
    print()



def is_good_solution(current_room, char, pos):
    if char == 'A':
        return (pos[0] == 2 and pos[1] == 3) or (current_room[1][3]=='A' and (pos[0] == 2 and pos[1] == 3))
    elif char == 'B':
        return (pos[0] == 2 and pos[1] == 5) or (current_room[1][5]=='B'  and (pos[0] == 2 and pos[1] == 5))
    elif char == 'C':
        return (pos[0] == 2 and pos[1] == 7) or (current_room[1][7]=='C'  and (pos[0] == 2 and pos[1] == 7))
    elif char == 'D':
        return (pos[0] == 2 and pos[1] == 9) or (current_room[1][9]=='D' and (pos[0] == 2 and pos[1] == 9))
    else:
        raise(Exception("Invalid char", char))

def move(room_map, ini_pos, destination_pos):
    current_room_map = copy.deepcopy(room_map)
    if is_good_solution(current_room_map, current_room_map[ini_pos[0]][ini_pos[1]], ini_pos):
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

    if destination_pos[0] == 1:
        if not current_room_map[2][destination_pos[1]] == char:
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

def check_if_board_ok(room_map):
    return room_map[1][3] == 'A' and room_map[1][5] == 'B' and room_map[1][7] == 'C' and room_map[1][9] == 'D' and room_map[2][3] == 'A' and room_map[2][5] == 'B' and room_map[2][7] == 'C' and room_map[2][9] == 'D'

def compute_candidate_starting_pos(room_map):
    candidate_points = []
    available_starters = [aux_point for aux_point in available_points if room_map[aux_point[0]][aux_point[1]] != '.']
    for point in available_starters:
        available_moves = [move(room_map, point, aux_point)[1] for aux_point in available_points]
        if any([move != -1 for move in available_moves]):
            candidate_points.append(point)
    return candidate_points


def neighbour_maps(current_tupled_map, visited):
    current_map = [list(line) for line in current_tupled_map]
    candidate_starters = compute_candidate_starting_pos(current_map)
    neighbour_list = []
    for starter in candidate_starters:
        for aux_point in available_points:
            new_map, energy = move(current_map, starter, aux_point)
            if energy != -1:
                new_tuple = tuple(tuple(line) for line in new_map)
                if new_tuple not in visited:
                    neighbour_list.append((new_tuple, energy))
    return neighbour_list

import time

import os
filename = "test.txt"
start_time = time.time()
lines_list = open(filename).read().splitlines()

forbidden_spots = [[0,3], [0,5], [0,7], [0,9]]
cost = {"A": 1,"B": 10,"C": 100,"D": 1000}
destination_room = {"A": 3,"B": 5,"C": 7,"D": 9}
energy = 0
available_points = []
available_points.extend([[0,i] for i in range(1, 12) if [0,i] not in forbidden_spots])
available_points.extend([[1,3], [1,5], [1,7], [1,9]])
available_points.extend([[2,3], [2,5], [2,7], [2,9]])
available_points = [tuple(point) for point in available_points]

room_map = [ [char for char in line] for line in lines_list[1:3]]
room_map.append(['#']*2+[char for char in lines_list[3][2:]]+['#']*2)
energy=0

ideal_map = [[char for char in line] for line in room_map]
ideal_map[1][3] = 'A'
ideal_map[1][5] = 'B'
ideal_map[1][7] = 'C'
ideal_map[1][9] = 'D'
ideal_map[2][3] = 'A'
ideal_map[2][5] = 'B'
ideal_map[2][7] = 'C'
ideal_map[2][9] = 'D'
pretty_print(ideal_map)
ideal_tuple = tuple(tuple(line) for line in ideal_map)

score = defaultdict(lambda : 1e6)
pretty_print(room_map)
current_node = tuple(tuple(line) for line in room_map)
score[current_node] = 0
visited = set()
visited_neighs = set()
neighbour_time = 0
update_time = 0
while not current_node == ideal_tuple:
    ini_time = time.time()
    neighbors_list = neighbour_maps(current_node, visited)
    neighbour_time += time.time() - ini_time
    ini_time = time.time()
    for neighbor, energy in neighbors_list:
        distance = score[current_node] + energy
        if distance < score[neighbor]:
            score[neighbor] = distance
        visited_neighs.add(neighbor)
    visited.add(current_node)
    if current_node in visited_neighs:
        visited_neighs.remove(current_node)
    current_node = min(visited_neighs, key=lambda x: score[x])
    update_time += time.time() - ini_time
print("Part 1", score[ideal_tuple])
print("Time", time.time()-start_time)
print("neighbour time ", neighbour_time)
print("update time ", update_time)
