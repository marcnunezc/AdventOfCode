std::vector<std::pair<size_t,size_t>> possible_moves = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0},
};

std::vector<std::pair<std::size_t, std::size_t>> find_neighbours(std::pair<size_t,size_t>& current, std::pair<size_t,size_t>& end, std::set<std::pair<size_t,size_t>>& visited, std::set<std::pair<size_t,size_t>>& walls, size_t max_i, size_t max_j)
{
    std::size_t i=current.first;
    std::size_t j=current.second;

    std::vector<std::pair<size_t,size_t>> neighbours;
    for (auto move : possible_moves) {
        int new_i = i+move.first;
        int new_j = j+move.second;
        if (new_i < 0 ||new_j < 0 || new_i >= max_i || new_j >= max_j)
            continue;
        std::pair<size_t,size_t> new_neighbour({new_i, new_j});
        if (visited.find(new_neighbour) == visited.end() && walls.find(new_neighbour) == walls.end()) {
            neighbours.push_back(new_neighbour);
        }
    }
    return neighbours;
}

size_t solveDay20(size_t max_steps) {
    std::string line;
    std::size_t sum = 0;
    std::pair<size_t,size_t> current;
    std::map<std::tuple<size_t,size_t>, std::size_t> distance_map;
    std::pair<size_t,size_t> end;
    std::set<std::pair<size_t,size_t>> walls;
    std::size_t i = 0;
    size_t max_i, max_j;
    while (getline(cin,line)) {
        max_j = line.size();
        for (std::size_t j = 0; j<line.size(); j++) {
            if (line[j] == '#')
                walls.insert({i,j});
            else if (line[j]=='S')
                current = std::pair<size_t,size_t>({i,j});
            else if (line[j]=='E')
                end = std::pair<size_t,size_t>({i,j});
        }
        i++;
    }
    max_i = i;
    std::pair<size_t,size_t> start=current;
    distance_map[current] = 0;

    std::set<std::pair<size_t,size_t>> visited;
    std::vector<std::pair<size_t, size_t>> path;

    path.push_back(current);
    while (current.first != end.first || current.second != end.second) {
            visited.insert(current);
            auto neighbours = find_neighbours(current, end, visited, walls, max_i, max_j);

            for (auto neighbour : neighbours) {
                distance_map[neighbour] = distance_map[current]+1;
            }
            current = neighbours[0];
            path.push_back(current);
    }
    visited.insert(current);

    for (int i_node = 0; i_node<path.size(); i_node++) {
        auto node = path[i_node];
        for (int j_node = 0; j_node<path.size(); j_node++) {
            auto cheat_end = path[j_node];
            int x1 = node.first;
            int y1 = node.second;
            int x2 = cheat_end.first;
            int y2 = cheat_end.second;
            auto distance = std::abs(x1-x2) + std::abs(y1-y2);

            if (distance <= max_steps) {
                auto diff = j_node-i_node-distance;
                if (diff >= 100)
                    sum++;
            }
        }
    }
    return sum;
}

AOC_DAY(Day20_1) {
    return std::to_string(solveDay20(2));
}

AOC_DAY(Day20_2) {
    return std::to_string(solveDay20(20));
}
