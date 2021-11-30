lines_list = open("input.txt").read().splitlines()

preamble = 25

for i, line in enumerate(lines_list[preamble:]):
    previous_window = {int(number) for number in lines_list[i:i+preamble]}
    number_check = [int(line)-number in previous_window for number in previous_window if not int(line)==number]
    if not max(number_check):
        print("Part 1 wrong number" , line)
        number_to_find = int(line)

def CheckWindow(window):
    for i, line in enumerate(lines_list[window:]):
        previous_window = [int(number) for number in lines_list[i:i+window]]
        if sum(previous_window) == number_to_find:
            print("Part 2 found window" , number_to_find, previous_window)
            print("... answer to problem", min(previous_window)+max(previous_window))
            return True
    return False

windows_gen = (window for window in range(2, len(lines_list)))
is_found = False
while (not is_found):
    is_found = CheckWindow(next(windows_gen))
