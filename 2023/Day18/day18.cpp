void look_for_neighs(std::pair<int,int> chunk, std::unordered_set<std::pair<int,int>, pair_hash>& chunk_set, std::unordered_set<std::pair<int,int>, pair_hash>& visited_chunks, std::unordered_set<std::pair<int,int>, pair_hash>& sparse_matrix, int min_i, int min_j, int max_i, int max_j) {

    chunk_set.insert(chunk);
    visited_chunks.insert(chunk);
    std::vector<std::pair<int,int>> neigh_increment_list = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };
    for (auto neigh_increment : neigh_increment_list) {
        std::pair<int,int> neigh = {chunk.first+neigh_increment.first, chunk.second+neigh_increment.second};
        if (neigh.first > min_i && neigh.second > min_j && neigh.first < max_i+1 && neigh.second < max_j+1) {
            if (sparse_matrix.find(neigh) == sparse_matrix.end() && visited_chunks.find(neigh) == visited_chunks.end() ){
                look_for_neighs(neigh, chunk_set, visited_chunks, sparse_matrix, min_i,min_j,max_i,max_j);
            }
        }
    }
    return;
}

bool is_outside(std::unordered_set<std::pair<int,int>, pair_hash>& chunk_set,  int min_i, int min_j, int max_i, int max_j) {
    for (auto point : chunk_set) {
        if (point.first == max_i || point.first == min_i || point.second == max_j || point.second == min_j)
            return true;
    }
    return false;
}

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
    }
    auto max_i = (*max_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; })).first;
    auto min_i = (*min_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; })).first;
    auto max_j = (*max_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })).second;
    auto min_j = (*min_element(sparse_matrix.begin(), sparse_matrix.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })).second;
    for (int i=min_i; i<max_i+1; i++) {
        for (int j=min_j; j<max_j+1; j++) {
            if (sparse_matrix.find({i,j})!=sparse_matrix.end())
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
    cout << endl;

    int sum_inside = 0;
    std::vector<std::unordered_set<std::pair<int,int>, pair_hash>> chunks_list;
    std::unordered_set<std::pair<int,int>, pair_hash> visited_chunks;
    for (int i=min_i; i<max_i+1; i++) {
        for (int j=min_j; j<max_j+1; j++) {
            if (visited_chunks.find({i,j}) == visited_chunks.end() && sparse_matrix.find({i,j})==sparse_matrix.end()) {
                std::unordered_set<std::pair<int,int>, pair_hash> chunk_set;
                look_for_neighs({i,j}, chunk_set, visited_chunks, sparse_matrix, min_i, min_j, max_i, max_j);
                chunks_list.push_back(chunk_set);

            }
        }
    }

    for (auto chunk_set : chunks_list) {
        if (!is_outside(chunk_set, min_i, min_j, max_i, max_j))
            sum_inside+=chunk_set.size();
    }

    return std::to_string(sum_inside+sparse_matrix.size());
}

AOC_DAY(Day18_2){
    size_t sum = 0;

    return std::to_string(sum);
}