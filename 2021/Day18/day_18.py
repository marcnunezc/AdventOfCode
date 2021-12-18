import re

def sum_numbers(num1, num2):
    if num1 == []:
        return num2
    else:
        return "".join(['['] + [num1] +[',']+ [num2] + [']'])

def check_exploding_split(line):
    count = 0
    for i, char in enumerate(line):
        if char == "[":
            count += 1
        elif char == "]":
            count -= 1
        if count > 4:
            return True, False
    if any([int(value) >= 10 for value in re.findall("\d+", line)]):
        return False, True
    return False, False

def get_first_fourth_depth(line):
    count = 0
    for i, char in enumerate(line):
        if char == "[":
            count += 1
        elif char == "]":
            count -= 1
        if count > 4:
            count = 0
            for j, char in enumerate(line[i:]):
                if char == "[":
                    count -= 1
                elif char == "]":
                    count += 1
                if count == 1:
                    return i,i+j
    return 0

def get_leftmost_index(line):
    for i, char in enumerate(reversed(line)):
        if char.isnumeric():
            return len(line)-i-1
    return 0

def get_rightmost_index(line):
    for i, char in enumerate(line):
        if char.isnumeric():
            return i
    return 0

def do_explode(line):
    i, j = get_first_fourth_depth(line)
    to_reduce = line[i:j]
    left, right =  line[:i], line[j:]
    regex = re.findall("\d+", to_reduce)
    left_regex = re.findall("\d+", left)
    right_regex = re.findall("\d+", right)
    if to_reduce[-1].isnumeric():
        result = "0,"+str(int(regex[1])+int(regex[2]))
        leftmost = get_leftmost_index(left)
        if leftmost > 0:
            subline = line[:i]
            left = subline[:(leftmost+1-len(left_regex[-1]))] + str(int(regex[0].split(',')[0])+int(left_regex[-1])) + subline[leftmost+1:]
        return left+result+right
    elif to_reduce.count("[") == 1:
        result = left[:-(len(left_regex[-1])+1)]+str(int(left_regex[-1])+int(regex[0]))+",0"+right
        rightmost = get_rightmost_index(right) + len(result) - len(right)
        if result[rightmost].isnumeric():
            return result[:rightmost] + str(int(right_regex[0])+int(regex[1]))+ result[rightmost+len(right_regex[0]):]
        else:
            return result
    else:
        result = "0,["+str(int(regex[1])+int(regex[2]))+","+regex[3]+"]"
        leftmost = get_leftmost_index(left)
        if leftmost > 0:
            subline = line[:i]
            left = subline[:(leftmost+1-len(left_regex[-1]))] + str(int(regex[0].split(',')[0])+int(left_regex[-1])) + subline[leftmost+1:]
        return left+result+right

def do_split(line):
    for i,char in enumerate(line[1:]):
        j = i+1
        if char.isnumeric() and line[j-1].isnumeric():
            number = int(line[j-1]+char)
            return line[:j-1]+"["+str(number//2)+","+str(number//2 + number%2)+"]"+line[j+1:]

def compute_sum(number_list):
    total_sum = number_list[0]
    for line in number_list[1:]:
        total_sum = sum_numbers(total_sum, line)
        is_explode, is_split = check_exploding_split(total_sum)
        while is_explode or is_split:
            if is_explode:
                total_sum = do_explode(total_sum)
            else:
                total_sum = do_split(total_sum)
            is_explode,is_split = check_exploding_split(total_sum)
    return total_sum

def to_list(this_line, i=0):
    this_list = []
    while i < len(this_line):
        char = this_line[i]
        if char == '[':
            new_list, i = to_list(this_line, i+1)
            this_list.append(new_list)
        elif char == ']':
            return this_list, i+1
        elif not char == ',':
            this_list.append(int(char))
            i += 1
        else:
            i += 1
    return this_list[0], i

def evaluate_sum(total_sum, result=0):
    for i,l in enumerate(total_sum.copy()):
        factor = 3 if i == 0 else 2
        if type(l) == list:
            result += evaluate_sum(l)*factor
        else:
            result += l*factor
    return result

def find_max_pair_sum(number_list):
    max_sum = 0
    for i,_ in enumerate(number_list):
        for j,_ in enumerate(number_list):
            if not i == j:
                this_sum = sum_numbers(number_list[i], number_list[j])
                is_explode,is_split = check_exploding_split(this_sum)
                while is_explode or is_split:
                    if is_explode:
                        this_sum = do_explode(this_sum)
                    else:
                        this_sum = do_split(this_sum)
                    is_explode,is_split = check_exploding_split(this_sum)
                max_sum = max(max_sum, evaluate_sum(to_list(this_sum)[0]))
    return max_sum

if __name__ == "__main__":
    number_list = [line for line in open('test.txt').read().splitlines()]
    total_sum = compute_sum(number_list)
    assert(total_sum=="[[[[0,7],4],[[7,8],[6,0]]],[8,1]]")

    number_list = [line for line in open('test2.txt').read().splitlines()]
    total_sum = compute_sum(number_list)
    assert(total_sum=="[[[[5,0],[7,4]],[5,5]],[6,6]]")

    assert(do_explode("[[[[[9,8],1],2],3],4])[0]==[[[[0,9],2],3],4]"))
    test_explode = do_explode("[7,[6,[5,[4,[3,2]]]]]")
    assert(test_explode=="[7,[6,[5,[7,0]]]]")
    test_explode=do_explode("[[6,[5,[4,[3,2]]]],1]")
    assert(test_explode=="[[6,[5,[7,0]]],3]")
    test_explode=do_explode("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]")
    assert(test_explode=="[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]")
    test_explode=do_explode("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]")
    assert(test_explode=="[[3,[2,[8,0]]],[9,[5,[7,0]]]]")

    number_list = [line for line in open('test3.txt').read().splitlines()]
    total_sum = compute_sum(number_list)
    assert(evaluate_sum(to_list(total_sum)[0])==3488)

    number_list = [line for line in open('test4.txt').read().splitlines()]
    total_sum = compute_sum(number_list)
    assert(evaluate_sum(to_list(total_sum)[0])==4140)

    number_list = [line for line in open('input.txt').read().splitlines()]
    total_sum = compute_sum(number_list)
    print("Part 1", evaluate_sum(to_list(total_sum)[0]))


    number_list = [line for line in open('test4.txt').read().splitlines()]
    assert(find_max_pair_sum(number_list)==3993)

    number_list = [line for line in open('input.txt').read().splitlines()]
    print("Part 2", find_max_pair_sum(number_list))
