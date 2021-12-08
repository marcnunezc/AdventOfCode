lines_list = open('input.txt').read().splitlines()
patterns = [line.split('|')[0].split() for line in lines_list]
output = [line.split('|')[1].split() for line in lines_list]
print("Part 1", sum(sum(len(word) in [2,3,4,7] for word in line) for line in output))

def sum_numbers(word1,word2):
    string=[char for char in word1]
    string.extend([char for char in word2 if char not in word1])
    return "".join(string)

def not_coinciding_wire(word1,word2):
    return "".join([char for char in word1 if char not in word2])

def sort_string(string):
    return "".join(sorted(string))

total = 0
for i, pattern in enumerate(patterns):
    one = [word for word in pattern if len(word) ==2][0]
    four = [word for word in pattern if len(word) == 4][0]
    seven = [word for word in pattern if len(word) == 3][0]
    eight = [word for word in pattern if len(word) == 7][0]
    four_seven = sum_numbers(four,seven)
    nine = [word for word in pattern if len(word) == 6 and len(not_coinciding_wire(word,four_seven))==1][0]
    five = [word for word in pattern if len(word) == 5 and len(not_coinciding_wire(nine,word))==1 and not len(not_coinciding_wire(one,word))==0][0]
    three = [word for word in pattern if len(word) == 5 and len(not_coinciding_wire(nine,word))==1 and len(not_coinciding_wire(one,word))==0][0]
    six = [word for word in pattern if len(word) == 6 and len(not_coinciding_wire(eight,sum_numbers(word, one)))==0][0]
    zero = [word for word in pattern if len(word) == 6 and not word == nine and not word == six][0]
    two = [word for word in pattern if len(word) == 5 and not word == three and not word == five][0]
    matching_patterns = {sort_string(one) : "1",sort_string(two) : "2",sort_string(three) : "3",sort_string(four) : "4",sort_string(five) : "5",sort_string(six) : "6",sort_string(seven) : "7",sort_string(eight) : "8",sort_string(nine) : "9",sort_string(zero) : "0"}
    value =  int("".join([matching_patterns[sort_string(out)] for out in output[i]]))
    total += value
print("Part 2", total)










