lines_list = open("input.txt").read().splitlines()

aux_dict = {}
counts = 0
for line in lines_list:
    if line == "":
        counts += len(aux_dict.keys())
        aux_dict = {}
    else:
        for char in line:
            aux_dict[char] = 1
counts += len(aux_dict.keys())
print("Part 1 number of counts", counts)

counts = 0
aux_dict = {}
is_first_line = True
for line in lines_list:
    if line == "":
        counts += len(aux_dict.keys())
        is_first_line = True
    else:
        if is_first_line:
            aux_dict = {char:1 for char in line}
        else:
            if not len(aux_dict) == 0:
                aux_dict = {char: 1 for char in line if char in aux_dict.keys()}
        is_first_line = False
counts += len(aux_dict.keys())
print("Part 2 number of counts", counts)