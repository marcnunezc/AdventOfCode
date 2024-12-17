enum DIR {
    E,
    N,
    W,
    S
};

std::map<DIR, std::pair<int,int>> move_list = {
    {DIR::E,{0,1}},
    {DIR::W,{0,-1}},
    {DIR::S,{1,0}},
    {DIR::N,{-1,0}},
};

std::vector<std::tuple<std::size_t, std::size_t, DIR>> get_neighbours(std::tuple<size_t,size_t, DIR>& current, std::set<std::tuple<size_t,size_t, DIR>>& visited, std::set<std::pair<size_t,size_t>>& walls)
{
    std::size_t i=std::get<0>(current);
    std::size_t j=std::get<1>(current);
    DIR current_dir=std::get<2>(current);

    std::map<DIR, std::pair<int,int>> move_list = {
        {DIR::E,{0,1}},
        {DIR::W,{0,-1}},
        {DIR::S,{1,0}},
        {DIR::N,{-1,0}},
    };

    std::vector<std::tuple<size_t,size_t, DIR>> neighbours;
    auto new_i = i+move_list[current_dir].first;
    auto new_j = j+move_list[current_dir].second;
    std::tuple<size_t,size_t, DIR> new_neighbour({new_i, new_j, current_dir});
    if (visited.find(new_neighbour) == visited.end() && walls.find({new_i,new_j}) == walls.end()) {
        neighbours.push_back(new_neighbour);
    }
    for (int k = 1; k<4; k++) {
        DIR new_dir = static_cast<DIR>((current_dir + k) % 4);
        std::tuple<size_t,size_t, DIR> dir_neighbour({i, j, new_dir});
        if (visited.find(dir_neighbour) == visited.end() && k!=2) {
            neighbours.push_back(dir_neighbour);
        }
    }

    return neighbours;
}

AOC_DAY(Day16_1) {
    std::string line;
    std::size_t sum = 0;
    std::tuple<size_t,size_t, DIR> current;
    std::map<std::tuple<size_t,size_t, DIR>, std::size_t> distance_map;
    std::pair<size_t,size_t> end;
    std::set<std::pair<size_t,size_t>> walls;
    std::size_t i = 0;
    while (getline(cin,line)) {
        for (std::size_t j = 0; j<line.size(); j++) {
            if (line[j] == '#')
                walls.insert({i,j});
            else if (line[j]=='S')
                current = std::tuple<size_t,size_t, DIR>({i,j, DIR::E});
            else if (line[j]=='E')
                end = std::pair<int,int>({i,j});
        }
        i++;
    }
    distance_map[current] = 0;
    std::set<std::tuple<size_t,size_t, DIR>> all_neighbours;
    std::set<std::tuple<size_t,size_t, DIR>> visited;

    while (std::get<0>(current) != end.first || std::get<1>(current) != end.second) {
            visited.insert(current);
            auto neighbours = get_neighbours(current, visited, walls);

            for (auto neighbour : neighbours) {
                size_t new_distance;
                if (std::get<2>(current) == std::get<2>(neighbour)) {
                    distance_map[neighbour] = distance_map[current]+1;

                } else {
                    distance_map[neighbour] = distance_map[current]+1000;
                }
            }
            all_neighbours.insert(neighbours.begin(), neighbours.end());

            current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
            all_neighbours.erase(current);
    }

    return std::to_string(distance_map[current]);
}



void find_path(std::tuple<size_t,size_t, DIR>& current, std::map<std::tuple<size_t, size_t, DIR>, std::vector<std::tuple<size_t, size_t, DIR>>>& parent_map , std::tuple<size_t,size_t, DIR> start, std::set<std::tuple<size_t,size_t>> & visited_points) {
    visited_points.insert({std::get<0>(current),std::get<1>(current)});
    if (std::get<0>(current) == std::get<0>(start) && std::get<1>(current) == std::get<1>(start))
        return;
    for (auto prev : parent_map[current]) {
        find_path(prev, parent_map, start, visited_points);
    }
}

AOC_DAY(Day16_2){

    std::string line;
    std::size_t sum = 0;
    std::tuple<size_t,size_t, DIR> current;
    std::tuple<size_t,size_t, DIR> start;
    std::map<std::tuple<size_t,size_t, DIR>, std::size_t> distance_map;
    std::pair<size_t,size_t> end;
    std::set<std::pair<size_t,size_t>> walls;
    std::size_t i = 0;
    std::size_t max_i, max_j;
    while (getline(cin,line)) {
        max_j = line.size();
        for (std::size_t j = 0; j<line.size(); j++) {
            if (line[j] == '#')
                walls.insert({i,j});
            else if (line[j]=='S')
                current = std::tuple<size_t,size_t, DIR>({i,j, DIR::E});
            else if (line[j]=='E')
                end = std::pair<int,int>({i,j});
        }
        i++;
    }
    max_i = i;
    start = current;
    distance_map[current] = 0;
    std::set<std::tuple<size_t,size_t, DIR>> all_neighbours;
    std::set<std::tuple<size_t,size_t, DIR>> visited;
    std::map<std::tuple<size_t, size_t, DIR>, std::vector<std::tuple<size_t, size_t, DIR>>> parent_map;

    size_t min_distance = 1e16;
    while (std::get<0>(current) != end.first || std::get<1>(current) != end.second) {
            visited.insert(current);
            auto neighbours = get_neighbours(current, visited, walls);

            for (auto neighbour : neighbours) {
                size_t new_distance;
                if (std::get<2>(current) == std::get<2>(neighbour)) {
                    new_distance = distance_map[current]+1;

                } else {
                    new_distance = distance_map[current]+1000;
                }
                if (!distance_map.count(neighbour) || new_distance < distance_map[neighbour]) {
                    distance_map[neighbour] = new_distance;
                    parent_map[neighbour] = {current};
                    all_neighbours.insert(neighbour);
                } else if (new_distance == distance_map[neighbour]) {
                    parent_map[neighbour].push_back(current);
                }
            }

            current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
            all_neighbours.erase(current);
    }

    std::set<std::tuple<size_t,size_t>> visited_points;
    find_path(current, parent_map, start, visited_points);

    return std::to_string(visited_points.size());
}