lines_list = open("input.txt").read().splitlines()

required_keys = [
"byr",
"iyr",
"eyr",
"hgt",
"hcl",
"ecl",
"pid",
]
def is_key_valid(required_key, aux_dict):
    if not required_key in aux_dict.keys():
        return False
    if required_key == "byr":
        if int(aux_dict[required_key]) < 1920 or int(aux_dict[required_key]) > 2002:
            return False
    if required_key == "iyr":
        if int(aux_dict[required_key]) < 2010 or int(aux_dict[required_key]) > 2020:
            return False
    if required_key == "eyr":
        if int(aux_dict[required_key]) < 2020 or int(aux_dict[required_key]) > 2030:
            return False
    if required_key == "hgt":
        string_to_check = aux_dict[required_key]
        if string_to_check[-2:] == "cm":
            if int(string_to_check[:-2]) < 150 or int(string_to_check[:-2]) > 193:
                return False
        elif string_to_check[-2:] == "in":
            if int(string_to_check[:-2]) < 59 or int(string_to_check[:-2]) > 76:
                return False
        else:
            return False
    if required_key == "hcl":
        string_to_check = aux_dict[required_key]
        if not string_to_check[0] == "#":
            return False
        import string
        if not all(c in string.hexdigits for c in string_to_check[1:]):
            return False
    if required_key == "ecl":
        valid_eyes = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
        if not aux_dict[required_key] in valid_eyes:
            return False
    if required_key == "pid":
        if not len(aux_dict[required_key]) == 9 or not aux_dict[required_key].isdigit():
            return False
    return True

def is_passport_valid(aux_dict):
    for required_key in required_keys:
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