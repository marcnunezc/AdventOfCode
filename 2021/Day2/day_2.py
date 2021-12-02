instructions = [[line.split()[0],int(line.split()[1])] for line in open('input.txt', 'r').read().splitlines()]
depth = 0
horizontal = 0
for instruction in instructions:
    if instruction[0] == "forward":
        horizontal += instruction[1]
    elif instruction[0] == "down":
        depth += instruction[1]
    elif instruction[0] == "up":
        depth -= instruction[1]
    else:
        raise(Exception("Invalid instruction"))

print("Day 1", depth*horizontal)

depth = 0
horizontal = 0
aim = 0
for instruction in instructions:
    if instruction[0] == "forward":
        horizontal += instruction[1]
        depth += instruction[1]*aim
    elif instruction[0] == "down":
        aim += instruction[1]
    elif instruction[0] == "up":
        aim -= instruction[1]
    else:
        raise(Exception("Invalid instruction"))

print("Day 2", depth*horizontal)