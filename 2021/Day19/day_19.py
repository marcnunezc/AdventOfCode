import time
import pickle
from collections import Counter

def read_input(lines_list):
    scanners = []
    for line in lines_list:
        if "scanner" in line:
            scanner=[]
        elif line == "":
            scanners.append(scanner)
        else:
            scanner.append([int(x) for x in line.split(',')])
    scanners.append(scanner)
    return scanners

def compute_orientations(position=[1,2,3]):
    orientations = []
    for i in range(len(position)):
        for factor in [1,-1]:
            facing = [x*factor if this_i == i else x for this_i, x in enumerate(position)]
            aux_i = [j for j in range(len(position)) if j != i]
            if factor == 1:
                if i==1:
                    rotations=[(2,1), (1,-2), (-2,-1), (-1,2)]
                else:
                    rotations=[(1,2), (2,-1), (-1,-2), (-2,1)]
            else:
                if i==1:
                    rotations=[(1,2), (2,-1), (-1,-2), (-2,1)]
                else:
                    rotations=[(2,1), (1,-2), (-2,-1), (-1,2)]
            for ra,rb in rotations:
                rotation = [facing[i]]
                sign_a = 1 if ra > 0 else -1
                sign_b = 1 if rb > 0 else -1
                rotation.append(sign_a*facing[aux_i[abs(ra)-1]])
                rotation.append(sign_b*facing[aux_i[abs(rb)-1]])
                orientations.append(rotation)
    return orientations

def compute_rotations(orientation, scanner):
    return [[beacon[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])] for beacon in scanner]

def search_down(i, connecitvity_map,communication=[], previous=0):
    for j in connectivity_map[i]:
        if j == previous:
            continue
        if j==0:
            communication.append(j)
            return communication
        else:
            new_communication = communication.copy()
            new_communication.append(j)
            new_communication = search_down(j, connecitvity_map,new_communication,i)
            if 0 in new_communication:
                return new_communication
            else:
                continue
    return communication

def generate_communication_map(connecitvity_map):
    communication_map = {}
    for i in connecitvity_map.keys():
        if 0 in connecitvity_map[i]:
            communication_map[i] = [0]
        else:
            communication_map[i] = search_down(i,connectivity_map, [])
    return communication_map

def compute_connectivity(i,j,scanner,scanner_j,connectivity_map,translation_map,orientation_map):
    if i==0 or i == j:
        return connectivity_map, translation_map, orientation_map

    for orientation in orientations:
        hashed_distances = Counter()
        rotated_beacons = compute_rotations(orientation, scanner)
        for beacon_i in rotated_beacons:
            for beacon_j in scanner_j:
                distance_x = beacon_j[0]-beacon_i[0]
                distance_y = beacon_j[1]-beacon_i[1]
                distance_z = beacon_j[2]-beacon_i[2]
                hashed_distances[(distance_x, distance_y, distance_z)] += 1
                if hashed_distances[(distance_x, distance_y, distance_z)] >=12:
                    connectivity_map[i].add(j)
                    translation_map[(i,j)] = [x for x in (distance_x, distance_y, distance_z)]
                    orientation_map[(i,j)] = orientation
                    return connectivity_map, translation_map, orientation_map
    return connectivity_map, translation_map, orientation_map

start_time = time.time()
filename = "input.txt"
lines_list = open(filename).read().splitlines()
scanners = read_input(lines_list)

connectivity_map = {}
translation_map = {}
orientation_map = {}
orientations = compute_orientations()

for i,scanner in enumerate(scanners):
    connectivity_map[i] = set()
    print("Computing connecitvity for scanner {}".format(i))
    for j,scanner_j in enumerate(scanners):
        connectivity_map, translation_map, orientation_map = compute_connectivity(i,j,scanner,scanner_j,connectivity_map,translation_map,orientation_map)

communication_map = generate_communication_map(connectivity_map)
all_beacons = {(beacon[0],beacon[1],beacon[2]) for beacon in scanners[0]}
coords = [[0,0,0]]
for i_scan, scanner in enumerate(scanners[1:]):
    for beacon in scanner:
        current_connection=i_scan+1
        for next_connection in communication_map[i_scan+1]:
            translation = translation_map[(current_connection,next_connection)]
            orientation = orientation_map[(current_connection,next_connection)]
            rotated_beacon=[beacon[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])]
            beacon=[x+y for x,y in zip(rotated_beacon, translation)]
            current_connection = next_connection
        all_beacons.add((beacon[0],beacon[1],beacon[2]))
    distance = [0,0,0]
    current_connection=i_scan+1
    for next_connection in communication_map[i_scan+1]:
        translation = translation_map[(current_connection,next_connection)]
        orientation = orientation_map[(current_connection,next_connection)]
        distance=[distance[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])]
        distance = [x+y for x,y in zip(distance, translation)]
        current_connection = next_connection
    coords.append(distance)

print("Part 1",len(all_beacons))

max_distance = -1e6
for i in range(len(coords)):
    for j in range(len(coords)):
        max_distance = max(max_distance,sum([abs(x-y) for x,y in zip(coords[i], coords[j])]))
print("Part 2", max_distance)
print("Time", time.time()-start_time)