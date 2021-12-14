from collections import Counter
lines_list = open('input.txt').read().splitlines()

polymer = [char for char in lines_list[0]]
pairs = { line.split(" -> ")[0]: line.split(" -> ")[1] for line in lines_list[2:] }
for step in range(10):
    new_polymer=[]
    for char1,char2 in zip(polymer, polymer[1:]):
        new_polymer.append(char1)
        if char1+char2 in pairs.keys():
            new_polymer.append(pairs[char1+char2])
    new_polymer.append(char2)
    polymer = new_polymer
counts = [polymer.count(char) for char in set(pairs.values())]
print("Part 1", max(counts) - min(counts))

polymer = [char for char in lines_list[0]]
count_pairs = Counter()
for pair in pairs.keys():
    if "".join(polymer).count(pair) > 0:
        count_pairs[pair] = "".join(polymer).count(pair)
count_chars = Counter()
for char in polymer:
    count_chars[char] += 1

generated_pairs_from_pair = {pair:(pair[0]+pairs[pair], pairs[pair]+pair[1]) for pair in pairs.keys() }
for step in range(40):
    new_count_pairs = count_pairs.copy()

    for counted_pair, current_count in count_pairs.items():
        for new_pair in generated_pairs_from_pair[counted_pair]:
            new_count_pairs[new_pair] += current_count
        new_count_pairs[counted_pair] -= current_count

        count_chars[pairs[counted_pair]] += current_count

    count_pairs = new_count_pairs.copy()
print("Part 2", max(count_chars.values()) - min(count_chars.values()))