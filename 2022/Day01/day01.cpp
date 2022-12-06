AOC_DAY(Day01_1){
    int value, max = 0, current = 0;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            max = std::max(current , max);
            current = 0;
        }
        else {
            current += stoi(line);
        }
    }
    return std::to_string(max);
}

AOC_DAY(Day01_2){
    int value, current = 0;
    string line;
    std::array<int, 3> max_values = {0,0,0};
    auto get_max_values = [&] () {
        for (unsigned int i = 0; i < max_values.size(); i++) {
            if (current  > max_values[i]) {
                max_values[i] = current;
                break;
            }
        }
        sort(max_values.begin(), max_values.end());
        current = 0;
    };
    while (getline(cin, line)) {
        if (line.empty()) {
            get_max_values();
        }
        else {
            current += stoi(line);
        }
    }
    get_max_values();

    return std::to_string(std::accumulate(max_values.begin(), max_values.end(), 0));
}
