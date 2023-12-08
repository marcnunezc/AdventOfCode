AOC_DAY(Day08_1){
    std::size_t sum = 0;
    std::string instructions;
    getline(cin, instructions);
    std::string line;
    std::unordered_map<std::string, std::pair<std::string,std::string>> desert_map;
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        std::string node, left, right;
        line.erase(std::remove_if(line.begin(), line.end(), []( auto const& c ) -> bool { return !std::isalnum(c) && c != ' '; }), line.end());
        std::stringstream ss(line);
        ss >> node >> left >> right;
        desert_map[node] = {left, right};
    }

    std::string current = "AAA";
    int i = 0;
    while (current.compare("ZZZ")) {
        sum++;
        current = instructions[i] == 'L' ? desert_map[current].first : desert_map[current].second;
        i = ++i % instructions.size();
    }
    return std::to_string(sum);
}

AOC_DAY(Day08_2){
    std::size_t iterations = 0;
    std::string instructions;
    getline(cin, instructions);
    std::string line;
    std::unordered_map<std::string, std::pair<std::string,std::string>> desert_map;
    std::vector<string> current_vector;
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        std::string node, left, right;
        line.erase(std::remove_if(line.begin(), line.end(), []( auto const& c ) -> bool { return !std::isalnum(c) && c != ' '; }), line.end());
        std::stringstream ss(line);
        ss >> node >> left >> right;
        desert_map[node] = {left, right};
        if (node.back() == 'A') {
            current_vector.push_back(node);
        }
    }

    std::vector<IntType> appearances_vector(current_vector.size(), 0);
    int i = 0;
    // store first occurance of a node ending in Z for every start
    while (std::any_of(appearances_vector.begin(), appearances_vector.end(), [](IntType value) { return value == 0;})) {
        iterations++;
        for (auto& current : current_vector) {
            current = instructions[i] == 'L' ? desert_map[current].first : desert_map[current].second;
        }
        i = ++i % instructions.size();

        for (int j = 0; j< current_vector.size(); j++) {
            if (current_vector[j].back() == 'Z') {
                appearances_vector[j]=iterations;
            }
        }
    }
    // compute lcm for all values
    return std::to_string(std::reduce(appearances_vector.begin(), appearances_vector.end(), 1L, std::lcm<IntType, IntType>));
}