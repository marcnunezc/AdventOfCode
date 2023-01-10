void print_elves(UnorderedSetType& elves_set) {
    auto min_i = std::min_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.first < r.first;})->first;
    auto max_i = std::max_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.first < r.first;})->first;
    auto min_j = std::min_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.second < r.second;})->second;
    auto max_j = std::max_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.second < r.second;})->second;
    for (int i=min_i; i<max_i+1; i++) {
        for (int j=min_j; j<max_j+1; j++) {
            if (elves_set.find({i,j}) != elves_set.end())
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
    cout << endl;
};

unsigned int count_empty(UnorderedSetType& elves_set) {
    auto min_i = std::min_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.first < r.first;})->first;
    auto max_i = std::max_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.first < r.first;})->first;
    auto min_j = std::min_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.second < r.second;})->second;
    auto max_j = std::max_element(elves_set.begin(), elves_set.end(),[] (auto l, auto r) {return l.second < r.second;})->second;
    unsigned int count = 0;
    for (int i=min_i; i<max_i+1; i++) {
        for (int j=min_j; j<max_j+1; j++) {
            if (elves_set.find({i,j}) == elves_set.end())
                count++;
        }
    }
    return count;
};


std::vector<pair<int,int>> movements = {
    {-1, 0}, // N
    {1, 0}, // S
    {0, -1}, // W
    {0, 1}, // E
};

bool is_move_already_set(pair<int,int> new_move, std::map<int, pair<int,int>>& next_moves) {
    for (auto it=next_moves.begin(); it!=next_moves.end(); it++) {
        if (new_move == it->second)
            return true;
    }
    return false;
};

AOC_DAY(Day23_1) {
    UnorderedSetType elves_set;
    std::string line;
    std::vector<std::pair<int,int>> elves;
    int i = 0;
    while(getline(cin, line)) {
        for (int j=0; j<line.size();j++) {
            if (line[j] == '#')
                elves.push_back({i,j});
        }
        i++;
    }
    for (auto elf : elves) {
        elves_set.insert(elf);
    }
    int i_movement = 0;
    // print_elves(elves_set);
    for (int i=0; i<10; i++) {
        std::map<int, pair<int,int>> next_moves;
        UnorderedSetType moves_to_avoid;

        // propose movements
        int start_i = i_movement;
        for (int i_elf=0; i_elf<elves.size();i_elf++) {
            auto pos_to_check = elves[i_elf];
            i_movement = start_i;
            std::pair<int,int> first_available_move = {0,0};
            bool all_empty = true;
            for (auto _ : movements) {
                auto move = movements[i_movement++ % movements.size()];
                bool is_empty;
                if (move.first==0) {

                    is_empty = elves_set.find({pos_to_check.first+1, pos_to_check.second + move.second}) == elves_set.end() && elves_set.find({pos_to_check.first, pos_to_check.second + move.second}) == elves_set.end() && elves_set.find({pos_to_check.first-1, pos_to_check.second + move.second}) == elves_set.end();
                }
                else {
                    is_empty = elves_set.find({pos_to_check.first+move.first, pos_to_check.second + 1}) == elves_set.end() && elves_set.find({pos_to_check.first+move.first, pos_to_check.second}) == elves_set.end() && elves_set.find({pos_to_check.first+move.first, pos_to_check.second-1}) == elves_set.end();
                }

                if (is_empty && first_available_move == pair<int,int>({0,0})) {
                    first_available_move = move;
                }

                if (!is_empty)
                    all_empty = false;
            }
            if (!all_empty) {
                pos_to_check.first += first_available_move.first;
                pos_to_check.second += first_available_move.second;
                if (is_move_already_set(pos_to_check, next_moves))
                    moves_to_avoid.insert(pos_to_check);
                else
                    next_moves[i_elf]=pos_to_check;
            }
        }
        if (next_moves.size() == 0)
            break;

        // execute movements
        for (auto it=next_moves.begin(); it!=next_moves.end(); it++) {
            if (moves_to_avoid.find(it->second) == moves_to_avoid.end()) {
                elves[it->first] = it->second;
            }
        }

        // fill set
        elves_set.clear();
        for (auto elf : elves) {
            elves_set.insert(elf);
        }

        //reset movement counter and increase it
        i_movement = start_i;
        i_movement++;

        // print_elves(elves_set);
    }

    return std::to_string(count_empty(elves_set));
}

AOC_DAY(Day23_2) {
    UnorderedSetType elves_set;
    std::string line;
    std::vector<std::pair<int,int>> elves;
    int i = 0;
    while(getline(cin, line)) {
        for (int j=0; j<line.size();j++) {
            if (line[j] == '#')
                elves.push_back({i,j});
        }
        i++;
    }
    for (auto elf : elves) {
        elves_set.insert(elf);
    }
    int i_movement = 0;
    // print_elves(elves_set);
    unsigned int iterations = 0;
    while(true) {
        iterations++;
        std::map<int, pair<int,int>> next_moves;
        UnorderedSetType moves_to_avoid;

        // propose movements
        int start_i = i_movement;
        for (int i_elf=0; i_elf<elves.size();i_elf++) {
            auto pos_to_check = elves[i_elf];
            i_movement = start_i;
            std::pair<int,int> first_available_move = {0,0};
            bool all_empty = true;
            for (auto _ : movements) {
                auto move = movements[i_movement++ % movements.size()];
                bool is_empty;
                if (move.first==0) {

                    is_empty = elves_set.find({pos_to_check.first+1, pos_to_check.second + move.second}) == elves_set.end() && elves_set.find({pos_to_check.first, pos_to_check.second + move.second}) == elves_set.end() && elves_set.find({pos_to_check.first-1, pos_to_check.second + move.second}) == elves_set.end();
                }
                else {
                    is_empty = elves_set.find({pos_to_check.first+move.first, pos_to_check.second + 1}) == elves_set.end() && elves_set.find({pos_to_check.first+move.first, pos_to_check.second}) == elves_set.end() && elves_set.find({pos_to_check.first+move.first, pos_to_check.second-1}) == elves_set.end();
                }

                if (is_empty && first_available_move == pair<int,int>({0,0})) {
                    first_available_move = move;
                }

                if (!is_empty)
                    all_empty = false;
            }
            if (!all_empty) {
                pos_to_check.first += first_available_move.first;
                pos_to_check.second += first_available_move.second;
                if (is_move_already_set(pos_to_check, next_moves))
                    moves_to_avoid.insert(pos_to_check);
                else
                    next_moves[i_elf]=pos_to_check;
            }
        }
        if (next_moves.size() == 0)
            break;

        // execute movements
        for (auto it=next_moves.begin(); it!=next_moves.end(); it++) {
            if (moves_to_avoid.find(it->second) == moves_to_avoid.end()) {
                elves[it->first] = it->second;
            }
        }

        // fill set
        elves_set.clear();
        for (auto elf : elves) {
            elves_set.insert(elf);
        }

        //reset movement counter and increase it
        i_movement = start_i;
        i_movement++;

        // print_elves(elves_set);
    }

    return std::to_string(iterations);
}