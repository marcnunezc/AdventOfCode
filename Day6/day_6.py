lines_list = open("input.txt").read().split("\n\n")

counts = sum([len({char for char in questionary if char != "\n"}) for questionary in lines_list])
print("Part 1 number of counts 6565", counts)

counts = 0
for questionary in lines_list:
    aux_set = {char for char in questionary.split("\n")[0]}
    for line in questionary.split("\n")[1:]:
        if line != "":
            aux_set=aux_set.intersection({char for char in line})
    counts += len(aux_set)
    is_first_line = True
print("Part 2 number of counts 3137", counts)