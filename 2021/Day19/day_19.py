import time

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
            # for ra,rb in [(2,-1), (-2,-1), (-2,1), (-1,2)]:
            for ra,rb in [(1,2), (2,-1), (-1,-2), (-2,1), (-2, -1), (1,-2),(-1,2),(2,1)]:
                rotation = [facing[i]]
                # rotation = [facing[0]]
                sign_a = 1 if ra > 0 else -1
                sign_b = 1 if rb > 0 else -1
                # rotation.append(sign_a*facing[abs(ra)])
                rotation.append(sign_a*facing[aux_i[abs(ra)-1]])
                # rotation.append(sign_a*facing[1])
                # rotation.append(sign_a*facing[2])
                # rotation.append(sign_b*facing[abs(rb)])
                rotation.append(sign_b*facing[aux_i[abs(rb)-1]])
                orientations.append(rotation)
    return orientations

# def compute_translation(scanner_0, scanner_1):
#     for i,line in enumerate(scanner_0):
#         for line1 in scanner_1[0:6]:
#             translation = [ x-y for x,y in zip(line, line1)]
#             translated_1 = [[x+y for x,y in zip(line, translation)] for line in scanner_1]
#             if sum([beacon in scanner_0 for beacon in translated_1])>=12:
#                 return translation
#     return None

def compute_translation(scanner_0, value0, scanner_1):
    for value1 in scanner_1:
        translation = [ x-y for x,y in zip(value0, value1)]
        all_translated_1 =  [[x+y for x,y in zip(line, translation)] for line in scanner_1]
        if sum([beacon in scanner_0 for beacon in all_translated_1])>=12:
            return translation
    return None

def compute_rotations(orientation, scanner):
    return [[beacon[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])] for beacon in scanner]

def search_down(i,connecitvity_map,communication=[]):
    for j in connectivity_map[i]:
        if j==0:
            communication.append(j)
            print(communication)
            return communication
        elif j not in communication:
            communication.append(j)
            return search_down(j, connecitvity_map, communication)

def generate_communication_map(connecitvity_map):
    communication_map = {}
    for i in connecitvity_map.keys():
        if 0 in connectivity_map[i]:
            communication_map[i] = [0]
        else:
            print("Computing map for", i)
            communication_map[i] = search_down(i,connectivity_map, [])
            print(communication_map[i])
    return communication_map

def compute_connectivity(i,j,rotated_beacons, scanner_j, connecitvity_map, translation_map, orientation_map):
    for beacon_j in scanner_j:
        translation = compute_translation(scanner_j, beacon_j, rotated_beacons)
        if translation is not None:
            connectivity_map[i].add(j)
            translation_map[(i,j)] = translation
            orientation_map[(i,j)] = orientation
            return connectivity_map, translation_map, orientation_map, True
    return connectivity_map, translation_map, orientation_map, False

lines_list = open('test3.txt').read().splitlines()
scanners = read_input(lines_list)

orientations = compute_orientations()
connectivity_map = {}
translation_map = {}
orientation_map = {}

for i,scanner in enumerate(scanners):
    if i == 0:
        continue
    connectivity_map[i] = set()
    trans_time = 0
    rot_time = 0
    print("Computing connecitvity for scanner {}".format(i))
    for j,scanner_j in enumerate(scanners):
        if i == j:
            continue
        for orientation in orientations:
            ini_time = time.time()
            rotated_beacons = compute_rotations(orientation, scanner)
            rot_time += time.time()-ini_time
            ini_time = time.time()
            connectivity_map, translation_map, orientation_map, found = compute_connectivity(i,j,rotated_beacons,scanner_j, connectivity_map,translation_map,orientation_map)
            trans_time += time.time()-ini_time
            if found:
                break

    print("Time rotation {}".format(rot_time))
    print("Time trans {}".format(trans_time))

print(connectivity_map)
communication_map = generate_communication_map(connectivity_map)
print(communication_map)
stop
print(translation_map)
print(orientation_map)
#
all_beacons = {(beacon[0],beacon[1],beacon[2]) for beacon in scanners[0]}
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
all_beacons = sorted(all_beacons, key=lambda x: x[0])
# for line in all_beacons:
    # print(line)
print("Part 1",len(all_beacons))

#  matched_beacons = {}
# for i_scan, connections in connectivity_map.items():
#     scanner=scanners[i_scan]
#     for j_scan in connections:
#         # if (i_scan,j_scan) in visited_pairs or (j_scan,i_scan) in visited_pairs:
#             # continue
#         # visited_pairs.add((i_scan,j_scan))
#         scanner_j = scanners[j_scan]
#         translation = translation_map[(i_scan,j_scan)]
#         orientation = orientation_map[(i_scan,j_scan)]
#         rotated_beacons = compute_rotations(orientation, scanner)
#         translated_beacons = [[x+y for x,y in zip(beacon, translation)] for beacon in rotated_beacons]
#         for beacon in translated_beacons:
#             if beacon in scanner_j:
#                 # print("prebeacon", beacon,i_scan, j_scan)

#                 if not j_scan == 0:
#                     min_connection = min(connectivity_map[j_scan])
#                     current_connection = j_scan
#                     while not min_connection==0:
#                         translation = translation_map[(current_connection,min_connection)]
#                         orientation = orientation_map[(current_connection,min_connection)]
#                         rotated_beacon=[beacon[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])]
#                         # translation = [translation[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])]
#                         beacon=[x+y for x,y in zip(rotated_beacon, translation)]
#                         current_connection = min_connection
#                         min_connection = min(connectivity_map[min_connection])
#                     translation = translation_map[(current_connection,min_connection)]
#                     orientation = orientation_map[(current_connection,min_connection)]
#                     # translation = [translation[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])]
#                     rotated_beacon=[beacon[abs(i)-1]*fact for i, fact in zip(orientation, [1 if x>0 else -1 for x in orientation])]
#                     beacon=[x+y for x,y in zip(rotated_beacon, translation)]
#                 print(beacon, i_scan, j_scan)
#                 matched_beacons.add((beacon[0],beacon[1],beacon[2]))
#                 matched_beacons_list.append((beacon[0],beacon[1],beacon[2]))