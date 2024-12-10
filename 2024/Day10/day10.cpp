std::vector<std::pair<int,int>> delta_pos_list = {{1,0},
                                                  {0,-1},
                                                  {-1,0},
                                                  {0,1}
                                                };


void find_tops_of_mountain(std::vector<std::vector<int>>& matrix,int start_value, int i, int j, int& count, std::set<std::pair<int,int>>* p_visited) {

    if (start_value == 9) {
        if (p_visited) { // part1
            if (p_visited->find({i,j})==p_visited->end()) {
                count++;
                p_visited->insert({i,j});
            }
        } else {       // part2
            count++;
        }
        return;
    }

    int max_i = matrix.size();
    int max_j = matrix[0].size();

    for (auto& delta : delta_pos_list) {
        int new_i = i + delta.first;
        int new_j = j + delta.second;
        if (new_i >= 0 && new_i < max_i && new_j >= 0 && new_j < max_j && start_value+1 == matrix[new_i][new_j]) {
            find_tops_of_mountain(matrix, start_value+1, new_i, new_j, count, p_visited);
        }
    }
}

AOC_DAY(Day10_1) {

    std::string line;
    std::size_t sum = 0;
    std::vector<std::vector<int>> matrix;
    std::set<std::pair<int,int>> zero_locations;
    int i=0;
    while(getline(cin, line)) {
        std::vector<int> row;
        for (int j=0; j<line.size();j++) {
            row.push_back(line[j]-'0');

            if ((line[j]-'0') == 0)
                zero_locations.insert({i,j});
        }
        matrix.push_back(row);
        i++;
    }

    for (auto& zero_location : zero_locations) {
        int count = 0;
        std::set<std::pair<int,int>> visited;
        find_tops_of_mountain(matrix, 0, zero_location.first, zero_location.second, count, &visited);
        sum += count;
    }

    return std::to_string(sum);
}


AOC_DAY(Day10_2){

    std::string line;
    std::size_t sum = 0;
    std::vector<std::vector<int>> matrix;
    std::set<std::pair<int,int>> zero_locations;
    int i=0;
    while(getline(cin, line)) {
        std::vector<int> row;
        for (int j=0; j<line.size();j++) {
            row.push_back(line[j]-'0');

            if ((line[j]-'0') == 0)
                zero_locations.insert({i,j});
        }
        matrix.push_back(row);
        i++;
    }

    for (auto& zero_location : zero_locations) {
        int count = 0;
        find_tops_of_mountain(matrix, 0, zero_location.first, zero_location.second, count, nullptr);
        sum += count;
    }

    return std::to_string(sum);
}
