lines_list = [line for line in open("input.txt").read().splitlines()]
print(lines_list[0])
main_dict = {}
for line in lines_list:
    words = line.split()
    main_color_tuple = (words[0], words[1])
    if words[4] == "no":
        main_dict[main_color_tuple] = {}
    else:
        n_bags = int(len(words[4:])/4)
        bag_dict
        for i_bag in range(n_bags):
            i = i_bag + 4*n_bags

        stop