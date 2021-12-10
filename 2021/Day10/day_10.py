lines_list = open("input.txt").read().splitlines()
openers = {"(", "[", "{", "<"}
closer_map = {"(": ")", "[": "]", "{": "}", "<": ">"}
char_points = {")":3, "]":57, "}":1197, ">":25137}

failed_chars = []
to_complete_list = []
for line in lines_list:
    broken = False
    opener_list = []
    for char in line:
        if char in openers:
            opener_list.append(char)
        elif char == closer_map[opener_list[-1]]:
            opener_list.pop()
        else:
            print("Expected {}, but found {} instead".format(closer_map[opener_list[-1]], char))
            failed_chars.append(char)
            broken = True
            break
    if not broken:
        to_complete = [closer_map[char]  for char in reversed(opener_list)]
        to_complete_list.append(to_complete)
print("Part 1", sum(char_points[char] for char in failed_chars))

complete_points = {")":1, "]":2, "}":3, ">":4}
points = []
for line in to_complete_list:
    score = 0
    for char in line:
        score = score*5+complete_points[char]
    points.append(score)
print("Part 2", sorted(points)[len(points)//2])