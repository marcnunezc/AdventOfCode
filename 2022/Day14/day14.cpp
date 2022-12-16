enum cave {
    AIR,
    ROCK,
    SAND,
    FLYING,
};

std::unordered_map<std::pair<int,int>, cave, pair_hash> read_cave_system() {

    std::string line;
    std::vector<std::vector<std::pair<int,int>>> rock_lines;
    std::unordered_map<std::pair<int,int>, cave, pair_hash> cave_map;
    while(getline(cin, line)) {
        std::vector<std::pair<int,int>> rock_line;
        cout << line << endl;
        int value;
        size_t pos = 0;
        std::string substr;
        while ((pos = line.find(" -> ")) != std::string::npos) {
            substr = line.substr(0, pos);
            std::pair<int,int> rock;
            sscanf(substr.c_str(), "%i,%i", &rock.first, &rock.second);
            rock_line.push_back(rock);
            line.erase(0, pos + 4);
        }
        std::pair<int,int> rock;
        sscanf(line.c_str(), "%i,%i", &rock.first, &rock.second);
        rock_line.push_back(rock);
        rock_lines.push_back(rock_line);

    }
    for (auto rock_line : rock_lines) {
        for (int k=1; k<rock_line.size(); k++) {
            if (rock_line[k-1].first > rock_line[k].first)
                for (int coord : std::ranges::iota_view{rock_line[k].first, rock_line[k-1].first+1})
                    cave_map[{coord, rock_line[k].second}]=cave::ROCK;
            else if (rock_line[k-1].first < rock_line[k].first)
                for (int coord : std::ranges::iota_view{rock_line[k-1].first, rock_line[k].first+1})
                    cave_map[{coord, rock_line[k].second}]=cave::ROCK;
            if (rock_line[k-1].second>rock_line[k].second)
                for (int coord : std::ranges::iota_view{rock_line[k].second, rock_line[k-1].second+1})
                    cave_map[{rock_line[k].first, coord}]=cave::ROCK;
            else if (rock_line[k-1].second < rock_line[k].second)
                for (int coord : std::ranges::iota_view{rock_line[k-1].second, rock_line[k].second+1})
                    cave_map[{rock_line[k].first, coord}]=cave::ROCK;
        }
    }

    return cave_map;
}

void draw_map(std::unordered_map<std::pair<int,int>, cave, pair_hash>& cave_map) {
    for (int i = -2; i<15;i++) {
        for (int j = 485; j<515;j++) {
            if (cave_map.find({j,i})!=cave_map.end())
                if (cave_map[{j,i}] == cave::ROCK)
                    cout << "#";
                else if (cave_map[{j,i}] == cave::SAND)
                    cout << "o";
                else
                    cout << "x";
            else
                cout << ".";
        }
        cout << endl;
    }
    cout << endl;
};

AOC_DAY(Day14_1) {
    std::unordered_map<std::pair<int,int>, cave, pair_hash> cave_map = read_cave_system();
    int max_i=0;
    for (auto it = cave_map.begin(); it!=cave_map.end(); it++) {
        max_i=max(max_i,it->first.second);
    }

    bool is_sand_stopped = true;
    int i = 0;
    int j = 500;
    while (is_sand_stopped) {
        if (cave_map.find({j,i})==cave_map.end())
            i++;
        else
            if (cave_map.find({j-1,i})==cave_map.end())
                j--;
            else if (cave_map.find({j+1,i})==cave_map.end())
                j++;
            else {

                cave_map[{j,i-1}] = cave::SAND;
                // draw_map(cave_map);
                i = 0;
                j = 500;
            }
        if (i>max_i+1) {
            cave_map[{j,i}] = cave::FLYING;
            is_sand_stopped=false;
            // draw_map(cave_map);
        }
    }

    int count = 0;

    for (auto it = cave_map.begin(); it!=cave_map.end(); it++) {
        if (it->second == cave::SAND)
            count++;
    }

    return std::to_string(count);
}

AOC_DAY(Day14_2) {
    std::unordered_map<std::pair<int,int>, cave, pair_hash> cave_map = read_cave_system();
    int max_i=0;
    for (auto it = cave_map.begin(); it!=cave_map.end(); it++) {
        max_i=max(max_i,it->first.second);
    }

    bool is_sand_stopped = true;
    int i = 0;
    int j = 500;
    while (is_sand_stopped) {
        if (cave_map.find({j,i})==cave_map.end() && i < max_i+2)
            i++;
        else
            if (cave_map.find({j-1,i})==cave_map.end()  && i < max_i+2)
                j--;
            else if (cave_map.find({j+1,i})==cave_map.end()  && i < max_i+2)
                j++;
            else {

                cave_map[{j,i-1}] = cave::SAND;
                // draw_map(cave_map);
                if (j == 500 && i-1==0)
                    is_sand_stopped=false;
                i = 0;
                j = 500;
            }
    }

    int count = 0;

    for (auto it = cave_map.begin(); it!=cave_map.end(); it++) {
        if (it->second == cave::SAND)
            count++;
    }

    return std::to_string(count);
}
