def generate_boards_list(boards_lines):
    boards_list = []
    board = {}
    i=0
    for line in boards_lines:
        if line == '':
            boards_list.append(board)
            board={}
            i=0
        else:
            for j, number in enumerate(line.split()):
                board[(i,j)] = [int(number), False]
            i += 1
    boards_list.append(board)
    return boards_list

def check_if_someone_won(boards_list):
    for board in boards_list:
        #check rows
        for i in range(5):
            if min(board[(i,j)][1] for j in range(5)):
                return board
        #check cols
        for j in range(5):
            if min(board[(i,j)][1] for i in range(5)):
                return board
    return None

def check_all_winners(boards_list):
    winners = []
    for board in boards_list:
        #check rows
        for i in range(5):
            if min(board[(i,j)][1] for j in range(5)) and board not in winners:
                winners.append(board)
                break
        #check cols
        for j in range(5):
            if min(board[(i,j)][1] for i in range(5)) and board not in winners:
                winners.append(board)
                break
    return winners

def set_matching_key(board, number):
    for key in board.keys():
        if board[key][0] == number:
            board[key][1] = True
            return board
    return board

if __name__ == "__main__":
    file_name="input.txt"
    lines_list = open(file_name).read().splitlines()
    random_numbers = [int(number) for number in lines_list[0].split(",")]
    boards_lines = lines_list[2:]
    boards_list = generate_boards_list(boards_lines)
    for number in random_numbers:
        for board in boards_list:
            board = set_matching_key(board, number)
        winner = check_if_someone_won(boards_list)
        if winner is not None:
            break
    print("Part 1", number*sum(value[0] for key, value in winner.items() if not value[1]))

    boards_list = generate_boards_list(boards_lines)
    for number in random_numbers:
        for board in boards_list:
            board = set_matching_key(board, number)
        winners = check_all_winners(boards_list)
        if len(winners) > 0:
            if len(boards_list) > 1:
                for winner in winners:
                    boards_list.remove(winner)
            else:
                break
    winner = winners[0]
    print("Part 2", number*sum(value[0] for key, value in winner.items() if not value[1]))
