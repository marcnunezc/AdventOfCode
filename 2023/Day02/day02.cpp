AOC_DAY(Day02_1){
    // Check if any number of boxes exceed the maximum for each color.
    std::unordered_map<std::string, int> max_colors = {
        {"red", 12},
        {"green", 13},
        {"blue", 14},
    };
    size_t sum = 0;
    std::string line;
    while(getline(cin, line)) {
        bool to_sum = true;
        int id;
        auto game_id_string = line.substr(0, line.find(":"));
        sscanf(game_id_string.c_str(), "Game %d", &id);
        auto sets_string = line.substr(strlen(game_id_string.c_str())+1);
        std::istringstream ss(sets_string);
        while (getline(ss, sets_string, ';') && to_sum) {
            std::istringstream set_ss(sets_string);
            std::string set;
            while (getline(set_ss, set, ',')) {
                std::istringstream box_ss(set);
                std::string color;
                int number;
                box_ss >> number;
                box_ss >> color;
                if (number > max_colors[color]) {
                    to_sum = false;
                    break;
                }
            }
        }
        if (to_sum)
            sum += id;

    }
    return std::to_string(sum);
}

AOC_DAY(Day02_2){
    // Find max values for each color and multiply
    size_t sum = 0;
    std::string line;
    while(getline(cin, line)) {
        std::unordered_map<std::string, int> max_colors;
        auto game_id_string = line.substr(0, line.find(":"));
        auto sets_string = line.substr(strlen(game_id_string.c_str())+1);
        std::istringstream ss(sets_string);
        while (getline(ss, sets_string, ';')) {
            std::istringstream set_ss(sets_string);
            std::string set;
            while (getline(set_ss, set, ',')) {
                std::istringstream box_ss(set);
                std::string color;
                int number;
                box_ss >> number;
                box_ss >> color;
                max_colors[color] = max(max_colors[color], number);
            }
        }
        sum += max_colors["red"]*max_colors["green"]*max_colors["blue"];
    }
    return std::to_string(sum);
}
