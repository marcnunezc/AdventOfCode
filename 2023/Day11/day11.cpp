IntType solve_day11(IntType expansion_rate) {
    IntType sum = 0;
    std::vector<std::pair<IntType,IntType>> galaxies;
    int i = 0;
    std::vector<IntType> empty_rows;
    std::vector<IntType> empty_columns;
    std::unordered_set<int> occupied_columns;

    std::string line;
    int line_length;
    while(getline(cin, line)) {
        line_length = line.size();
        if (line.find('#') == std::string::npos) {
            empty_rows.push_back(i);
        } else {
            for (int j=0; j<line.size();j++) {
                if (line[j] == '#') {
                    galaxies.push_back({i,j});
                    occupied_columns.insert(j);
                }
            }
        }
        i++;
    }
    for (int j = 0;  j<line_length; j++) {
        if (occupied_columns.find(j) == occupied_columns.end())
            empty_columns.push_back(j);
    }

    for (int i = 0; i < empty_rows.size(); i++) {
        for (int j = i+1; j< empty_rows.size(); j++) {
            empty_rows[j] += expansion_rate;
        }
        for (int j = 0; j< galaxies.size(); j++) {
            if (galaxies[j].first > empty_rows[i])
                galaxies[j].first += expansion_rate;
        }
    }

    for (int i = 0; i < empty_columns.size(); i++) {
        for (int j = i+1; j< empty_columns.size(); j++) {
            empty_columns[j] += expansion_rate;
        }
        for (int j = 0; j< galaxies.size(); j++) {
            if (galaxies[j].second > empty_columns[i])
                galaxies[j].second += expansion_rate;
        }
    }
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i; j < galaxies.size(); j++) {
            sum += std::abs(galaxies[i].first-galaxies[j].first) + std::abs(galaxies[i].second-galaxies[j].second);
        }
    }
    return sum;
}

AOC_DAY(Day11_1){
    return std::to_string(solve_day11(1));
}

AOC_DAY(Day11_2){
    return std::to_string(solve_day11(1000000-1));
}