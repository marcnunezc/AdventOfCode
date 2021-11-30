from collections import defaultdict

def get_input(lines_list):
    i=1
    player_1 = []
    while lines_list[i]!="":
        player_1.append(int(lines_list[i]))
        i += 1
    i += 2
    player_2 = [int(line) for line in lines_list[i:]]
    return player_1, player_2
def play_normal_game(player_1, player_2):
    while (len(player_1) > 0 and len(player_2) > 0):
        card_1 = player_1.pop(0)
        card_2 = player_2.pop(0)
        if card_1 > card_2:
            player_1.append(card_1)
            player_1.append(card_2)
        else:
            player_2.append(card_2)
            player_2.append(card_1)
    return player_1, player_2
def get_score(card_list):
    return sum([card*i for card, i in zip(card_list[::-1], range(1, len(card_list)+1))])

dict_of_plays = defaultdict(dict)
def play_normal_game_2(player_1, player_2):
    while (len(player_1) > 0 and len(player_2) > 0):
        tuple_of_1 = tuple(play for play in player_1)
        if not dict_of_plays[tuple_of_1] == player_2:
            card_1 = player_1.pop(0)
            card_2 = player_2.pop(0)
            if card_1 <= len(player_1) and card_2 <= len(player_2):
                aux_player_1 = [card for card in player_1[:card_1]]
                aux_player_2 = [card for card in player_2[:card_2]]
                sub_tuple_of_play_1 = tuple(play for play in aux_player_1)
                if not dict_of_plays[sub_tuple_of_play_1] == aux_player_2:
                    player_1_sub, player_2_sub = play_normal_game_2(aux_player_1, aux_player_2)
                    if len(player_1_sub) > len(player_2_sub):
                        player_1.append(card_1)
                        player_1.append(card_2)
                    else:
                        player_2.append(card_2)
                        player_2.append(card_1)
                    dict_of_plays[sub_tuple_of_play_1] == aux_player_2
                else:
                    player_1.append(card_1)
                    player_1.append(card_2)
            else:
                if card_1 > card_2:
                    player_1.append(card_1)
                    player_1.append(card_2)
                else:
                    player_2.append(card_2)
                    player_2.append(card_1)
            dict_of_plays[tuple_of_1] = player_2
        else:
            card_1 = player_1.pop(0)
            card_2 = player_2.pop(0)
            player_1.append(card_1)
            player_1.append(card_2)
    return player_1, player_2

lines_list = open("input.txt").read().splitlines()
player_1, player_2 = get_input(lines_list)
player_1, player_2 = play_normal_game(player_1, player_2)
print("Part 1", get_score(player_1) if len(player_1) > 0 else get_score(player_2))

player_1, player_2 = get_input(lines_list)
player_1, player_2 = play_normal_game_2(player_1, player_2)
print("Part 2", get_score(player_1) if len(player_1) > 0 else get_score(player_2))