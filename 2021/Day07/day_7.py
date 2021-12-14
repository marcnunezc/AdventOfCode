positions =[int(pos) for pos in open('input.txt').read().splitlines()[0].split(',')]
print("Part 1", min(sum([abs(i-pos) for pos in positions]) for i in range(min(positions), max(positions)+1)))
print("Part 2", min(sum([abs(i-pos)*(1+abs(i-pos))//2 for pos in positions]) for i in range(min(positions), max(positions)+1)))