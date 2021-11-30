lines_list = [line.split(" ") for line in open("input.txt").read().splitlines()]
memory = {}
for line in lines_list:
    line.remove("=")
    if line[0] == "mask":
        mask = {i:char for i, char in enumerate(line[1])}
    else:
        key = line[0][4:-1]
        value = bin(int(line[1]))[2:]
        str_value = '0'*(len(mask)-len(value)) + str(value)
        masked_value ="".join([mask[i] if mask[i] !="X" else str_value[i] for i in range(len(mask))])
        memory[key] = int("0b"+masked_value,2)

print("Part 1", sum(memory.values()))

import itertools
memory = {}
for line in lines_list:
    if line[0] == "mask":
        mask = {i:char for i, char in enumerate(line[1])}
    else:
        key = bin(int(line[0][4:-1]))[2:]
        value = line[1]
        str_key = '0'*(len(mask)-len(key)) + str(key)
        masked_key ="".join([mask[i] if mask[i] != "0" else str_key[i] for i in range(len(mask))])
        number_of_x = masked_key.count("X")
        for permutation in itertools.product([0,1], repeat=number_of_x):
            i = 0
            key_list = [char for char in masked_key]
            for j, char in enumerate(key_list):
                if char == "X":
                    key_list[j] = str(permutation[i])
                    i += 1
            key = "".join(key_list)
            memory[key] = int(value)
print("Part 2", sum(memory.values()))
