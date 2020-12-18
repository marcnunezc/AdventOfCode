
def find_next_closing_index(line):
    next_open_index = line[1:].find("(") + 1
    close_index = line.find(")") + 1
    if next_open_index < close_index  and not next_open_index < 0:
        close_index = find_next_closing_index(line[close_index:]) + close_index
    return close_index

def evaluate_string(line, line_operator):
    open_index = line.find("(")

    if open_index != -1:
        close_index = find_next_closing_index(line[open_index:]) + open_index
    else:
        return line_operator(line)
    result = evaluate_string(line[(open_index+1):(close_index-1)], line_operator)
    while not result.isdigit():
        result = evaluate_string(result, line_operator)
    return evaluate_string(line.replace(line[(open_index):(close_index)], result), line_operator)

def part_1_operator(line):
    operation = line.split(" ")
    result = int(operation[0])
    i = 1
    while (i < len(operation)):
        if operation[i] == '+':
            result += int(operation[i+1])
        elif operation[i] == '*':
            result *= int(operation[i+1])
        i += 2
    return str(result)


def part_2_operator(line):
    if "*" in line:
        operation = line.split("*")
        result = 1
        for value in operation:
            if not value.isdigit():
                value = int(evaluate_string(value, part_2_operator))
            result *= value
        return str(result)

    else:
        operation = [int(char) for char in line.split("+")]
        return str(sum(operation))



lines_list =open("input.txt").read().splitlines()
print("Part 1", sum([int(evaluate_string(line, part_1_operator)) for line in lines_list]))
print("Part 2", sum([int(evaluate_string(line, part_2_operator)) for line in lines_list]))