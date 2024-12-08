bool add_antinode(std::set<std::pair<int,int>>& antinode_set, int max_i, int max_j, int xa, int ya) {
    if (xa >= 0 && xa < max_i && ya >= 0 && ya < max_j) {
        antinode_set.insert({xa, ya});

        return true;
    }
    return false;
}

AOC_DAY(Day08_1) {

    std::string line;
    std::size_t sum = 0;
    std::unordered_map<char, std::vector<std::pair<int,int>>> antenna_map;
    std::set<std::pair<int,int>> antenna_set;
    std::set<std::pair<int,int>> antinode_set;

    int i = 0;
    int max_j;
    while (getline(cin, line)) {
        max_j = line.size();
        for (int j=0; j<line.size();j++) {
            auto ch = line[j];
            if (ch != '.') {
                if (antenna_map.find(ch) == antenna_map.end()) {
                    std::vector<std::pair<int,int>> location_list;
                    location_list.push_back({i,j});
                    antenna_map[ch] = location_list;
                } else {
                    antenna_map[ch].push_back({i,j});
                }
                antenna_set.insert({i,j});
            }
        }
        i++;
    }
    int max_i = i;

    for (auto const& [ch, antenna_list] : antenna_map)
    {
        for(size_t i = 0; i<antenna_list.size()-1; i++) {
            for(size_t j = i+1; j<antenna_list.size(); j++) {
                auto x1 = antenna_list[i].first;
                auto x2 = antenna_list[j].first;
                auto y1 = antenna_list[i].second;
                auto y2 = antenna_list[j].second;

                auto xa1 = 2*x1-x2;
                auto ya1 = 2*y1-y2;
                add_antinode(antinode_set, max_i, max_j, xa1, ya1);

                auto xa2 = 2*x2-x1;
                auto ya2 = 2*y2-y1;
                add_antinode(antinode_set, max_i, max_j, xa2, ya2);
            }
        }
    }

    return std::to_string(antinode_set.size());
}

AOC_DAY(Day08_2){

  std::string line;
    std::size_t sum = 0;
    std::unordered_map<char, std::vector<std::pair<int,int>>> antenna_map;
    std::set<std::pair<int,int>> antenna_set;
    std::set<std::pair<int,int>> antinode_set;

    int i = 0;
    int max_j;
    while (getline(cin, line)) {
        max_j = line.size();
        for (int j=0; j<line.size();j++) {
            auto ch = line[j];
            if (ch != '.') {
                if (antenna_map.find(ch) == antenna_map.end()) {
                    std::vector<std::pair<int,int>> location_list;
                    location_list.push_back({i,j});
                    antenna_map[ch] = location_list;
                } else {
                    antenna_map[ch].push_back({i,j});
                }
                antenna_set.insert({i,j});
            }
        }
        i++;
    }
    int max_i = i;

    for (auto const& [ch, antenna_list] : antenna_map)
    {
        for(size_t i = 0; i<antenna_list.size()-1; i++) {
            for(size_t j = i+1; j<antenna_list.size(); j++) {
                auto x1 = antenna_list[i].first;
                auto x2 = antenna_list[j].first;
                auto y1 = antenna_list[i].second;
                auto y2 = antenna_list[j].second;

                auto dx = x1-x2;
                auto dy = y1-y2;

                auto xa1 = x1-dx;
                auto ya1 = y1-dy;
                while (add_antinode(antinode_set, max_i, max_j, xa1, ya1)) {
                    xa1 -= dx;
                    ya1 -= dy;
                }

                auto xa2 = x2+dx;
                auto ya2 = y2+dy;
                while (add_antinode(antinode_set, max_i, max_j, xa2, ya2)) {
                    xa2 += dx;
                    ya2 += dy;
                }
            }
        }
    }

    return std::to_string(antinode_set.size());
}
