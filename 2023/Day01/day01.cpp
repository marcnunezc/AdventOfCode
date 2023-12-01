AOC_DAY(Day01_1){

    std::string line;
    unsigned int sum=0;
    while(getline(cin, line)) {
        unsigned int min=0, max=0;
        for (auto& digit : line) {
            if (isdigit(digit)) {
                if (min == 0) {
                    min = digit-'0';
                    max = min;
                }
                else {
                    max = digit-'0';
                }
            }
        }
        sum += min*10 + max;
    }

    return std::to_string(sum);
}

AOC_DAY(Day01_2){

    std::unordered_map<std::string, int> string_to_number = {
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9}
    };

    std::string line;
    unsigned int sum=0;
    while(getline(cin, line)) {
        std::vector<std::pair<int, int>> number_to_positions;
        for (auto& number_pair : string_to_number) {
            // find all positions for string numbers
            auto pos = line.find(number_pair.first);
            while (pos != string::npos) {
                number_to_positions.push_back({string_to_number[number_pair.first], pos});
                pos = line.find(number_pair.first, pos+1);
            }
            // find all positions for digits
            pos = line.find(std::to_string(number_pair.second));
            while (pos != string::npos) {
                number_to_positions.push_back({number_pair.second, pos});
                pos = line.find(std::to_string(number_pair.second), pos+1);
            }
        }
        // get number at min position and at max position
        auto minmax_pair = minmax_element(number_to_positions.begin(),
            number_to_positions.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
        sum += minmax_pair.first->first*10 + minmax_pair.second->first;
    }

    return std::to_string(sum);
}
