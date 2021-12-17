import re
target_area = open('input.txt').read()
x_min, x_max, y_min, y_max = (int(value) for value in re.findall(r"-?\d+", target_area))

def is_inside(x, y):
    return x_min <= x <= x_max and y_min <= y <= y_max

high_point = -1e6
found_vels = set()
for i in range(1, x_max+1):
    for j in range(-abs(y_min), abs(y_min)):
        this_high_point = 0
        x, y = 0, 0
        vx, vy = (i, j)
        while  y >= y_min:
            x, y = x + vx, y + vy
            this_high_point = max(this_high_point, y)
            if is_inside(x, y):
                high_point = max(this_high_point, high_point)
                found_vels.add((i, j))
                break
            vx = vx-1 if vx > 0 else vx+1 if vx < 0 else 0
            vy = vy-1
print("Part 1", high_point)
print("Part 2", len(found_vels))
