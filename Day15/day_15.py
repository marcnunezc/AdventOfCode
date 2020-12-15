number_list =[int(number) for number in open("input.txt").read().splitlines()[0].split(",")]
dict_of_indices = { number:[i] for i, number in enumerate(number_list)}

def add_number_to_dict(number_list, number, i):
    if not number in dict_of_indices.keys():
        dict_of_indices[number]=[]
    dict_of_indices[number].append(i)
    if len(dict_of_indices[number]) > 2:
        dict_of_indices[number].pop(0)

def compute_ith_value(stop_criteria):
    i = len(number_list)
    prev_value = number_list[i-1]
    while (i < stop_criteria):
        prev_indices = dict_of_indices[prev_value]
        prev_value = prev_indices[1] - prev_indices[0] if len(prev_indices) > 1 else 0
        add_number_to_dict(number_list, prev_value, i)
        i += 1
    return prev_value

stop_criteria = 2020
print("Part 1", compute_ith_value(stop_criteria))
dict_of_indices = {number:[i] for i, number in enumerate(number_list)}
stop_criteria = 30000000
print("Part 2", compute_ith_value(stop_criteria))