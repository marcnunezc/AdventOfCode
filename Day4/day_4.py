import string
lines_list = open("input.txt").read().splitlines()

def CheckStringInLimit(string_to_check, min_lim, max_lim):
    return min_lim <= int(string_to_check) <= max_lim

def CheckHeight(string_to_check):
    if string_to_check[-2:] == "cm":
        return CheckStringInLimit(string_to_check[:-2], 150, 193)
    elif string_to_check[-2:] == "in":
        return CheckStringInLimit(string_to_check[:-2], 59, 76)
    else:
        return False

required_keys_with_check = {
"byr" : lambda x : CheckStringInLimit(x, 1920, 2002),
"iyr" : lambda x : CheckStringInLimit(x, 2010, 2020),
"eyr" : lambda x : CheckStringInLimit(x, 2020, 2030),
"hgt" : CheckHeight,
"hcl" : lambda x: x[0] == "#" and all(c in string.hexdigits for c in x[1:]),
"ecl" : lambda x: x in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"],
"pid" : lambda x: len(x) == 9 and x.isdigit()
}

def is_key_valid(required_key, aux_dict):
    if not required_key in aux_dict.keys():
        return False
    if not required_keys_with_check[required_key](aux_dict[required_key]):
        return False
    return True

def is_passport_valid(aux_dict):
    for required_key in required_keys_with_check.keys():
        if not is_key_valid(required_key, aux_dict):
            return False
    return True

aux_dict = {}
valid_passports = 0
for line in lines_list:
    if line == "":
        if is_passport_valid(aux_dict):
            valid_passports += 1
        aux_dict = {}
    else:
        for entry in line.split(" "):
            aux_dict[entry.split(":")[0]] = entry.split(":")[1]
# Check last dict
if is_passport_valid(aux_dict):
    valid_passports += 1

print("Valid passports", valid_passports)