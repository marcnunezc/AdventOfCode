def find_list(this_line, i):
    # print("this line",this_line)
    this_list = []
    while i < len(this_line):
        char = this_line[i]
        # print("char", char)
        # print("this_list ", this_list, this_line[i:])
        if char == '[':
            # print("square char", char)
            new_list, i = find_list(this_line, i+1)
            this_list.append(new_list)
        elif char == ']':
            # print("close square char", char)
            return this_list, i+1
        elif not char == ',':
            # print("other char", "".join(char), type(char), len(char))
            this_list.append(int(char))
            i += 1
        else:
            # print('this sholud be a comma', char, char == ',')
            i += 1

    return this_list[0], i
def sum_numbers(num1, num2):
    if num1 == []:
        return num2
    else:
        return [num1] + [num2]

def check_exploding(this_list, depth=0):
    depth += 1
    for i,l in enumerate(this_list):
        if type(l) == list:
            if depth == 4:
                return True
            else:
                if check_exploding(l, depth):
                    return True
    return False


def check_split(this_list):
    for i,l in enumerate(this_list):
        if type(l) == list:
            if check_split(l):
                return True
        else:
            if l>=10:
                return True
    return False

def do_explode(this_list, depth=0, compute_new_list=True, to_carry=[0,0,0]):
    print("exploding", this_list)
    depth += 1
    list_to_send = []
    for i,l in enumerate(this_list.copy()):
        # print("l depth", l, depth)
        # print("this_list", l)
        if to_carry[0] == 0 and to_carry[1] == 0 and not compute_new_list:
            list_to_send.append(l)
            continue

        if type(l) == list:
            # if depth > 1:
                # to_carry = [0,0]
            if depth == 4 and compute_new_list:
                print("computing new with", this_list)
                if type(this_list[0]) == list and type(this_list[1]) == list:
                    new_list = [0, [this_list[1][0] + this_list[0][1], this_list[1][1]]]
                    to_carry = [this_list[0][0],0, 3]
                elif type(this_list[0]) == list:
                    to_add = this_list[1] if not type(this_list[1]) == list else this_list[1][0]
                    new_list  = [0, this_list[0][1] + to_add]
                    to_carry[0] = this_list[0][0]
                    to_carry[2] = 4
                else:
                    to_add = this_list[0] if not type(this_list[0]) == list else this_list[0][1]
                    new_list = [to_add + this_list[1][0], 0]
                    to_carry[1] = this_list[1][1]
                    to_carry[2] = 4

                print("new_list", new_list)
                print("to_carry", to_carry)
                return new_list, False, to_carry
            else:
                new_list, compute_new_list, to_carry = do_explode(l, depth, compute_new_list, to_carry)
                print("im", list_to_send, "with len", len(list_to_send),"and i have", new_list, "and to_carry", to_carry, "my i is", i, "and depth is", depth)
                print(to_carry[0] > 0)
                if to_carry[0]>0 and depth<to_carry[2] and len(list_to_send)>0:
                    print("setting to carry", list_to_send[0])
                    if type(list_to_send[0]) == int:
                        list_to_send[0] += to_carry[0]
                    elif type(list_to_send[0][1]) == int:
                        list_to_send[0][1] += to_carry[0]
                    elif type(list_to_send[0][1][1]) == int:
                        list_to_send[0][1][1] += to_carry[0]
                    else:
                        list_to_send[0][1][1][1] += to_carry[0]
                to_carry[0] = 0
                # print("new this_list", list_to_send)
        else:
            # print("Ltosend", list_to_send,"to_carry", to_carry)
            print("L", l,"to_carry", to_carry)
            new_list = l + to_carry[1]
            to_carry[1] = 0
        list_to_send.append(new_list)
        print("toappend", new_list, "to carry", to_carry)
        print("tosend", list_to_send, "to carry", to_carry)
    return list_to_send, compute_new_list, to_carry

def do_split(this_list, compute_new_list=True):
    list_to_send = []
    for l in this_list:
        if type(l) == list:
            new_list, compute_new_list = do_split(l, compute_new_list)
            list_to_send.append(new_list)
        elif l >= 10 and compute_new_list:
            compute_new_list = False
            list_to_send.append([l//2, l//2 + l%2])
        else:
            list_to_send.append(l)
    return list_to_send, compute_new_list

assert(do_explode([[[[[9,8],1],2],3],4])[0]==[[[[0,9],2],3],4])
test_explode = do_explode([7,[6,[5,[4,[3,2]]]]],to_carry=[0,0,0])[0]
assert(test_explode==[7,[6,[5,[7,0]]]])
test_explode=do_explode([[6,[5,[4,[3,2]]]],1],to_carry=[0,0,0])[0]
assert(test_explode==[[6,[5,[7,0]]],3])
test_explode=do_explode([[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]],to_carry=[0,0,0])[0]
assert(test_explode==[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]])
test_explode=do_explode([[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]],to_carry=[0,0,0])[0]
assert(test_explode==[[3,[2,[8,0]]],[9,[5,[7,0]]]])

lines_list = open('test3.txt').read().splitlines()
number_list = [find_list(line, 0)[0] for line in lines_list]
total_sum = number_list[0]
for line in number_list[1:]:
    print("SUMMING:", total_sum, line)
    total_sum = sum_numbers(total_sum, line)
    is_explode = check_exploding(total_sum)
    is_split = check_split(total_sum)
    print(is_explode, is_split)
    i = 0
    j = 0
    while is_explode or is_split:
        print("###################")
        print(total_sum)
        if is_explode:
            i += 1
            total_sum = do_explode(total_sum, to_carry=[0,0,0])[0]
            print("new sum explode", total_sum)
            if i==1:
                stop
        else:
            total_sum = do_split(total_sum)[0]
            print("new split sum", total_sum)
        is_explode = check_exploding(total_sum)
        is_split = check_split(total_sum)
        print(is_explode, is_split)

    j += 1
    print(total_sum)
    if j==1:
        stop