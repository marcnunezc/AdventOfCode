lines_list = [int(line) for line in open('input.txt', 'r').read().splitlines()]

increased = [1 for i,_ in enumerate(lines_list[:-1]) if lines_list[i+1] > lines_list[i]]
print("Part 1:", sum(increased))

windows = [lines_list[i:i+3] for i,_ in enumerate(lines_list[:-2]) ]
increased_windows =  [1 for i,_ in enumerate(windows[:-1]) if sum(windows[i+1]) > sum(windows[i])]
print("Part 1:", sum(increased_windows))
