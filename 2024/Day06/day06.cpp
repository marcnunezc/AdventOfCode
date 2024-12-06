std::unordered_map<char,char> next_dir= {
                                            {'U', 'R'},
                                            {'R', 'D'},
                                            {'D', 'L'},
                                            {'L', 'U'},
                                          };

AOC_DAY(Day06_1){

    std::string line;
    char current_dir = 'U';
    std::set<std::pair<int,int>> block_positions;
    std::set<std::pair<int,int>> visited_positions;
    std::pair<int,int> current_pos;
    int i = 0;
    int max_size_i, max_size_j;
    while (getline(cin,line)) {
        max_size_j = line.size();
        for (int j = 0; j<line.size(); j++) {
            if (line[j] == '#')
                block_positions.insert({i,j});
            else if (line[j] == '^')
                current_pos = {i,j};
        }
        i++;
    }
    max_size_i = i;

    while(true) {

        visited_positions.insert(current_pos);
        auto new_pos = current_pos;
        if (current_dir == 'U')
            new_pos.first--;
        else if (current_dir == 'R')
            new_pos.second++;
        else if (current_dir == 'L')
            new_pos.second--;
        else if (current_dir == 'D')
            new_pos.first++;

        if (block_positions.find(new_pos) != block_positions.end())
            current_dir = next_dir[current_dir];
        else{
            current_pos = new_pos;
        }

        if (current_pos.first < 0 || current_pos.first >= max_size_i || current_pos.second < 0 || current_pos.second >= max_size_j)
            break;

    }

    return std::to_string(visited_positions.size());
}


bool compute_path(std::pair<int,int> starting_pos, std::set<std::pair<int,int>>& block_positions, std::set<std::pair<int,int>>& visited_positions, int max_size_i, int max_size_j) {

    char current_dir = 'U';
    auto current_pos = starting_pos;
    size_t loops = 0;
    size_t max_loops = 1000;
    std::set<std::tuple<int,int,char>> visited_pos_and_dir;
    do {
        visited_positions.insert(current_pos);
        visited_pos_and_dir.insert({current_pos.first,current_pos.second,current_dir});
        auto new_pos = current_pos;
        if (current_dir == 'U')
            new_pos.first--;
        else if (current_dir == 'R')
            new_pos.second++;
        else if (current_dir == 'L')
            new_pos.second--;
        else if (current_dir == 'D')
            new_pos.first++;

        if (block_positions.find(new_pos) != block_positions.end())
            current_dir = next_dir[current_dir];
        else{
            current_pos = new_pos;
        }

        if (current_pos.first < 0 || current_pos.first >= max_size_i || current_pos.second < 0 || current_pos.second >= max_size_j) {
            return true;
        }

    } while (visited_pos_and_dir.find({current_pos.first,current_pos.second,current_dir}) == visited_pos_and_dir.end());

    return false;
}

AOC_DAY(Day06_2){


    std::string line;
    std::size_t sum = 0;
    char current_dir = 'U';
    std::set<std::pair<int,int>> block_positions;
    std::set<std::pair<int,int>> visited_positions;
    std::pair<int,int> starting_pos;
    int i = 0;
    int max_size_i, max_size_j;
    while (getline(cin,line)) {
        max_size_j = line.size();
        for (int j = 0; j<line.size(); j++) {
            if (line[j] == '#')
                block_positions.insert({i,j});
            else if (line[j] == '^')
                starting_pos = {i,j};
        }
        i++;
    }
    max_size_i = i;

    compute_path(starting_pos, block_positions, visited_positions, max_size_i, max_size_j);


    for (auto block_candidate : visited_positions)
    {

        if (block_candidate == starting_pos)
            continue;
        std::set<std::pair<int,int>> new_block_positions=block_positions;
        std::set<std::pair<int,int>> visited_dummy;
        new_block_positions.insert(block_candidate);

        if (!compute_path(starting_pos, new_block_positions, visited_dummy, max_size_i, max_size_j)) {
            sum++;
        }

    }

    return std::to_string(sum);
}
