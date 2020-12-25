lines_list = open("input.txt").read().splitlines()
def get_value_through_loop(loop_size, subject_number=7):
    value = 1
    for i in range(loop_size):
        value *= subject_number
        value = value % 20201227
    return value

def get_value_single_loop(value, subject_number=7):
    value *= subject_number
    if not value < 20201227:
        value = value % 20201227
    return value

card_public = int(lines_list[0])
door_public = int(lines_list[1])
loop_size = 0
public_key = 1
while (public_key != card_public and public_key != door_public):
    loop_size += 1
    public_key=get_value_single_loop(public_key)

if public_key == door_public:
    print("Part 1",get_value_through_loop(loop_size, card_public))
if public_key == card_public:
    print("Part 1",get_value_through_loop(loop_size, door_public))