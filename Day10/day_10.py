lines_list =[int(line.strip()) for line in open("input.txt").read().splitlines()]
# Adding built-in joltage 
lines_list.append(max(lines_list)+3)

def CheackAndReturnJolt(current_jolt):
    for i in [1,2,3]:
        new_jolt = current_jolt+i
        if new_jolt in lines_list:
            return new_jolt

jolt = 0
jolt_diff_list = []
while (jolt < max(lines_list)):
    new_jolt = CheackAndReturnJolt(jolt)
    jolt_diff_list.append(new_jolt - jolt)
    jolt = new_jolt
get_occurances = lambda x: len([i for i in jolt_diff_list if i == x])
print("Part 1 solution", get_occurances(1)*get_occurances(3))


# Construct dict with combinations
jolt = 0
combinations = 0
main_dict_with_combinations = {}
lines_list.insert(0,0)
for jolt in lines_list:
    main_dict_with_combinations[jolt] = set()
    for i in [1,2,3]:
        new_jolt = jolt+i
        if new_jolt in lines_list:
            main_dict_with_combinations[jolt].add(new_jolt)

# EXPENSIVE, NOT USED
def RecursivelyCountOccurances(source_key):
    this_len = 0
    if len(main_dict_with_combinations[source_key])>0:
        for child in main_dict_with_combinations[source_key]:
            this_len += RecursivelyCountOccurances(child)
        return this_len
    else:
        return 1
# EXPENSIVE, NOT USED
# print("Part 2 solution", RecursivelyCountOccurances(0))

dict_with_occurances = {}
dict_with_occurances[lines_list[-1]] = 1
for key, value in sorted(main_dict_with_combinations.items())[::-1][1:]:
    this_len = 0
    for jolt in value:
        this_len += dict_with_occurances[jolt]
    dict_with_occurances[key] = this_len
    
print("Part 2 solution", dict_with_occurances[0])
