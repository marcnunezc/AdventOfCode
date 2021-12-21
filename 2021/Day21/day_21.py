import itertools
from functools import cache
import time

class Dice:
    def __init__(self):
        self.value = 0
        self.rolling_times = 0
    def roll(self):
        self.rolling_times += 1
        self.value += 1
        if self.value > 100:
            self.value = 1
        return self.value
    def get_rolling_times(self):
        return self.rolling_times

# @cache
def play_realization(pos_i, pos_j, score_i, score_j, wins_i, wins_j,  product):
    if score_i  >= 21:
        wins_i += product
        return wins_i, wins_j

    if score_j >= 21:
        wins_j += product
        return wins_i, wins_j

    for outcome_i, outcome_j in itertools.product(outcomes_wins.keys(), repeat=2):
        new_pos_i = sum_outcome(pos_i, outcome_i)
        new_pos_j = sum_outcome(pos_j, outcome_j)
        current_product = product*outcomes_wins[outcome_i]*outcomes_wins[outcome_j]
        wins_i, wins_j= play_realization(new_pos_i, new_pos_j, score_i+new_pos_i, score_j+new_pos_j, wins_i, wins_j, current_product)
    return wins_i, wins_j

def sum_outcome(pos, outcome):
    pos += outcome
    while pos>10:
        pos -= 10
    return pos


start_time = time.time()
lines_list = open('input.txt').read().splitlines()
player_positions = [int(line.split(":")[1].strip()) for line in lines_list]
player_scores = [0] * len(player_positions)
dice = Dice()
while not any([score>=1000 for score in player_scores]):
    for i, position in enumerate(player_positions):
        new_score = [dice.roll() for _ in range(3)]
        player_positions[i] += sum(new_score)
        while player_positions[i]>10:
            player_positions[i] -= 10
        player_scores[i] += player_positions[i]
        if player_scores[i]>=1000:
            break
print("Part 1 ", dice.get_rolling_times()*min(player_scores))


player_positions = [int(line.split(":")[1].strip()) for line in lines_list]
player_scores = [0] * len(player_positions)
dice_outcomes = []
for i in range(1, 4):
    for j in range(1, 4):
        for k in range(1, 4):
            dice_outcomes.append(i+j+k)
outcomes_wins = {value:dice_outcomes.count(value) for value in dice_outcomes}
wins_i, wins_j=play_realization(player_positions[0], player_positions[1], player_scores[0], player_scores[1], 0, 0,1)

print("Part 2 ", max(wins_i//len(dice_outcomes),wins_j))
print("--- %s seconds ---" % (time.time() - start_time))

