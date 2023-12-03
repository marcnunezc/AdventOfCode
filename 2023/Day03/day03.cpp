struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

bool is_symbol_a_neighbour(std::vector<std::pair<int,int>>& number_positions, std::unordered_map<std::pair<int,int>, string, pair_hash>& symbol_positions) {
    for (auto& pos : number_positions) {
        auto i = pos.first;
        auto j = pos.second;
        for (int x = i - 1; x <= i + 1; ++x) {
            for (int y = j - 1; y <= j + 1; ++y) {
                if (symbol_positions.find({x,y}) != symbol_positions.end()) {
                    return true;
                }
            }
        }

    }
    return false;
}

void register_neighbours_to_symbol(std::vector<std::pair<int,int>>& number_positions, std::unordered_map<std::pair<int,int>, std::vector<int>, pair_hash>& symbol_positions, int number) {
    for (auto& pos : number_positions) {
        auto i = pos.first;
        auto j = pos.second;
        for (int x = i - 1; x <= i + 1; ++x) {
            for (int y = j - 1; y <= j + 1; ++y) {
                if (symbol_positions.find({x,y}) != symbol_positions.end()) {
                    symbol_positions[{x,y}].push_back(number);
                    return;
                }
            }
        }

    }
    return;
}

AOC_DAY(Day03_1){
    size_t sum = 0;
    std::string line;
    std::vector<std::vector<int>> engine;
    std::vector<int> number_list;
    std::vector<std::vector<std::pair<int,int>>> number_position_list;
    std::unordered_map<std::pair<int,int>, string, pair_hash> symbol_positions;
    int i=0;
    while (getline(cin, line)) {
        std::string str_number;
        std::vector<std::pair<int,int>> positions;
        for (int j=0; j<line.length(); ++j) {
            if (isdigit(line[j])) {
                str_number += line[j];
                positions.push_back({i, j});
            }
            else {
                if (line[j] != '.') {
                    symbol_positions[{i,j}]=line[j];
                }
                if (str_number.length()>0) {
                    number_list.push_back(stoi(str_number));
                    number_position_list.push_back(positions);
                    str_number.clear();
                    positions.clear();
                }
            }
        }
        if (str_number.length()>0) {
            number_list.push_back(stoi(str_number));
            number_position_list.push_back(positions);
            str_number.clear();
            positions.clear();
        }

        i++;
    }
    for (int i=0; i<number_list.size(); i++) {
        auto& number = number_list[i];
        auto& positions = number_position_list[i];

        if (is_symbol_a_neighbour(positions, symbol_positions)) {
            sum += number;
        }

    }
    return std::to_string(sum);
}

AOC_DAY(Day03_2){
    size_t sum = 0;
    std::string line;
    std::vector<std::vector<int>> engine;
    std::vector<int> number_list;
    std::vector<std::vector<std::pair<int,int>>> number_position_list;
    std::unordered_map<std::pair<int,int>, std::vector<int>, pair_hash> symbol_positions;
    int i=0;
    while (getline(cin, line)) {
        std::string str_number;
        std::vector<std::pair<int,int>> positions;
        for (int j=0; j<line.length(); ++j) {
            if (isdigit(line[j])) {
                str_number += line[j];
                positions.push_back({i, j});
            }
            else {
                if (line[j] == '*') {
                    symbol_positions[{i,j}]=std::vector<int>();
                }
                if (str_number.length()>0) {
                    number_list.push_back(stoi(str_number));
                    number_position_list.push_back(positions);
                    str_number.clear();
                    positions.clear();
                }
            }
        }
        if (str_number.length()>0) {
            number_list.push_back(stoi(str_number));
            number_position_list.push_back(positions);
            str_number.clear();
            positions.clear();
        }
        i++;
    }

    for (int i=0; i<number_list.size(); i++) {
        auto& number = number_list[i];
        auto& positions = number_position_list[i];

        register_neighbours_to_symbol(positions, symbol_positions, number);
    }

    for (auto& values : symbol_positions) {
        if (values.second.size()==2) {
            sum += values.second[0]*values.second[1];
        }
    }


    return std::to_string(sum);
}
