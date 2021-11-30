expenses_list = [int(expense) for expense in open("input.txt").read().splitlines()]
for expense in expenses_list:
    to_2020 = 2020 - expense
    if to_2020 in expenses_list:
        print("Sum :", expense, "+" , to_2020, "= 2020, Multiplication", expense*to_2020)
        break

for expense in expenses_list:
    for expense2 in expenses_list:
        to_2020 = 2020 - expense - expense2
        if to_2020 in expenses_list:
            print("Sum :", expense, "+", expense2, "+", to_2020, "= 2020, Multiplication", expense*expense2*to_2020)
            break