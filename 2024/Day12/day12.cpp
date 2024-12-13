
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
            row.push_back((int) ch);
        }
        matrix.push_back(row);
    }

    std::set<std::pair<int,int>> visited;


    std::vector<std::set<std::pair<int, int>>> regions_list;

    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix[0].size(); j++) {
            if (visited.find({i,j}) == visited.end()) {
                std::set<std::pair<int, int>> region_set;
                region_set.insert({i,j});
                find_region({i,j}, region_set, matrix);

                visited.insert(region_set.begin(), region_set.end());
                regions_list.push_back(region_set);
                auto area = region_set.size();
                auto perimeter = compute_perimeter(region_set, matrix);
                sum += area*perimeter;
            }
        }
    }

    return std::to_string(sum);
}

std::size_t compute_edges( std::set<std::pair<int, int>>& region_set, std::vector<std::vector<int>>& matrix) {
    std::size_t n_edges = 0;
    auto size_i = matrix.size();
    auto size_j = matrix[0].size();

    auto is_value = [&] (const std::pair<int,int> value) {
        return region_set.find(value) != region_set.end();
    };

    auto fill_edges = [&is_value] (bool& current_value_on, std::pair<int,int> pos, int i_ref, std::set<std::pair<int,bool>>& detected_edges) {
        if (current_value_on && (!is_value(pos))) {
            current_value_on = false;
            detected_edges.insert({i_ref, current_value_on});
        } else if(!current_value_on && is_value(pos) ) {
            current_value_on = true;
            detected_edges.insert({i_ref, current_value_on});
        } 
    };

    auto add_non_repeated_edges= [](size_t& n_edges, std::set<std::pair<int,bool>>& detected_edges, std::set<std::pair<int,bool>>& previous_edges) {
        for (auto edge : detected_edges) {
            if (previous_edges.find(edge) == previous_edges.end()) {
                n_edges++;
            }
        }
    };


    std::set<std::pair<int,bool>> previous_edges;
    for (int i = 0; i<matrix.size()+1; i++) {
        bool current_value_on = false;
        std::set<std::pair<int,bool>> detected_edges;
        for (int j = 0; j<matrix[0].size()+1; j++) {
            fill_edges(current_value_on, {i,j}, j, detected_edges);
        }
        add_non_repeated_edges(n_edges, detected_edges, previous_edges);
        previous_edges = detected_edges;
    }
    previous_edges.clear();
    
    for (int j = 0; j<matrix[0].size()+1; j++) {
        bool current_value_on = false;
        std::set<std::pair<int,bool>> detected_edges;
        for (int i = 0; i<matrix.size()+1; i++) {

            fill_edges(current_value_on, {i,j}, i , detected_edges);

        }
        add_non_repeated_edges(n_edges, detected_edges, previous_edges);
        previous_edges = detected_edges;
    }
    return n_edges;
}


AOC_DAY(Day12_2){
    std::string line;
    std::size_t sum = 0;
    std::vector<std::vector<int>> matrix;

    while(getline(cin,line)) {
        std::vector<int> row;
        for (auto ch : line) {
            row.push_back((int) ch);
        }
        matrix.push_back(row);
    }

    std::set<std::pair<int,int>> visited;


    std::vector<std::set<std::pair<int, int>>> regions_list;

    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix[0].size(); j++) {
            if (visited.find({i,j}) == visited.end()) {
                std::set<std::pair<int, int>> region_set;
                region_set.insert({i,j});
                find_region({i,j}, region_set, matrix);

                visited.insert(region_set.begin(), region_set.end());
                regions_list.push_back(region_set);
                auto area = region_set.size();
                auto perimeter = compute_edges(region_set, matrix);
                sum += area*perimeter;
            }
        }
    }

    return std::to_string(sum);
}
