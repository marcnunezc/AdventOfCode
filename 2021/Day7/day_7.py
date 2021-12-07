horizontal_pos =[int(pos) for pos in open('input.txt').read().splitlines()[0].split(',')]
def compute_min_cost(cost_func):
    fuel_cost=[]
    for i in range(min(horizontal_pos), max(horizontal_pos)+1):
        this_cost = 0
        cost_per_step = 1
        for pos in horizontal_pos:
            this_cost += cost_func(i, pos)
        fuel_cost.append(this_cost)
    return int(min(fuel_cost))

print("Part 1", compute_min_cost(lambda i,pos:abs(i-pos)))
print("Part 1", compute_min_cost(lambda i,pos:abs(i-pos)*(1+abs(i-pos))/2))