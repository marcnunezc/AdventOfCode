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
    if len(winners)>0:
        return winners
    else:
        return None

if __name__ == "__main__":

    file_name="input.txt"
    random_numbers = [int(number) for number in open(file_name).read().splitlines()[0].split(",")]
    boards_lines = open(file_name).read().splitlines()[2:]
    boards_list = generate_boards_list(boards_lines)
    for number in random_numbers:
        for i_board, board in enumerate(boards_list):
            for key in board.keys():
                if board[key][0] == number:
                    board[key][1] = True
                    break
        winner = check_if_someone_won(boards_list)
        if winner is not None:
            break
    print("Part 1", number*sum(value[0] for key, value in winner.items() if not value[1]))

    boards_list = generate_boards_list(boards_lines)
    for number in random_numbers:
        for i_board, board in enumerate(boards_list):
            for key in board.keys():
                if board[key][0] == number:
                    board[key][1] = True
                    break
        winners = check_all_winners(boards_list)
        if winners is not None :
            if len(boards_list) > 1:
                for winner in winners:
                    boards_list.remove(winner)
            else:
                break
    winner = winners[0]
    print("Part 2", number*sum(value[0] for key, value in winner.items() if not value[1]))
