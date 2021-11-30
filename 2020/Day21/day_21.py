from collections import defaultdict
lines_list =open("test.txt").read().splitlines()
ingredient_to_alergen = defaultdict(lambda: defaultdict(int))
ingredient_apperances = defaultdict(int)
alergent_appearance = defaultdict(int)
for line in lines_list:
    ing_and_alg = line.split(" ")
    x = ing_and_alg.index("(contains")
    ingredients = [ing for ing in ing_and_alg[:x]]
    alergens = [alg[:-1] for alg in ing_and_alg[(x+1):]]
    for ing in ingredients:
        ingredient_apperances[ing] += 1
        alergen_dict = ingredient_to_alergen[ing]
        for alg in alergens:
            alergent_appearance[alg] += 1
            alergen_dict[alg] += 1
alergic_ing_dict = {}

# Computing priority to assign the most occurrent ingredient the last
ingredient_priority = {}
for ing, values in ingredient_to_alergen.items():
    n_alg = 0
    alg_sum = 0
    for alg, apperances in values.items():
        if apperances > 0:
            n_alg += 1
        alg_sum += apperances
    ingredient_priority[ing] = alg_sum - n_alg
sorted_ingredients = sorted(ingredient_priority, key=ingredient_priority.get)

for alg in alergent_appearance.keys():
    max_ing = "dummy"
    max_value = 0
    for ing in sorted_ingredients:
        value = ingredient_to_alergen[ing]
        if value[alg] > max_value and not ing in alergic_ing_dict.values():
            max_ing = ing
            max_value = value[alg]
    alergic_ing_dict[alg] = max_ing
print("Part 1", sum(value for ing, value in ingredient_apperances.items() if not ing in alergic_ing_dict.values()))

dangerous_list = ""
for key in sorted(alergic_ing_dict):
    dangerous_list += alergic_ing_dict[key]+","
dangerous_list=dangerous_list[:-1]
print("Part 2", dangerous_list)