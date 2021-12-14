lines_list = [line for line in open('input.txt', 'r').read().splitlines()]
digits_list = [[line[i] for line in lines_list]  for i,_ in enumerate(lines_list[0])]
gamma = [max(digits, key=digits.count) for digits in digits_list]
eps = [min(digits, key=digits.count) for digits in digits_list]
print("Part 1:", int("".join(gamma),2)*int("".join(eps),2))

max_lines = [line for line in lines_list]
min_lines = [line for line in lines_list]
for i,_ in enumerate(lines_list[0]):
    max_digits=[line[i] for line in max_lines]
    min_digits=[line[i] for line in min_lines]
    max_common=max(max_digits, key=max_digits.count) if not max_digits.count("0") == max_digits.count("1") else "1"
    min_common=min(min_digits, key=min_digits.count) if not min_digits.count("0") == min_digits.count("1") else "0"
    if len(max_lines) > 1:
        max_lines = [line for line in max_lines if line[i] == max_common]
    if len(min_lines) > 1:
        min_lines = [line for line in min_lines if line[i] == min_common]
print("Part 2:", int("".join(max_lines[0]),2)*int("".join(min_lines[0]),2))
