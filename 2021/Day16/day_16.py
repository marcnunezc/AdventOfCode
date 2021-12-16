import numpy as np

def evaluate_number(transmission, i, version_sum):
    version = transmission[i:i+3]
    version_sum += int(version, 2)
    pack_type = transmission[i+3:i+6]
    i=i+6
    if int(pack_type,2) == 4:
        groups = []
        while not transmission[i] == '0':
            groups.append(transmission[i+1:i+5])
            i = i+5
        groups.append(transmission[i+1:i+5])
        return int("".join(groups),2), i+5, version_sum
    else:
        if transmission[i] == '0':
            sub_pack_len = int(transmission[i+1:i+16], 2)
            i=i+16
            starting_index = i
            values = []
            while not i-starting_index==sub_pack_len:
                number, i, version_sum = evaluate_number(transmission, i, version_sum)
                values.append(number)

        elif transmission[i] == '1':
            sub_pack_number = int(transmission[i+1:i+12], 2)
            i=i+12
            values = []
            for sub_pack in range(sub_pack_number):
                number, i, version_sum = evaluate_number(transmission, i, version_sum)
                values.append(number)
        processed_value = process_value(pack_type, values)
        return processed_value, i, version_sum

def process_value(pack_type, values):
    if int(pack_type,2) == 0:
        return sum(values)
    elif int(pack_type,2) == 1:
        return np.prod(values)
    elif int(pack_type,2) == 2:
        return min(values)
    elif int(pack_type,2) == 3:
        return max(values)
    elif int(pack_type,2) == 5:
        if not len(values) == 2:
            raise(Exception("Error: expected 2 values for pack type 5"))
        return 1 if values[0] > values[1] else 0
    elif int(pack_type,2) == 6:
        if not len(values) == 2:
            raise(Exception("Error: expected 2 values for pack type 6"))
        return 1 if values[0] < values[1] else 0
    elif int(pack_type,2) == 7:
        if not len(values) == 2:
            raise(Exception("Error: expected 2 values for pack type 7"))
        return 1 if values[0] == values[1] else 0
    else:
        raise(Exception("Error: unknown pack type"))

if __name__ == "__main__":
    hexa_string = open("input.txt").read().strip()
    hex_to_bin = {'0':'0000', '1':'0001', '2':'0010', '3':'0011', '4':'0100', '5':'0101', '6':'0110', '7':'0111', '8':'1000', '9':'1001', 'A':'1010', 'B':'1011', 'C':'1100', 'D':'1101', 'E':'1110', 'F':'1111'}
    transmission = "".join([hex_to_bin[char] for char in hexa_string])
    version_sum = 0
    print("Part 1", evaluate_number(transmission, 0, version_sum)[2])
    print("Part 2", evaluate_number(transmission, 0, version_sum)[0])
