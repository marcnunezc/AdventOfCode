file_lines = open("input.txt").readlines()
count = 0
for line in file_lines:
    split_line=line.split()
    # getting min_max values
    min_value=int(split_line[0].split('-')[0])
    max_value=int(split_line[0].split('-')[1])

    required_letter = split_line[1][0]

    # check if pass is ok:
    n_apperances = split_line[2].count(required_letter)
    if n_apperances >= min_value and n_apperances<=max_value:
        count += 1

print("Valid passwords:", count)

count = 0
for line in file_lines:
    split_line=line.split()
    # getting list positions
    first_pos=int(split_line[0].split('-')[0]) - 1
    second_pos=int(split_line[0].split('-')[1]) - 1

    required_letter = split_line[1][0]

    string_to_check = split_line[2]
    if (string_to_check[first_pos] == required_letter) != (string_to_check[second_pos] == required_letter):
        count += 1
print("Valid passwords part 2:", count)
