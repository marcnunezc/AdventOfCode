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


std::set<std::string> find_shortest_paths(std::string target_sequence, std::pair<size_t, size_t> current_start, std::map<std::pair<size_t,size_t>, char>& map_to_search, std::map<char, std::pair<size_t,size_t>>& reverse_keypad_map) {
    auto current = current_start;
    std::set<std::string> all_results;
    for (auto ch : target_sequence) {
        auto end = reverse_keypad_map[ch];
        auto start = current;

        std::map<std::pair<size_t, size_t>, size_t> distance_map;
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
                        paths[neighbour].clear();
                        for (auto path : paths[current]) {
                            paths[neighbour].push_back(path + keypad_moves_map[{dx, dy}]);
                        }
                        all_neighbours.insert(neighbour);
                    } else if (new_dist == distance_map[neighbour]) {
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

        if (all_results.empty()) {
            for (const auto &path : paths[end]) {
                all_results.insert(path + "A");
            }
        } else {
            std::set<std::string> new_results;
            for (const auto &path : paths[end]) {
                for (auto result : all_results) {
                    new_results.insert(result + path + "A");
                }
            }
            all_results = new_results;
        }
        current = end;
    }
    return all_results;
}


size_t compute_size(char current,  std::array<char,26>& start, size_t current_depth, size_t final_depth, std::map<std::pair<char,char>, std::vector<std::string>> directional_translations, std::map<std::tuple<char, char, size_t>, size_t>& cache) {
    auto cache_tuple = std::make_tuple(current, start[current_depth], current_depth);
    if (cache.find(cache_tuple) != cache.end())
        return cache[cache_tuple];

    auto result_list = directional_translations[{current, start[current_depth]}];
    std::size_t sum = 1e18;
    if (current_depth == final_depth) {
        return result_list[0].size();
    }
    else {
        for (auto result : result_list) {
            std::size_t partial_sum = 0;
            start[current_depth+1] = result.back();
            for (auto ch : result) {
                partial_sum += compute_size(ch,  start, current_depth+1, final_depth, directional_translations, cache);
                start[current_depth+1] = ch;
            }
            sum = std::min(sum, partial_sum);
        }

    }

    cache[cache_tuple] = sum;

    return sum;
}


size_t solve_problem(size_t max_level) {
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
    std::map<std::pair<char,char>, std::vector<std::string>> directional_translations;


    // find all shortest pathes for all combination of key, start in the directional keypad.
    for (auto [key, value] : directional_keypad_reverse) {
        for (auto [start_key, start_value] : directional_keypad_reverse) {
            auto result = find_shortest_paths(std::string(1, key), start_value,directional_keypad, directional_keypad_reverse);
            for (auto res : result) {
                directional_translations[{key, start_key}].push_back(res);
            }
        }
    }

    for (auto number : codes) {
        size_t min_size = 1e16;
        auto numerical_results = find_shortest_paths(number, numerical_start, numerical_keypad, numerical_keypad_reverse);

        for (auto numerical_result : numerical_results) {

            std::array<char,26> start;
            std::fill(start.begin(), start.end(), 'A');

            size_t size = 0;
            std::map<std::tuple<char, char, size_t>, size_t> cache;
            for (auto ch : numerical_result) {
                size += compute_size(ch, start, 0, max_level, directional_translations,cache);
                start[0] = ch;
            }

            min_size = std::min(min_size, size);
        }
        sum += min_size*std::stoi(number.substr(0, number.size()-1));

    }

    return sum;
}

AOC_DAY(Day21_1) {

    return std::to_string(solve_problem(1));
}


AOC_DAY(Day21_2) {

    return std::to_string(solve_problem(24));
}
