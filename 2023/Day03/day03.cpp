struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

bool any_neighbour_is_symbol(std::vector<std::pair<int,int>>& digit_positions, std::unordered_map<std::pair<int,int>, string, pair_hash>& symbol_positions) {
    for (auto& pos : digit_positions) {
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

void register_neighbours_to_symbol(std::vector<std::pair<int,int>>& digit_positions, std::unordered_map<std::pair<int,int>, std::vector<int>, pair_hash>& symbol_position_to_neighbour_numbers, int number) {
    for (auto& pos : digit_positions) {
        auto i = pos.first;
        auto j = pos.second;
        for (int x = i - 1; x <= i + 1; ++x) {
            for (int y = j - 1; y <= j + 1; ++y) {
                if (symbol_position_to_neighbour_numbers.find({x,y}) != symbol_position_to_neighbour_numbers.end()) {
                    symbol_position_to_neighbour_numbers[{x,y}].push_back(number);
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
    std::vector<int> number_list;
    std::vector<std::vector<std::pair<int,int>>> number_digit_positions_list;
    std::unordered_map<std::pair<int,int>, string, pair_hash> symbol_positions;
    int i=0;
    while (getline(cin, line)) {
        std::string str_number;
        std::vector<std::pair<int,int>> digit_positions;
        for (int j=0; j<line.length(); ++j) {
            if (isdigit(line[j])) {
                str_number += line[j];
                digit_positions.push_back({i, j});
            }
            else {
                if (line[j] != '.') {
                    symbol_positions[{i,j}]=line[j];
                }
            }
            if ((!isdigit(line[j]) || j==line.length()-1) && str_number.length()>0) {
                number_list.push_back(stoi(str_number));
                number_digit_positions_list.push_back(digit_positions);
                str_number.clear();
                digit_positions.clear();
            }
        }
        i++;
    }
    for (int i=0; i<number_list.size(); i++) {
        auto& number = number_list[i];
        auto& digit_positions = number_digit_positions_list[i];

        if (any_neighbour_is_symbol(digit_positions, symbol_positions)) {
            sum += number;
        }

    }
    return std::to_string(sum);
}

AOC_DAY(Day03_2){
    size_t sum = 0;
    std::string line;
    std::vector<int> number_list;
    std::vector<std::vector<std::pair<int,int>>> number_digit_positions_list;
    std::unordered_map<std::pair<int,int>, std::vector<int>, pair_hash> symbol_position_to_neighbour_numbers;
    int i=0;
    while (getline(cin, line)) {
        std::string str_number;
        std::vector<std::pair<int,int>> digit_positions;
        for (int j=0; j<line.length(); ++j) {
            if (isdigit(line[j])) {
                str_number += line[j];
                digit_positions.push_back({i, j});
            }
            else {
                if (line[j] == '*') {
                    symbol_position_to_neighbour_numbers[{i,j}] = {};
                }
            }
            if ((!isdigit(line[j]) || j==line.length()-1) && str_number.length()>0) {
                number_list.push_back(stoi(str_number));
                number_digit_positions_list.push_back(digit_positions);
                str_number.clear();
                digit_positions.clear();
            }
        }
        i++;
    }

    for (int i=0; i<number_list.size(); i++) {
        auto& number = number_list[i];
        auto& digit_positions = number_digit_positions_list[i];

        register_neighbours_to_symbol(digit_positions, symbol_position_to_neighbour_numbers, number);
    }

    for (auto& values : symbol_position_to_neighbour_numbers) {
        if (values.second.size()==2) {
            sum += values.second[0]*values.second[1];
        }
    }

    return std::to_string(sum);
}
