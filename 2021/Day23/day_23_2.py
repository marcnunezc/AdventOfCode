from day_23_1 import *

if __name__ == "__main__":

    start_time = time.time()

    filename = "input.txt"
    lines_list = open(filename).read().splitlines()
    extra_lines = ["#D#C#B#A#","#D#B#A#C#"]

    room_map = [ [char for char in line] for line in lines_list[1:3]]
    room_map.append(['#']*2+[char for char in extra_lines[0]]+['#']*2)
    room_map.append(['#']*2+[char for char in extra_lines[1]]+['#']*2)
    room_map.append(['#']*2+[char for char in lines_list[3][2:]]+['#']*2)

    print("Part 2", solve_dijkstra(room_map))
    print("Time", time.time()-start_time)