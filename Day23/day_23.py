
def get_dest(current_cup, pick_up, this_dict):
    guess = current_cup-1
    while guess > 0:
        if guess in pick_up:
            guess -= 1
        else:
            return guess
    current_max = max(this_dict.keys())
    removed_max = []
    while (current_max in pick_up):
        removed_max.append([current_max, this_dict[current_max]])
        this_dict.pop(current_max)
        current_max = max(this_dict.keys())
    for key, value in removed_max:
        this_dict[key] = value
    return current_max

def play(line, moves):
    dict_line = {cup:next_cup for cup, next_cup in zip(line, line[1:])}
    dict_line[line[-1]] = line[0]
    current_cup = line[0]
    for move in range(1, int(moves + 1)):
        if move % 1e6 == 0:
            print("Current move", move)
        next_cup = current_cup
        pick_up = []
        for x in range(pick_up_range):
            cup_to_pick = next_cup
            next_cup = dict_line[cup_to_pick]
            pick_up.append(next_cup)
        last_pick_up_pointer = dict_line[pick_up[-1]]
        dict_line[current_cup] = last_pick_up_pointer
        destination =  get_dest(current_cup, pick_up, dict_line)
        destination_pointer = dict_line[destination]
        dict_line[destination] = pick_up[0]
        dict_line[pick_up[-1]] = destination_pointer
        current_cup = dict_line[current_cup]
    return dict_line


line = '459672813'

line = [int(char) for char in line]
pick_up_range = 3
moves = 100
dict_line_1 = play(line, moves)
line_1 = [1]
for x in range(len(dict_line_1.keys())):
    new_cup = dict_line_1[line_1[-1]]
    line_1.append(new_cup)
line_1=line_1[:-1]
one_index = line_1.index(1)
solution = [str(char) for char in line_1[one_index+1:]]
solution.extend([str(char) for char in line_1[:one_index]])
print("Part 1", "".join(solution))

max_cup = 1e6
line.extend(i for i in range(10, int(max_cup+1)))
moves = 1e7
dict_line_2 = play(line, moves)
first = dict_line_2[1]
second = dict_line_2[first]
print("Part 2", first*second)

