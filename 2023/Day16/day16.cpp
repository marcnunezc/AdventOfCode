
enum class MOVE {
    U,
    D,
    L,
    R
};
std::vector<MOVE> get_next_moves(std::vector<std::string>& cave, std::pair<int,int> current, MOVE dir) {
    std::vector<MOVE> next_moves;
    if (cave[current.first][current.second]=='|') {
        if (dir == MOVE::R || dir == MOVE::L) {
            next_moves.push_back(MOVE::U);
            next_moves.push_back(MOVE::D);
        } else {
            next_moves.push_back(dir);
        }
    } else if (cave[current.first][current.second]=='-') {
        if (dir == MOVE::U || dir == MOVE::D) {
            next_moves.push_back(MOVE::R);
            next_moves.push_back(MOVE::L);
        } else {
            next_moves.push_back(dir);
        }
    } else if (cave[current.first][current.second]=='\\') {
        if (dir == MOVE::R)
            next_moves.push_back(MOVE::D);
        else if (dir == MOVE::L)
            next_moves.push_back(MOVE::U);
        else if (dir == MOVE::U)
            next_moves.push_back(MOVE::L);
        else if (dir == MOVE::D)
            next_moves.push_back(MOVE::R);

    } else if (cave[current.first][current.second]=='/') {
        if (dir == MOVE::R)
            next_moves.push_back(MOVE::U);
        else if (dir == MOVE::L)
            next_moves.push_back(MOVE::D);
        else if (dir == MOVE::U)
            next_moves.push_back(MOVE::R);
        else if (dir == MOVE::D)
            next_moves.push_back(MOVE::L);
    } else {
        next_moves.push_back(dir);
    }
    return next_moves;
}

void do_move(std::vector<std::string>& cave, std::pair<int,int> current, MOVE dir, std::set<std::pair<int,int>>& energized, int already_energized) {
    if (energized.find(current) != energized.end())
        already_energized++;
    else
        already_energized=0;
    energized.insert(current);
    if (dir == MOVE::R)
        current.second++;
    else if (dir == MOVE::L)
        current.second--;
    else if (dir == MOVE::D)
        current.first++;
    else if (dir == MOVE::U)
        current.first--;


    if ( 0 > current.first || current.first > cave.size()-1 || 0 > current.second || current.second > cave[0].size()-1 || already_energized > 50 ) {
        return;
    }

    auto next_moves = get_next_moves(cave, current, dir);
    for (auto next : next_moves) {
        do_move(cave, current, next, energized, already_energized);
    }
}

AOC_DAY(Day16_1){
    std::pair<int,int> start{0,0};
    std::set<std::pair<int,int>> energized;
    auto dir = MOVE::R;
    std::vector<std::string> cave;
    std::string line;
    while(getline(cin, line)) {
        cave.push_back(line);
    }

    auto next_moves = get_next_moves(cave, start, dir);
    for (auto next : next_moves) {
        do_move(cave, start, next, energized, 0);
    }

    return std::to_string(energized.size());
}

AOC_DAY(Day16_2){
    size_t max_energized = 0;
    std::set<std::pair<int,int>> energized;
    std::vector<std::string> cave;
    std::string line;
    while(getline(cin, line)) {
        cave.push_back(line);
    }

    // top
    for (int j=0; j<cave[0].size(); j++) {
        std::pair<int,int> start{0,j};
        auto dir = MOVE::D;
        auto next_moves = get_next_moves(cave, start, dir);
        for (auto next : next_moves) {
            do_move(cave, start, next, energized, 0);
        }
        max_energized = max(max_energized, energized.size());
        energized.clear();
    }
    // bottom
    for (int j=0; j<cave[0].size(); j++) {
        std::pair<int,int> start{cave.size()-1,j};
        auto dir = MOVE::U;
        auto next_moves = get_next_moves(cave, start, dir);
        for (auto next : next_moves) {
            do_move(cave, start, next, energized, 0);
        }
        max_energized = max(max_energized, energized.size());
        energized.clear();
    }

    // left
    for (int i=0; i<cave.size(); i++) {
        std::pair<int,int> start{i,0};
        auto dir = MOVE::R;
        auto next_moves = get_next_moves(cave, start, dir);
        for (auto next : next_moves) {
            do_move(cave, start, next, energized, 0);
        }
        max_energized = max(max_energized, energized.size());
        energized.clear();
    }

    // right
    for (int i=0; i<cave.size(); i++) {
        std::pair<int,int> start{i,cave.size()-1};
        auto dir = MOVE::L;
        auto next_moves = get_next_moves(cave, start, dir);
        for (auto next : next_moves) {
            do_move(cave, start, next, energized, 0);
        }
        max_energized = max(max_energized, energized.size());
        energized.clear();
    }

    return std::to_string(max_energized);
}