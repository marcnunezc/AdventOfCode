import math
lines_list = open("input.txt").read().splitlines()
arrival = int(lines_list[0])
buses_scheduled = [int(char) for char in lines_list[1].split(',') if char != "x"]
first_appearances = [math.ceil(arrival/bus)*bus for bus in buses_scheduled]
print("Part 1", (min(first_appearances)-arrival)*buses_scheduled[first_appearances.index(min(first_appearances))])


all_buses_scheduled = [int(char) if char.isdigit() else 0 for char in lines_list[1].split(',')]
for index, bus in enumerate(all_buses_scheduled):
    if not bus==0:
        if index == 0:
            target_value = bus
            target_mod = 0
        else:
            k=1
            bus_mod = bus-(index%bus)
            while  (target_value*k + target_mod) % bus != bus_mod:
                k += 1
            target_mod=target_value*k+target_mod
            target_value=bus*target_value
            print(target_mod)
print("Part 2",  target_mod)