def find_list(this_line, i):
    this_list = []
    while i < len(this_line):
        char = this_line[i]
        if char == '[':
            new_list, i = find_list(this_line, i+1)
            this_list.append(new_list)
        elif char == ']':
            return this_list, i+1
        elif not char == ',':
            this_list.append(int(char))
            i += 1
        else:
            i += 1
    return this_list[0], i

def sum_numbers(num1, num2):
    if num1 == []:
        return num2
    else:
        return [num1] + [num2]

def check_exploding_split(this_list, depth=0):
    depth += 1
    for i,l in enumerate(this_list):
        if type(l) == list:
            # if not type(l[0])== list and l[0]>=10:
                # return False, True
            if depth == 4:
                return True, False
            else:
                explode, _ = check_exploding_split(l, depth)
                if explode:
                    return True, False
    for i,l in enumerate(this_list):
        if type(l) == list:
            _ , split = check_exploding_split(l, depth)
            if split:
                return False, True
        elif l>=10:
            return False, True

    return False, False
def recursively_compute_length(this_list):
    if type(this_list) == list:
        return sum(recursively_compute_length(l) for l in this_list)
    else:
        return 1
def do_explode(this_list, depth=0, compute_new_list=True, to_carry=[0,0,0,0],  global_i=0, max_previous_i=0, length_string=0):
    # print("exploding", this_list)
    depth += 1
    list_to_send = []
    for i,l in enumerate(this_list.copy()):
        # print(i, l, length_string)
        global_i += 1 if not type(l)==list else len(l)
        # print("ASSESING DEPTH i", depth, i)
        # print("this_list", l, depth)
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
                    to_carry = [this_list[0][0],0, 3, global_i]
                elif type(this_list[0]) == list:
                    to_add = this_list[1] if not type(this_list[1]) == list else this_list[1][0]
                    new_list  = [0, this_list[0][1] + to_add]
                    to_carry[0] = this_list[0][0]
                    to_carry[2] = 4
                    to_carry[3] = global_i
                else:
                    to_add = this_list[0] if not type(this_list[0]) == list else this_list[0][1]
                    new_list = [to_add + this_list[1][0], 0]
                    to_carry[1] = this_list[1][1]
                    to_carry[2] = 4
                    to_carry[3] = global_i

                print("new_list", new_list)
                print("to_carry", to_carry)
                return new_list, False, to_carry, global_i
            else:
                new_list, compute_new_list, to_carry, global_i = do_explode(l, depth, compute_new_list, to_carry,global_i, max(max_previous_i,i),  length_string)
                len_0 = recursively_compute_length(list_to_send)
                print("im", list_to_send, "with len", len(list_to_send),"and i have", new_list, "and to_carry", to_carry, "my i is", i, "and depth is", depth, "global i", global_i+len_0, "maxprev", max_previous_i)
                # print("my signature is", i_signature)
                # print("their signature is", to_carry[2])
                # if len(list_to_send) == 0:
                    # to_carry[0] = 0
                if to_carry[0]>0 and len(list_to_send)>0  and global_i < to_carry[3]:
                # if to_carry[0]>0 and depth<len(i_signature) and len(list_to_send)>0:
                    # print("setting to carry", list_to_send[0])
                    if type(list_to_send[0]) == int:
                        list_to_send[0] += to_carry[0]
                    elif type(list_to_send[0][1]) == int:
                        list_to_send[0][1] += to_carry[0]
                    elif type(list_to_send[0][1][1]) == int:
                        list_to_send[0][1][1] += to_carry[0]
                    else:
                        list_to_send[0][1][1][1] += to_carry[0]
                    to_carry[0] = 0
                else:
                    to_carry[2]
                # print("new this_list", list_to_send)
        else:
            # print("Ltosend", list_to_send,"to_carry", to_carry)
            # print("L", l,"to_carry", to_carry)
            new_list = l + to_carry[1]
            to_carry[1] = 0
            # global_i += 1
        list_to_send.append(new_list)
        if max_previous_i==0:
            to_carry[0] = 0
        # print("toappend", new_list, "to carry", to_carry)
        # print("tosend", list_to_send, "to carry", to_carry)
    return list_to_send, compute_new_list, to_carry, global_i

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

lines_list = open('test3.txt').read().splitlines()
number_list = [find_list(line, 0)[0] for line in lines_list]
total_sum = number_list[0]
j = 0
for line in number_list[1:]:
    print("SUMMING:", total_sum, line)
    # input("press enter")
    total_sum = sum_numbers(total_sum, line)
    is_explode,is_split = check_exploding_split(total_sum)

    print(is_explode, is_split)
    i = 0
    while is_explode or is_split:
        print("###################")
        print(total_sum)
        i += 1
        if is_explode:
            total_sum = do_explode(total_sum, to_carry=[0,0,0,0])[0]
            # print("new sum explode", total_sum)
        else:
            total_sum = do_split(total_sum)[0]

            # print("new split sum", total_sum)
        is_explode,is_split = check_exploding_split(total_sum)
        # print(is_explode, is_split)
        print(total_sum)
        print("we are at i", i)
        input("Press Enter to continue...")
        # if i==13:
            # stop

    j += 1
    print(total_sum)
    if j==2:
        stop