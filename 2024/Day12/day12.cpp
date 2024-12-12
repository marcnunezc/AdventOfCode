
void find_region(std::pair<int,int> current, std::set<std::pair<int, int>>& region_set, std::vector<std::vector<int>>& matrix)
{
    auto size_i = matrix.size();
    auto size_j = matrix[0].size();
    auto value = matrix[current.first][current.second];

    std::vector<std::pair<int,int>> neigh_deltas =  {{1,0},{-1,0},{0,1},{0,-1}};
    for (int i = 0; i<neigh_deltas.size(); i++) {
        auto new_i = neigh_deltas[i].first+current.first;
        auto new_j = neigh_deltas[i].second+current.second;
        if (new_i<0 || new_i >= size_i)
            continue;
        if (new_j<0 || new_j >= size_j)
            continue;
        if (matrix[new_i][new_j] == value && region_set.find({new_i,new_j}) == region_set.end()) {
            // cout << "found " << (char) matrix[new_i][new_j] << " in " << new_i << " " << new_j << endl;
            region_set.insert({new_i,new_j});
            find_region({new_i,new_j}, region_set, matrix);
        }
    }
}

std::size_t compute_perimeter( std::set<std::pair<int, int>>& region_set, std::vector<std::vector<int>>& matrix) {
    std::size_t perimeter = 0;
    auto size_i = matrix.size();
    auto size_j = matrix[0].size();
    std::vector<std::pair<int,int>> neigh_deltas =  {{1,0},{-1,0},{0,1},{0,-1}};
    for (auto& current : region_set) {
        for (int i = 0; i<neigh_deltas.size(); i++) {

            auto new_i = neigh_deltas[i].first+current.first;
            auto new_j = neigh_deltas[i].second+current.second;
            if (new_i<0 || new_i >= size_i || new_j<0 || new_j >= size_j || matrix[new_i][new_j] != matrix[current.first][current.second]) {
                perimeter++;
            }
        }
    }
    return perimeter;
}

AOC_DAY(Day12_1) {

    std::string line;
    std::size_t sum = 0;
    std::vector<std::vector<int>> matrix;

    while(getline(cin,line)) {
        std::vector<int> row;
        for (auto ch : line) {
            // cout << ch << " = " << (int) ch << endl;;
            cout << ch;
            row.push_back((int) ch);
        }
        cout << endl;
        matrix.push_back(row);
    }

    std::set<std::pair<int,int>> visited;


    std::vector<std::set<std::pair<int, int>>> regions_list;

    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix[0].size(); j++) {
            if (visited.find({i,j}) == visited.end()) {
                // cout << "Region search start for " << (char) matrix[i][j] << " in " << i << " " << j << endl;
                std::set<std::pair<int, int>> region_set;
                region_set.insert({i,j});
                find_region({i,j}, region_set, matrix);

                visited.insert(region_set.begin(), region_set.end());
                regions_list.push_back(region_set);
                auto area = region_set.size();
                auto perimeter = compute_perimeter(region_set, matrix);
                cout << "Region search finish " <<  (char) matrix[i][j] << "  size of region:" << region_set.size() << " perimetr "<<perimeter << endl;
                sum += area*perimeter;
            }
        }
    }

    cout << "Number of regions " <<  regions_list.size() << endl;

    return std::to_string(sum);
}

std::size_t compute_edges( std::set<std::pair<int, int>>& region_set, std::vector<std::vector<int>>& matrix) {
    std::size_t perimeter = 0;
    auto size_i = matrix.size();
    auto size_j = matrix[0].size();

    std::vector<std::pair<int,int>> neigh_deltas =  {{1,0},{-1,0},{0,1},{0,-1}};
    for (auto& current : region_set) {
        for (int i = 0; i<neigh_deltas.size(); i++) {

            auto new_i = neigh_deltas[i].first+current.first;
            auto new_j = neigh_deltas[i].second+current.second;
            if (new_i<0 || new_i >= size_i || new_j<0 || new_j >= size_j || matrix[new_i][new_j] != matrix[current.first][current.second]) {
                perimeter++;
            }
        }
    }
    return perimeter;
}
AOC_DAY(Day12_2){
    std::string line;
    std::size_t sum = 0;
    std::vector<std::vector<int>> matrix;

    while(getline(cin,line)) {
        std::vector<int> row;
        for (auto ch : line) {
            // cout << ch << " = " << (int) ch << endl;;
            cout << ch;
            row.push_back((int) ch);
        }
        cout << endl;
        matrix.push_back(row);
    }

    std::set<std::pair<int,int>> visited;


    std::vector<std::set<std::pair<int, int>>> regions_list;

    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix[0].size(); j++) {
            if (visited.find({i,j}) == visited.end()) {
                // cout << "Region search start for " << (char) matrix[i][j] << " in " << i << " " << j << endl;
                std::set<std::pair<int, int>> region_set;
                region_set.insert({i,j});
                find_region({i,j}, region_set, matrix);

                visited.insert(region_set.begin(), region_set.end());
                regions_list.push_back(region_set);
                auto area = region_set.size();
                auto perimeter = compute_edges(region_set, matrix);
                cout << "Region search finish " <<  (char) matrix[i][j] << "  size of region:" << region_set.size() << " perimetr "<<perimeter << endl;
                sum += area*perimeter;
            }
        }
    }

    cout << "Number of regions " <<  regions_list.size() << endl;

    return std::to_string(sum);
}
