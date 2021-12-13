def read_input(filename):
    lines_list = open(filename).read().splitlines()
    dots = set()
    i = 0
    while lines_list[i] != '':
        x,y = lines_list[i].split(',')
        dots.add((int(x),int(y)))
        i += 1
    i += 1
    instructions_list = []
    while i < len(lines_list):
        instruction, value = lines_list[i].split("=")
        instructions_list.append((instruction[11:], int(value)))
        i += 1
    return dots, instructions_list

def fold_paper(dots, instruction):
    max_x = max(dots, key=lambda x: x[0])[0]
    max_y = max(dots, key=lambda x: x[1])[1]
    old_dots = dots.copy()
    dots = set()
    if "y" in instruction[0]:
        for y in range(0, max_y+1):
            if y < instruction[1]:
                for x in range(0, max_x+1):
                    if (x,y) in old_dots or (x,max_y-y) in old_dots:
                        dots.add((x,y))
    if "x" in instruction[0]:
        for y in range(0, max_y+1):
            for x in range(0, max_x+1):
                if x < instruction[1]:
                    if (x,y) in old_dots or (max_x-x,y) in old_dots:
                        dots.add((x,y))
    return dots

if __name__ == "__main__":
    dots, instructions_list = read_input("input.txt")

    print("Part 1:", len(fold_paper(dots, instructions_list[0])))

    for instruction in instructions_list:
        dots = fold_paper(dots, instruction)
    print("Part 2:")
    for y in range(0, max(dots, key=lambda x: x[1])[1]+1):
        for x in range(0, max(dots, key=lambda x: x[0])[0]+1):
            if (x,y) in dots:
                print('#', end='')
            else:
                print(' ', end='')
        print()