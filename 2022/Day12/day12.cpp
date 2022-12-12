std::vector<std::pair<int,int>> get_neighbours(std::pair<int,int>& current, std::vector<std::string>& matrix, std::set<std::pair<int,int>>& visited)
{
    int i=current.first;
    int j=current.second;
    int size_i = matrix.size();
    int size_j = matrix[0].length();

    std::vector<std::pair<int,int>> neighbour_list = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1},
    };

    std::vector<std::pair<int,int>> neighbours;
    char current_elevation = matrix[i][j]=='S' ? 'a' : matrix[i][j];
    for (auto [neigh_i, neigh_j] : neighbour_list) {
        if (neigh_i+i<0 || neigh_i+i >= size_i)
            continue;
        if (neigh_j+j<0 || neigh_j+j >= size_j)
            continue;
        // cout << "Neigh candidate: " << neigh_i +i<< " " << neigh_j +j<< endl;
        std::pair<int,int> new_pair = {neigh_i+i, neigh_j+j};
        if (visited.find(new_pair)==visited.end()) {
            char neigh_elevation = matrix[neigh_i+i][neigh_j+j]=='E' ? 'z' : matrix[neigh_i+i][neigh_j+j];
        // cout << "elevation diff : " <<neigh_elevation - current_elevation<< endl;
            if ((neigh_elevation - current_elevation) < 2)
                neighbours.push_back(new_pair);
        }
    }
    return neighbours;

}
AOC_DAY(Day12_1) {

    std::vector<std::string> matrix;
    std::string line;
    std::set<std::pair<int,int>> visited;
    std::pair<int,int> start ;
    int i=0;
    while(getline(cin, line)) {
        int j = line.find('S');
        if (j != string::npos)
            start={i,j};
        i++;
        matrix.push_back(line);
    }

    std::map<std::pair<int,int>, int> distance_map;
    distance_map[start] = 0;
    std::pair<int, int> current = start;
    std::set<std::pair<int,int>> all_neighbours;
    while(matrix[current.first][current.second] != 'E') {
        visited.insert(current);
        int current_distance = distance_map[current];
        auto neighbours = get_neighbours(current, matrix, visited);
        for (auto neigh: neighbours) {
            distance_map[neigh] = current_distance+1;
        }
        all_neighbours.insert(neighbours.begin(), neighbours.end());

        current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
        all_neighbours.erase(current);
    }

    return std::to_string(distance_map[current]);
}

AOC_DAY(Day12_2) {


    std::vector<std::string> matrix;
    std::string line;
    int i=0;
    while(getline(cin, line)) {
        int j = line.find('S');
        if (j != string::npos)
            line[j] = 'a';
        matrix.push_back(line);
    }

    int min_distance = 1e6;
    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix[0].length(); j++) {
            std::pair<int,int> start = {i,j};
            if (matrix[i][j] != 'a')
                continue;
            std::map<std::pair<int,int>, int> distance_map;
            distance_map[start] = 0;
            std::pair<int, int> current = start;
            std::set<std::pair<int,int>> visited;
            std::set<std::pair<int,int>> all_neighbours;
            while(matrix[current.first][current.second] != 'E') {
                visited.insert(current);
                int current_distance = distance_map[current];
                auto neighbours = get_neighbours(current, matrix, visited);
                for (auto neigh: neighbours) {
                    distance_map[neigh] = current_distance+1;
                }
                all_neighbours.insert(neighbours.begin(), neighbours.end());

                current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
                all_neighbours.erase(current);
            }

            if (distance_map[current]<min_distance)
                min_distance=distance_map[current];
        }
    }

    return std::to_string(min_distance);
}
