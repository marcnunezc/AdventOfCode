from collections import defaultdict

def process_vent_1(diagram, line):
    pos1,pos2 = line.split('->')
    x1,y1 = (int(pos) for pos in pos1.split(','))
    x2,y2 = (int(pos) for pos in pos2.split(','))
    if x2==x1: # vertical
        dif = 1 if y2 > y1 else -1
        pos = y1
        while not pos == y2:
            diagram[(x1,pos)] += 1
            pos += dif
        diagram[(x1,pos)] += 1
    elif y2==y1: # horizontal
        dif = 1 if x2 > x1 else -1
        pos = x1
        while not pos == x2:
            diagram[(pos,y1)] += 1
            pos += dif
        diagram[(pos,y1)] += 1

def process_vent_2(diagram, line):
    pos1,pos2 = line.split('->')
    x1,y1 = (int(pos) for pos in pos1.split(','))
    x2,y2 = (int(pos) for pos in pos2.split(','))
    dif_y = 1 if y2 > y1 else -1 if y1 > y2 else 0
    dif_x = 1 if x2 > x1 else -1 if x1 > x2 else 0
    pos_x,pos_y = x1,y1
    while not (pos_x == x2 and pos_y == y2):
        diagram[(pos_x,pos_y)] += 1
        pos_x += dif_x
        pos_y += dif_y
    diagram[(pos_x,pos_y)] += 1


if __name__ == '__main__':
    lines_list = open('input.txt', 'r').read().splitlines()
    diagram = defaultdict(lambda: 0)
    for line in lines_list:
        process_vent_1(diagram, line)
    print("Part 1", sum(value>=2 for value in diagram.values()))

    diagram = defaultdict(lambda: 0)
    for line in lines_list:
        process_vent_2(diagram, line)

    print("Part 2", sum(value>=2 for value in diagram.values()))