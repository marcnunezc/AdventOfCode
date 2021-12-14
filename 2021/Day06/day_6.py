class LanternFish:
    def __init__(self, timer=8):
        self.timer = timer
        self.number_of_fishes = 1
    def decrease(self):
        self.timer -= 1
    def reset_timer(self):
        self.timer = 6
    def get_timer(self):
        return self.timer
    def __len__(self):
        return self.number_of_fishes

class GroupOfFishes(LanternFish):
    def __init__(self, number_of_fishes):
        self.timer = 8
        self.number_of_fishes = number_of_fishes

def simulate_days(days, fishes):
    for day in range(days):
        to_add = 0
        for fish in fishes:
            if fish.get_timer() == 0:
                fish.reset_timer()
                to_add += len(fish)
            else:
                fish.decrease()
        if to_add > 0:
            fishes.add(GroupOfFishes(to_add))
    return fishes

if __name__ == '__main__':
    import time
    ini_time = time.time()
    fishes = {LanternFish(int(value)) for value in open('input.txt').read().splitlines()[0].split(',')}
    print("Part 1", sum(len(fish) for fish in simulate_days(80, fishes)))
    fishes = {LanternFish(int(value)) for value in open('input.txt').read().splitlines()[0].split(',')}
    print("Part 2", sum(len(fish) for fish in simulate_days(256, fishes)))
    print("Time:", time.time() - ini_time)