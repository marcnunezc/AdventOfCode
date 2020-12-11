lines_list =[list(line) for line in open("input.txt").read().splitlines()]
import copy

i_length = len(lines_list) - 1
j_length = len(lines_list[0]) -1
check_occup = lambda  i,j, lines: lines[i][j] == "#"
check_found = lambda  i,j, lines: lines[i][j] == "L" or lines[i][j] =="#"
def check_if_surrounded(i, j, lines):
    is_surrounded_list = []
    if i-1 >= 0:
        is_surrounded_list.append(check_occup(i-1, j, lines))
        if j-1 >= 0:
            is_surrounded_list.append(check_occup(i-1, j-1, lines))
        if j+1 <= j_length:
            is_surrounded_list.append(check_occup(i-1, j+1, lines))
    if j-1 >= 0:
        is_surrounded_list.append(check_occup(i, j-1, lines))
    if j+1 <= j_length:
        is_surrounded_list.append(check_occup(i, j+1, lines))
    if i+1 <= i_length:
        is_surrounded_list.append(check_occup(i+1, j, lines))
        if j-1 >= 0:
            is_surrounded_list.append(check_occup(i+1, j-1, lines))
        if j+1 <= j_length:
            is_surrounded_list.append(check_occup(i+1, j+1, lines))
    return is_surrounded_list
def check_if_surrounded_2(i, j, lines):
    is_surrounded_list = []
    if i-1 >= 0:
        for i_aux in range(i-1,-1,-1):
            if check_found(i_aux, j, lines):
                    is_surrounded_list.append(check_occup(i_aux, j, lines))
                    break
        if j-1 >= 0:
            for i_aux, j_aux in zip(range(i-1,-1,-1), range(j-1,-1,-1)):
                if check_found(i_aux, j_aux, lines):
                    is_surrounded_list.append(check_occup(i_aux, j_aux, lines))
                    break
        if j+1 <= j_length:
            for i_aux, j_aux in zip(range(i-1,-1,-1), range(j+1,j_length+1)):
                if check_found(i_aux, j_aux, lines):
                    is_surrounded_list.append(check_occup(i_aux, j_aux, lines))
                    break
    if j-1 >= 0:
        for j_aux in range(j-1,-1,-1):
            if check_found(i, j_aux, lines):
                is_surrounded_list.append(check_occup(i, j_aux, lines))
                break
    if j+1 <= j_length:
        for j_aux in range(j+1,j_length+1):
            if check_found(i, j_aux, lines):
                is_surrounded_list.append(check_occup(i, j_aux, lines))
                break
    if i+1 <= i_length:
        for i_aux in range(i+1,i_length+1):
            if check_found(i_aux, j, lines):
                is_surrounded_list.append(check_occup(i_aux, j, lines))
                break
        if j-1 >= 0:
            for i_aux, j_aux in zip(range(i+1,i_length+1), range(j-1,-1,-1)):
                if check_found(i_aux, j_aux, lines):
                    is_surrounded_list.append(check_occup(i_aux, j_aux, lines))
                    break
        if j+1 <= j_length:
            for i_aux, j_aux in zip(range(i+1,i_length+1), range(j+1,j_length+1)):
                if check_found(i_aux, j_aux, lines):
                    is_surrounded_list.append(check_occup(i_aux, j_aux, lines))
                    break
    return is_surrounded_list

old_matrix = copy.deepcopy(lines_list)
new_matrix = copy.deepcopy(lines_list)
new_matrix[0][0] = "d"
while (True):
    for i, line in enumerate(old_matrix):
        for j, _ in enumerate(line):
            if old_matrix[i][j]=="L":
                is_surrounded = max(check_if_surrounded(i,j, old_matrix))
                if not is_surrounded:
                    new_matrix[i][j] = "#"
            elif old_matrix[i][j]=="#":
                is_surrounded_list = [check for check in check_if_surrounded(i,j, old_matrix) if check is True]
                if len(is_surrounded_list)>3:
                    new_matrix[i][j] = "L"

    if old_matrix==new_matrix:
        break
    old_matrix = copy.deepcopy(new_matrix)
def count_seats(new_matrix):
    return sum([1 for line in new_matrix for char in line if char=="#"])

print("Solution part 1", count_seats(new_matrix))

old_matrix = copy.deepcopy(lines_list)
new_matrix = copy.deepcopy(lines_list)
new_matrix[0][0] = "d"
while (True):
    for i, line in enumerate(old_matrix):
        for j, _ in enumerate(line):
            if old_matrix[i][j]=="L":
                is_surrounded = max(check_if_surrounded_2(i,j, old_matrix))
                if not is_surrounded:
                    new_matrix[i][j] = "#"
            elif old_matrix[i][j]=="#":
                is_surrounded_list = [check for check in check_if_surrounded_2(i,j, old_matrix) if check is True]
                if len(is_surrounded_list)>4:
                    new_matrix[i][j] = "L"
    if old_matrix==new_matrix:
        break
    old_matrix = copy.deepcopy(new_matrix)
def count_seats(new_matrix):
    return sum([1 for line in new_matrix for char in line if char=="#"])

print("Solution part 2", count_seats(new_matrix))