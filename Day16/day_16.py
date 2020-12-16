def get_data(lines_list):
    rules = {}
    tickets = []
    i = 0
    while (lines_list[i] != ""):
        key = lines_list[i].split(":")[0]
        body = lines_list[i].split(":")[1]
        sub_rules = []
        for j in [1,3]:
            min_max = [int(number) for number in body.split(" ")[j].split("-")]
            sub_rules.append(range(min_max[0], min_max[1]+1))
        rules[key] = sub_rules
        i += 1
    i += 2
    while (lines_list[i] != ""):
        my_ticket =[int(number) for number in lines_list[i].split(",")]
        i += 1
    i += 2
    for line in lines_list[i:]:
        tickets.append([int(number) for number in line.split(",")])
    return rules, my_ticket, tickets
def check_number(number):
    for rule in rules.values():
        for sub_rule in rule:
            if number in sub_rule:
                return True
    return False
def check_ticket(ticket):
    for number in ticket:
        if not check_number(number):
            return False
    return True
def check_rule_on_ith_position(i, rule):
    is_valid = True
    for ticket in tickets:
        is_valid = min(is_valid, max([ticket[i] in sub_rule for sub_rule in rule]))
    return is_valid
def are_values_unitary(possible_rule_positions):
    for value in possible_rule_positions.values():
        if len(value) > 1:
            return False
    return True
def get_first_unitary_rule(possible_rule_positions, checked_positions):
    for key, value in possible_rule_positions.items():
        if len(value) == 1:
            if value[0] not in checked_positions:
                return key, value[0]


if __name__ == "__main__":
    lines_list =open("input.txt").read().splitlines()

    rules, my_ticket, tickets = get_data(lines_list)
    error_rate = sum([number for ticket in tickets for number in ticket if not check_number(number)])

    print("Part 1", error_rate)

    # Correct tickets:
    tickets = [ticket for ticket in tickets if check_ticket(ticket)]

    # Build possible positions
    possible_rule_positions = {}
    for key_rule, value_rule in rules.items():
        positions = [i for i in range(0, len(my_ticket)) if check_rule_on_ith_position(i, value_rule)]
        possible_rule_positions[key_rule] = positions

    # Get unique positions
    checked_positions = []
    while not are_values_unitary(possible_rule_positions):
        #search first unique
        key_unique, value_unique = get_first_unitary_rule(possible_rule_positions, checked_positions)
        checked_positions.append(value_unique)
        for keys_to_correct, values_to_correct in possible_rule_positions.items():
            if not keys_to_correct == key_unique:
                if value_unique in values_to_correct:
                    values_to_correct.remove(value_unique)
    # Compute my ticket
    multiplication = 1
    for key, value in possible_rule_positions.items():
        if "departure" in key:
            position = int(value[0])
            multiplication *= my_ticket[position]
    print("Part 2", multiplication)