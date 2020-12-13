import math
lines_list = open("test.txt").read().splitlines()
arrival = int(lines_list[0])
buses_scheduled = [int(char) for char in lines_list[1].split(',') if char != "x"]
first_appearances = [math.ceil(arrival/bus)*bus for bus in buses_scheduled]
print("Part 1", (min(first_appearances)-arrival)*buses_scheduled[first_appearances.index(min(first_appearances))])


all_buses_scheduled = [int(char) if char.isdigit() else 0 for char in lines_list[1].split(',')]
delay = [i for i in range(0, len(all_buses_scheduled))]
max_value = max(all_buses_scheduled)
max_index = all_buses_scheduled.index(max(all_buses_scheduled))
is_found = False
time_stamp = max_value
def evaluate_condition(t):
    for i, bus in enumerate(all_buses_scheduled):
        if not bus==0:
           if (t+i) % bus != 0:
               return False
    return True

def get_new_time_stamp(i):
    return max_value*i-max_index
def get_starting_time_stamp():
    t = 100000000000000
    while (t+max_index) % max_value != 0:
        t += 1
    return t     

# time_stamp = get_starting_time_stamp() 
# i = (time_stamp+max_index)/max_value
i=0
while (not evaluate_condition(time_stamp)):
    time_stamp = get_new_time_stamp(i)
    i += 1
print("Part 2", time_stamp)
