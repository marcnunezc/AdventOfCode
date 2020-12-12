lines_list =[list(line) for line in open("input.txt").read().splitlines()]
import copy

i_length = len(lines_list)
j_length = len(lines_list[0])
check_occup = lambda  i,j, lines: lines[i][j] == "#"
check_found = lambda  i,j, lines: lines[i][j] == "L" or lines[i][j] =="#"
check_range = lambda  i,j, lines: i in range(0, len(lines)) and j in range(0, len(lines[0]))
def check_if_surrounded(i, j, lines):
    is_surrounded_list = [check_occup(i+delta_i, j+delta_j, lines) for delta_i in [-1,0,1] for delta_j in [-1,0,1] if not abs(delta_i)+abs(delta_j)==0 and check_range(i+delta_i,j+delta_j, lines)]
    return is_surrounded_list
            
def check_if_surrounded_2(i, j, lines):
    def get_ij_on_range_and_check(range_i, range_j):
        for i_aux, j_aux in zip(range_i, range_j):
            if check_found(i_aux, j_aux, lines):
                return check_occup(i_aux, j_aux, lines)
        return False
        
    list_of_ranges=[[range(i-1,-1,-1), [j]*j_length],
                    [range(i-1,-1,-1), range(j-1,-1,-1)],
                    [range(i-1,-1,-1), range(j+1,j_length)],
                    [[i]*i_length, range(j-1,-1,-1)],
                    [[i]*i_length, range(j+1,j_length)],
                    [range(i+1,i_length), [j]*j_length],
                    [range(i+1,i_length), range(j-1,-1,-1)],
                    [range(i+1,i_length), range(j+1,j_length)]]
    is_surrounded_list = [get_ij_on_range_and_check(range_i, range_j) for range_i, range_j  in list_of_ranges]
    return is_surrounded_list

def count_seats(new_matrix):
    return sum([1 for line in new_matrix for char in line if char=="#"])

def update_matrix(old_matrix, check_func, rule):
    new_matrix=copy.deepcopy(old_matrix)
    for i, line in enumerate(old_matrix):
        for j, _ in enumerate(line):
            if old_matrix[i][j]=="L":
                if not max(check_func(i,j, old_matrix)):
                    new_matrix[i][j] = "#"
            elif old_matrix[i][j]=="#":
                if len([check for check in check_func(i,j, old_matrix) if check is True])>rule:
                    new_matrix[i][j] = "L"
    return new_matrix

old_matrix = copy.deepcopy(lines_list)
new_matrix = update_matrix(old_matrix, check_if_surrounded, 3)
while (old_matrix != new_matrix):
    old_matrix = copy.deepcopy(new_matrix)
    new_matrix = update_matrix(old_matrix, check_if_surrounded, 3)
print("Solution part 1 2249", count_seats(new_matrix))
old_matrix = copy.deepcopy(lines_list)
new_matrix = update_matrix(old_matrix, check_if_surrounded_2, 4)
while (old_matrix != new_matrix):
    old_matrix = copy.deepcopy(new_matrix)
    new_matrix = update_matrix(old_matrix, check_if_surrounded_2, 4)
print("Solution part 2 2023", count_seats(new_matrix))