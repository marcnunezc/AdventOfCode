std::vector<std::pair<size_t,size_t>> keypad_moves = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0},
};

std::map<std::pair<size_t,size_t>, char> numerical_keypad = {
    {{0,0}, '7'},
    {{0,1}, '8'},
    {{0,2}, '9'},
    {{1,0}, '4'},
    {{1,1}, '5'},
    {{1,2}, '6'},
    {{2,0}, '1'},
    {{2,1}, '2'},
    {{2,2}, '3'},
    {{3,1}, '0'},
    {{3,2}, 'A'},
};

std::map<std::pair<size_t,size_t>, char> directional_keypad = {
    {{0,1}, '^'},
    {{0,2}, 'A'},
    {{1,0}, '<'},
    {{1,1}, 'v'},
    {{1,2}, '>'},
};

std::map<std::pair<size_t,size_t>, char>  keypad_moves_map = {
    {{0,1}, '>'},
    {{0,-1}, '<'},
    {{1,0}, 'v'},
    {{-1,0}, '^'},
};



std::vector<std::string> find_shortest_paths(std::string target_sequence, std::pair<size_t, size_t> current_start, std::map<std::pair<size_t,size_t>, char>& map_to_search, std::map<char, std::pair<size_t,size_t>>& reverse_keypad_map) {
    auto current = current_start;
    std::vector<std::string> all_results;
    for (auto ch : target_sequence) {
        auto end = reverse_keypad_map[ch];
        auto start = current;

        std::map<std::pair<size_t, size_t>, size_t> distance_map;
        std::set<std::pair<size_t, size_t>> visited;
        std::map<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>> parent_map;
        std::set<std::pair<size_t, size_t>> all_neighbours;
        std::map<std::pair<size_t, size_t>, std::vector<std::string>> paths;

        distance_map[current] = 0;
        paths[current].push_back(""); // Start with empty path

        while (current.first != end.first || current.second != end.second) {
            for (auto [dx, dy] : keypad_moves) {
                auto neighbour = std::make_pair(current.first + dx, current.second + dy);

                if (map_to_search.find(neighbour) != map_to_search.end()) {
                    size_t new_dist = distance_map[current] + 1;

                    if (distance_map.find(neighbour) == distance_map.end() || new_dist < distance_map[neighbour]) {
                        distance_map[neighbour] = new_dist;
                        parent_map[neighbour] = {current};
                        paths[neighbour].clear();
                        for (auto path : paths[current]) {
                            paths[neighbour].push_back(path + keypad_moves_map[{dx, dy}]);
                        }
                        all_neighbours.insert(neighbour);
                    } else if (new_dist == distance_map[neighbour]) {
                        parent_map[neighbour].push_back(current);
                        for (auto path : paths[current]) {
                            paths[neighbour].push_back(path + keypad_moves_map[{dx, dy}]);
                        }
                    }
                }
            }

            current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto &l, const auto &r) {
                return distance_map[l] < distance_map[r];
            });
            all_neighbours.erase(current);
        }
        size_t min_changes = 1e16;
        std::string min_path;
        for (auto path : paths[end]) {
            auto starting_char = path[0];
            size_t changes = 0;
            for (size_t i = 1; i < path.size(); i++) {
                if (path[i] != path[i-1]) {
                    changes++;
                }
            }
            min_changes = std::min(min_changes, changes);
        }

        std::vector<std::string> new_min_paths;
        for (auto path : paths[end]) {
            auto starting_char = path[0];
            size_t changes = 0;
            for (size_t i = 1; i < path.size(); i++) {
                if (path[i] != path[i-1]) {
                    changes++;
                }
            }
            if (changes == min_changes) {
                new_min_paths.push_back(path);
            }
        }
        if (all_results.empty()) {
            for (const auto &path : new_min_paths) {
                all_results.push_back(path + "A");
            }
        } else {
            std::vector<std::string> new_results;
            for (const auto &path : new_min_paths) {
                for (auto result : all_results) {
                    new_results.push_back(result + path + "A");
                }
            }
            all_results = new_results;
        }
        current = end;
    }
    return all_results;
}


size_t search_shortest_instruction(std::string target_sequence, std::pair<size_t, size_t> current_start, std::map<std::pair<size_t,size_t>, char>& map_to_search, std::map<char, std::pair<size_t,size_t>>& reverse_keypad_map, int level, int target_level) {

    auto new_directional_results = find_shortest_paths(target_sequence, current_start, map_to_search, reverse_keypad_map);
    if (level == target_level) {
        size_t min_size = 1e16;
        for (auto new_directional_result : new_directional_results) {
            auto final_diretiona_results = find_shortest_paths(new_directional_result, current_start, map_to_search, reverse_keypad_map);
            for (auto final_diretiona_result : final_diretiona_results) {
                min_size = std::min(min_size, final_diretiona_result.size());
            }
        }
        return min_size;
    } else {
        for (auto new_directional_result : new_directional_results) {
            return search_shortest_instruction(new_directional_result, current_start, map_to_search, reverse_keypad_map, level+1, target_level);
        }
    }
}

AOC_DAY(Day21_1) {
    std::string line;
    std::vector<std::string> codes;
    std::size_t sum = 0;
    while (getline(cin,line)) {
        codes.push_back(line);
    }
    std::pair<size_t, size_t> numerical_start = {3,2};
    std::pair<size_t, size_t> directional_start = {0,2};

    // compute reverse map of numerical_keypad
    std::map<char, std::pair<size_t,size_t>> numerical_keypad_reverse;
    for (auto [pos, ch] : numerical_keypad) {
        numerical_keypad_reverse[ch] = pos;
    }

    // compute reverse map of directional_keypad
    std::map<char, std::pair<size_t,size_t>> directional_keypad_reverse;
    for (auto [pos, ch] : directional_keypad) {
        directional_keypad_reverse[ch] = pos;
    }

    auto current = numerical_start;

    for (auto number : codes) {
        size_t min_size = 1e16;
        auto numerical_results = find_shortest_paths(number, numerical_start, numerical_keypad, numerical_keypad_reverse);

        for (auto numerical_result : numerical_results) {
            min_size = std::min(min_size, search_shortest_instruction(numerical_result, directional_start, directional_keypad, directional_keypad_reverse, 1, 1));
        }
        sum += min_size*std::stoi(number.substr(0, number.size()-1));
    }


    return std::to_string(sum);
}

AOC_DAY(Day21_2) {
    return std::to_string(0);
}
