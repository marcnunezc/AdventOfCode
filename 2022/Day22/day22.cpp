typedef std::unordered_map<std::pair<int,int>, int, pair_hash> UnordMapPairIntType;

std::unordered_map<char, char> clockwise_turn = {
    {'n', 'e'},
    {'e', 's'},
    {'s', 'w'},
    {'w', 'n'},
};

std::unordered_map<char, char> counterclockwise_turn = {
    {'n', 'w'},
    {'w', 's'},
    {'s', 'e'},
    {'e', 'n'},
};

char turn(char current, char dir) {
    if (dir == 'R')
        return clockwise_turn[current];
    else
        return counterclockwise_turn[current];
}
bool move(std::pair<int,int>& pos, char dir, UnordMapPairIntType& map)  {
    auto next_pos = pos;
    if (dir == 'n')
        next_pos.second--;
    else if (dir == 's')
        next_pos.second++;
    else if (dir == 'e')
        next_pos.first++;
    else if (dir == 'w')
        next_pos.first--;

    auto is_wall = [&](std::pair<int,int> pos_to_check) {
        if (map[pos_to_check]) // wall
            return false;
        else {
            pos = pos_to_check;
            return true;
        }
    };

    if (map.find(next_pos) == map.end()) {
        //wrap around
        if (dir == 'n') {
            int j=0;
            while (map.find({next_pos.first, j}) == map.end())
                j++;
            while (map.find({next_pos.first, j}) != map.end())
                j++;
            next_pos.second = j-1;
            return is_wall(next_pos);
        }
        else if (dir == 's') {
            int j=0;
            while (map.find({next_pos.first, j}) == map.end())
                j++;
            next_pos.second = j;
            return is_wall(next_pos);
        }
        else if (dir == 'w') {
            int i=0;
            while (map.find({i, next_pos.second}) == map.end())
                i++;
            while (map.find({i, next_pos.second}) != map.end())
                i++;
            next_pos.first = i-1;
            return is_wall(next_pos);
        }
        else if (dir == 'e') {
            int i=0;
            while (map.find({i, next_pos.second}) == map.end())
                i++;
            next_pos.first = i;
            return is_wall(next_pos);
        }
    }
    return is_wall(next_pos);
}

AOC_DAY(Day22_1) {

    UnordMapPairIntType map;
    std::string line;
    std::string instruction;
    int j = 0;
    while(getline(cin, line)) {
        if (line.empty()) {
            getline(cin, instruction);
            break;
        }

        for (int i=0; i<line.size();i++) {
            if (line[i] == '.')
                map[{i,j}] = 0;
            else if (line[i] == '#')
                map[{i,j}] = 1;
        }
        j++;
    }

    std::pair<int,int> pos;
    int i = 0;
    while (++i) {
        if (map.find({i, 0}) != map.end()) {
            pos = {i,0};
            break;
        }
    }

    int head = 0;
    i = 0;
    char current_dir = 'e';
    // cout << "row column facing " << pos.first+1 <<  " "<< pos.second+1 <<  " "<< current_dir <<  endl;
    char next_dir;
    while (head < instruction.size()-1) {
        while(isdigit(instruction[i]) && i < instruction.size())
            i++;
        char next_dir=instruction[i];

        int steps = stoi(instruction.substr(head, i-head));
        // cout << "moving " << steps << " towards " << current_dir <<endl;
        for (int step : std::ranges::iota_view{0, steps}) {
            if (!move(pos, current_dir, map))
                break;
        }
        if (i < instruction.size())
            current_dir = turn(current_dir, next_dir);
        head = ++i;
        // cout << "row column facing " << pos.first+1 <<  " "<< pos.second+1 <<  " "<< current_dir <<  endl;
    }
    std::unordered_map<char,int> dir_to_points = {
        {'e', 0},
        {'s', 1},
        {'w', 2},
        {'n', 3},
    };

    return std::to_string(1000*(pos.second+1)+4*(pos.first+1)+dir_to_points[current_dir]);
}

AOC_DAY(Day22_2) {

    return std::to_string(3);
}