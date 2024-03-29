
def check_sub_sub_rule(line, subrule):
    if isinstance(rules[subrule], list):
        is_check, checked_line =  check_rule(line, subrule)
        if is_check:
            return True, checked_line
        else:
            return False, line
    else:
        if len(line) > 0 and line[0]==rules[subrule]:
            return True, line[1:]
        else:
            return False, line

def check_sub_rule(rule, line):
    for subrule in rule:
        sub_rule_check, checked_line = check_sub_sub_rule(line, subrule)
        if sub_rule_check:
            line = checked_line
        else:
            return False, line
    return True, line

def check_rule(line, rule_key):
    for rule in rules[rule_key]:
        rule_check, checked_line = check_sub_rule(rule, line)
        if rule_check:
            return True, checked_line
    return False, line

def check_master(line, rule_key):
    is_check_rule, left_line = check_rule(line, rule_key)
    return min(is_check_rule, len(left_line) == 0)

lines_list =open("input.txt").read().splitlines()
rules = {}
i=0
while lines_list[i] != "":
    key, value = lines_list[i].split(": ")
    if "\"" in value:
        rules[key] = value.replace("\"","")
    else:
        rules[key] = [rule.split(" ") for rule in value.split(" | ")]
    i += 1
i += 1

part_1=len([check for check in (check_master(line,"0") for line in lines_list[i:]) if check])
print("Part 1:",  part_1)

rules["8"] = [['42'], ['42','8']]
rules["11"] =  [['42','31'], ['42','11','31']]
rules["0"] = [['8' ,'11'], ['8', '0']]
part_2=len([check for check in (check_master(line,'0') for line in lines_list[i:]) if check])
print("Part 2:",  part_2)