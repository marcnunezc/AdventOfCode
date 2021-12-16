import numpy as np
process_values = {
    0 : lambda x: sum(x),
    1 : lambda x: np.prod(x),
    2 : lambda x: min(x),
    3 : lambda x: max(x),
    5 : lambda x: 1 if x[0] > x[1] else 0,
    6 : lambda x: 1 if x[0] < x[1] else 0,
    7 : lambda x: 1 if x[0] == x[1] else 0
}
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
        return process_values[int(pack_type, 2)](values), i, version_sum

if __name__ == "__main__":
    hexa_string = open("input.txt").read().strip()
    hex_to_bin = {'0':'0000', '1':'0001', '2':'0010', '3':'0011', '4':'0100', '5':'0101', '6':'0110', '7':'0111', '8':'1000', '9':'1001', 'A':'1010', 'B':'1011', 'C':'1100', 'D':'1101', 'E':'1110', 'F':'1111'}
    transmission = "".join([hex_to_bin[char] for char in hexa_string])
    version_sum = 0
    print("Part 1", evaluate_number(transmission, 0, version_sum)[2])
    print("Part 2", evaluate_number(transmission, 0, version_sum)[0])
