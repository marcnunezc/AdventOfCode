
AOC_DAY(Day18_1){
    std::string line;
    std::vector<std::tuple<char, int, std::string>> instructions_list;
    std::unordered_set<std::pair<int,int>, pair_hash> sparse_matrix;
    while(getline(cin, line)) {
        std::stringstream ss(line);
        char dir;
        int num;
        std::string code;
        ss >> dir >> num >> code;
        instructions_list.push_back({dir,num,code});
    }
    std::pair<int,int> current{0,0};
    sparse_matrix.insert(current);
    for (auto instruction : instructions_list) {
        char dir;
        int num;
        std::string code;
        std::tie(dir, num, code) = instruction;
        for (int i=0; i<num; i++) {
            if (dir == 'R')
                current.second++;
            else if (dir == 'L')
                current.second--;
            else if (dir == 'D')
                current.first++;
            else if (dir == 'U')
                current.first--;
            sparse_matrix.insert(current);
        }
        cout << dir << " " << num << " " << code << endl;
    }
    auto max_i = (*max_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; })).first;
    auto min_i = (*min_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; })).first;
    auto max_j = (*max_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })).second;
    auto min_j = (*min_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })).second;
    cout << max_i << endl;
    cout << min_i << endl;
    cout << max_j << endl;
    cout << min_i << endl;
    for (int i=min_i; i<max_i+1; i++) {
        for (int j=min_j; j<max_j+1; j++) {
            if (sparse_matrix.find({i,j})!=sparse_matrix.end())
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
    return std::to_string(0);
}

AOC_DAY(Day18_2){
    size_t sum = 0;

    return std::to_string(sum);
}