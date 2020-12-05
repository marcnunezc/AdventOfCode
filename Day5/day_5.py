def DecodeSeat(seat_string, seat_list, upper_char):
    half_len = int(len(seat_list)/2)
    if half_len == 0:
        return seat_list[0]
    if seat_string[0]==upper_char:
        return DecodeSeat(seat_string[1:], seat_list[half_len:], upper_char)
    else:
        return DecodeSeat(seat_string[1:], seat_list[:half_len], upper_char)
def GetSeatId(column, row):
    return 8*row+column

# TEST
string_seat= "FBFBBFFRLR"
n_rows = 128
n_columns = 8
test_row = DecodeSeat(string_seat[:7], list(range(n_rows)), "B")
test_column = DecodeSeat(string_seat[7:], list(range(n_columns)), "R")
print("Test column:", test_column, "row: ",\
      test_row, "seat_id:", GetSeatId(test_column, test_row))
#PART 1
lines_list = open("input.txt").read().splitlines()
max_id = 0
list_of_avail_ids = []
for string_seat in lines_list:
    row = DecodeSeat(string_seat[:7], list(range(n_rows)), "B")
    column = DecodeSeat(string_seat[7:], list(range(n_columns)), "R")
    this_id =  GetSeatId(column, row)
    list_of_avail_ids.append(this_id)
    max_id = max(max_id, this_id)

print("Max seat id:", max_id)

#PART 2
all_possible_ids = list(range(GetSeatId(0,0), GetSeatId(n_columns-1, n_rows-1)))
not_available_seats = list(filter(lambda x : x not in list_of_avail_ids, all_possible_ids))
for not_available_seat in not_available_seats:
    if ((not_available_seat + 1) in not_available_seats):
        continue
    elif ((not_available_seat - 1) in not_available_seats):
        continue
    else:
        print("I found my seat id", not_available_seat)