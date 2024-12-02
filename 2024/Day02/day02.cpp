AOC_DAY(Day02_1){

    std::string line;
    std::vector<std::vector<size_t>> levels_list;
    levels_list.reserve(1000);
    while(getline(cin, line)) {
        std::vector<size_t> levels;
        levels.reserve(10);
        std::stringstream ss(line);
        std::size_t level;
        while (ss >> level) {
            levels.push_back(level);
        }
        levels_list.push_back(levels);
    }
    std::size_t sum = 0;
    for (auto& levels: levels_list) {
        bool decreasing = levels[0] > levels[1];
        bool safe = true;
        for (size_t i = 1; i<levels.size(); i++) {
            int diff = levels[i] - levels[i-1];

            if (diff > 0 && diff < 4  && !decreasing) {
                continue;
            }
            else if (diff < 0 && diff > -4 && decreasing) {
                continue;
            }
            else {
                safe=false;
                break;
            }
        }
        if (safe) sum++;
    }

    return std::to_string(sum);
}

AOC_DAY(Day02_2){

    std::string line;
    std::vector<std::vector<size_t>> levels_list;
    levels_list.reserve(1000);
    while(getline(cin, line)) {
        std::vector<size_t> levels;
        levels.reserve(10);
        std::stringstream ss(line);
        std::size_t level;
        while (ss >> level) {
            levels.push_back(level);
        }
        levels_list.push_back(levels);
    }
    std::size_t sum = 0;
    auto check_level = [] (const std::vector<size_t>& levels_to_check) {
        bool decreasing = levels_to_check[0] > levels_to_check[1];
        for (size_t i = 1; i<levels_to_check.size(); i++) {
            int diff = levels_to_check[i] - levels_to_check[i-1];
            if (diff > 0 && diff < 4  && !decreasing) {
                continue;
            }
            else if (diff < 0 && diff > -4 && decreasing) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    };

    for (auto& levels: levels_list) {
        if (check_level(levels)) {
            sum++;
        } else {
            for (std::size_t i=0; i<levels.size(); i++) {
                auto levels_copy = levels;
                levels_copy.erase(levels_copy.begin()+i);
                if (check_level(levels_copy)) {
                    sum++;
                    break;
                }
            }
        }
    }

    return std::to_string(sum);
}
