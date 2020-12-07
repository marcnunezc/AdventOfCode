lines_list = [line for line in open("input.txt").read().splitlines()]
gold_tuple = ("shiny", "gold")

# Constructing main dict
main_dict = {}
for line in lines_list:
    words = line.split()
    main_color_tuple = (words[0], words[1])
    if words[4] == "no":
        main_dict[main_color_tuple] = {}
    else:
        n_bags = int(len(words[4:])/4)
        inner_bag_string=words[4:]
        bag_dict = {}
        for i_bag in range(n_bags):
            i = 4*(i_bag-1)
            n_inner_bag = int(inner_bag_string[i])
            bag_color_tuple = (inner_bag_string[i+1], inner_bag_string[i+2])
            bag_dict[bag_color_tuple] = n_inner_bag
        main_dict[main_color_tuple] = bag_dict

# Part 1
keys_with_gold = {key for key, value in main_dict.items() if gold_tuple in value.keys()}
all_key_set =keys_with_gold
sub_key_set = keys_with_gold
while len(sub_key_set)>0:
    sub_key_set = {key for key, value in main_dict.items() for subkey, subvalue in value.items() if subkey in sub_key_set and not key in all_key_set}
    all_key_set = all_key_set.union(sub_key_set)
print("Part 1, number of bags", len(all_key_set))

# Part 2
def RecursivelyReturnNumberOfBags(dict_bag):
    total_bags = 0
    for key, n_bags in dict_bag.items():
        dict_to_send = main_dict[key]
        if dict_to_send != {}:
            total_bags += RecursivelyReturnNumberOfBags(dict_to_send)*n_bags + n_bags
        else:
            total_bags += n_bags
    return total_bags

n_bags = RecursivelyReturnNumberOfBags(main_dict[gold_tuple])
print("Part 2, number of bags", n_bags)