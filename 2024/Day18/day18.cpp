std::vector<std::pair<std::size_t, std::size_t>> get_neighbours(std::pair<size_t,size_t>& current, std::pair<size_t,size_t>& end, std::set<std::pair<size_t,size_t>>& visited, std::set<std::pair<size_t,size_t>>& walls)
{
    std::size_t i=current.first;
    std::size_t j=current.second;
    std::vector<std::pair<size_t,size_t>> move_list = {
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
    };

    std::vector<std::pair<size_t,size_t>> neighbours;
    for (auto move : move_list) {
        auto new_i = i+move.first;
        auto new_j = j+move.second;
        if (new_i < 0 || new_i > end.first || new_j < 0 || new_j > end.second)
            continue;
        std::pair<size_t,size_t> new_neighbour({new_i, new_j});
        if (visited.find(new_neighbour) == visited.end() && walls.find(new_neighbour) == walls.end()) {
            neighbours.push_back(new_neighbour);
        }
    }
    return neighbours;
}

AOC_DAY(Day18_1) {
    std::string line;
    std::size_t sum = 0;
    std::set<std::pair<size_t,size_t>> bytes;
    std::map<std::pair<size_t,size_t>, std::size_t> distance_map;
    size_t count = 0;
    while (getline(cin,line) && count<1024)
    {
        size_t i,j;
        sscanf(line.c_str(), "%ld,%ld", &i, &j);
        bytes.insert({i,j});
        count++;
    }

    std::pair<size_t,size_t> start({0,0});
    std::pair<size_t,size_t> current = start;;
    std::pair<size_t,size_t> end;

    if (bytes.size() > 50) {
        end = {70,70};
    } else {
        end = {6,6};
    }
    std::set<std::pair<size_t,size_t>> all_neighbours;
    std::set<std::pair<size_t,size_t>> visited;
    distance_map[current] = 0;

    while (current.first != end.first || current.second != end.second) {
            visited.insert(current);
            auto neighbours = get_neighbours(current, end, visited, bytes);

            for (auto neighbour : neighbours) {
                distance_map[neighbour] = distance_map[current]+1;
            }
            all_neighbours.insert(neighbours.begin(), neighbours.end());

            current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
            all_neighbours.erase(current);
    }



    return std::to_string(distance_map[current]);
}


void find_path(std::pair<size_t,size_t>& current, std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>>& parent_map , std::pair<size_t,size_t> start, std::set<std::pair<size_t,size_t>> & visited_points) {
    visited_points.insert({current.first, current.second});
    if (current.first == start.first && current.second == start.second)
        return;
    find_path(parent_map[current], parent_map, start, visited_points);
}


AOC_DAY(Day18_2){
    std::string line;
    std::size_t sum = 0;
    std::vector<std::pair<size_t,size_t>> bytes;
    std::set<std::pair<size_t,size_t>> bytes_set;
    std::map<std::pair<size_t,size_t>, std::size_t> distance_map;
    size_t count = 0;
    while (getline(cin,line))
    {
        size_t i,j;
        sscanf(line.c_str(), "%ld,%ld", &i, &j);
        bytes.push_back({i,j});
        if (count < 1025) {
            bytes_set.insert({i,j});
        }
        count++;
    }

    std::pair<size_t,size_t> start({0,0});
    std::pair<size_t,size_t> current = start;;
    std::pair<size_t,size_t> end;

    if (bytes.size() > 50) {
        end = {70,70};
    } else {
        end = {6,6};
    }
    std::set<std::pair<size_t,size_t>> all_neighbours;
    std::set<std::pair<size_t,size_t>> visited;
    distance_map[current] = 0;

    std::size_t pointer = 1025;
    std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> parent_map;
    std::set<std::pair<size_t,size_t>>  visited_points;

    while(pointer < bytes.size()) {

        if (parent_map.size() > 0 && visited_points.size()==0) {
            find_path(current, parent_map, start, visited_points);
        }

        if (visited_points.size() > 0 && !visited_points.count(bytes[pointer])) {
            bytes_set.insert(bytes[pointer++]);
            continue;
        }

        parent_map.clear();
        visited_points.clear();
        bytes_set.insert(bytes[pointer]);
        visited.clear();
        all_neighbours.clear();
        current = start;
        while (current.first != end.first || current.second != end.second) {
                visited.insert(current);
                auto neighbours = get_neighbours(current, end, visited, bytes_set);

                for (auto neighbour : neighbours) {
                    auto new_distance = distance_map[current]+1;
                    parent_map[neighbour] = current;
                }
                all_neighbours.insert(neighbours.begin(), neighbours.end());

                if (all_neighbours.size() == 0)
                    break;

                current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
                all_neighbours.erase(current);
        }

        if (current.first != end.first || current.second != end.second)
            break;
        pointer++;
    }

    return std::to_string(bytes[pointer].first)+","+std::to_string(bytes[pointer].second);
}