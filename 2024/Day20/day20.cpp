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
        // cout << "new_i " << new_i << " new_j " << new_j <<" and current " << i << " " << j << endl;
        if (new_i < 0 ||new_j < 0 || new_i >= max_i || new_j >= max_j)
            continue;
        std::pair<size_t,size_t> new_neighbour({new_i, new_j});
        if (visited.find(new_neighbour) == visited.end() && walls.find(new_neighbour) == walls.end()) {
            neighbours.push_back(new_neighbour);
        }
    }
    return neighbours;
}

void find_walls_in_path(std::pair<size_t,size_t>& current, std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>>& parent_map , std::pair<size_t,size_t> start, std::set<std::pair<size_t,size_t>> & walls, std::set<std::pair<size_t,size_t>> & visited_walls) {
    for (auto move : possible_moves) {
        auto new_i = current.first+move.first;
        auto new_j = current.second+move.second;
        if (walls.find({new_i,new_j}) != walls.end()) {
            // cout << "found wall at " << new_i << " " << new_j << endl;
            visited_walls.insert({new_i, new_j});
        }
    }
    if (current.first == start.first && current.second == start.second)
        return;
    find_walls_in_path(parent_map[current], parent_map, start, walls, visited_walls);
}

AOC_DAY(Day20_1) {
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

    std::set<std::pair<size_t,size_t>> all_neighbours;
    std::set<std::pair<size_t,size_t>> visited;
    std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> parent_map;
    std::vector<std::pair<size_t, size_t>> path;

    path.push_back(current);
    while (current.first != end.first || current.second != end.second) {
            visited.insert(current);
            auto neighbours = find_neighbours(current, end, visited, walls, max_i, max_j);

            for (auto neighbour : neighbours) {
                distance_map[neighbour] = distance_map[current]+1;
            }
            current = neighbours[0];
            // all_neighbours.insert(neighbours.begin(), neighbours.end());

            // current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
            // all_neighbours.erase(current);
            path.push_back(current);
    }
    visited.insert(current);
    cout << "number of visited nodes " << visited.size() -1 << endl;
    cout << "number of nodes in path " << path.size() -1<< endl;
    cout << "Final distance is " << distance_map[current] << endl;
    std::map<size_t,size_t> count_map;

    int steps = 2;

    for (int i_node = 0; i_node<path.size(); i_node++) {
        auto node = path[i_node];
        // cout << node.first << " " << node.second << endl;
        for (auto move : possible_moves) {
            auto i = node.first+move.first;
            auto j = node.second+move.second;
            std::pair<size_t,size_t> neighbour({i, j});
            if (walls.find(neighbour) != walls.end()) {
                // cout << "wall at " << i << " " << j << endl;
                int i_step = 1;
                while (i_step < steps) {
                    for (auto move : possible_moves) {
                        auto new_i = neighbour.first+move.first;
                        auto new_j = neighbour.second+move.second;
                        std::pair<size_t,size_t> neighbour_wall({new_i, new_j});
                        if (visited.find(neighbour_wall) != visited.end()) {
                            // cout << "found path again at " << new_i << " " << new_j << endl;
                            // get index number of neighbour wall in path
                            auto index = std::find(path.begin(), path.end(), neighbour_wall) - path.begin();
                            auto diff = index-i_node-steps;
                            if (diff > 0) {

                                if (count_map.find(diff) == count_map.end())
                                    count_map[diff] = 1;
                                else
                                    count_map[diff]++;
                            }
                            if (diff >= 100)
                                sum++;
                            if (diff == 66) {
                                cout << "diff is " << diff << endl;
                                cout << "wall at " << i << " " << j << endl;
                                cout << "found path again at " << new_i << " " << new_j << endl;
                                cout << "first index is " << i_node << " second index is " << index << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    for (auto [key, value] : count_map) {
        cout << "saved seconds " << key << " happened this many times: " << value << endl;
    }
    // std::size_t start_distance = distance_map[current];
    // std::set<std::pair<size_t,size_t>> visited_walls;
    // find_walls_in_path(current, parent_map, start, walls, visited_walls);
    // cout << "number of visited walls " << visited_walls.size() << endl;
    // std::map<size_t,size_t> count_map;
    // std::size_t count = 0;
    // for (auto wall : visited_walls) {
    //     count++;
    //     auto new_wall_set = walls;
    //     new_wall_set.erase(wall);
    //     // auto second_wall = wall;
    //     // for (auto move : possible_moves) {
    //     //     auto new_i = wall.first+move.first;
    //     //     auto new_j = wall.second+move.second;
    //     //     std::pair<size_t,size_t> neighbour_wall({new_i, new_j});
    //     //     if (new_wall_set.find(neighbour_wall) != new_wall_set.end()) {
    //     //         // new_wall_set.erase(neighbour_wall);
    //     //         second_wall = neighbour_wall;
    //     //         break;
    //     //     } else
    //     //     {
    //     //         continue;
    //     //     }
    //     // }

    //     current = start;
    //     visited.clear();
    //     all_neighbours.clear();
    //     distance_map.clear();
    //     std::size_t new_sum = 0;
    //     while (current.first != end.first || current.second != end.second) {
    //         // cout << "current is " << current.first << " " << current.second << endl;
    //             visited.insert(current);
    //             auto neighbours = find_neighbours(current, end, visited, new_wall_set, max_i, max_j);

    //             for (auto neighbour : neighbours) {
    //                 distance_map[neighbour] = distance_map[current]+1;
    //             }
    //             all_neighbours.insert(neighbours.begin(), neighbours.end());

    //             current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
    //             all_neighbours.erase(current);
    //     }
    //      cout << count << "/" << visited_walls.size() <<  " final distance is " << distance_map[current] << endl;

    //     auto diff = start_distance - distance_map[current];
    //     if (diff >= 100)
    //         sum++;
    //     if (diff > 0) {
    //         // rewrite this using diff:
    //         if (count_map.find(diff) == count_map.end())
    //             count_map[diff] = 1;
    //         else
    //             count_map[diff]++;
    //     }
    // }
    // for (auto [key, value] : count_map) {
    //     cout << "saved seconds " << key << " happened this many times: " << value << endl;
    // }

    return std::to_string(sum);
}

AOC_DAY(Day20_2){
    std::string line;
    std::size_t sum = 0;


    return std::to_string(sum);
}




// AOC_DAY(Day20_1) {
//     std::string line;
//     std::size_t sum = 0;
//     std::pair<size_t,size_t> current;
//     std::map<std::tuple<size_t,size_t>, std::size_t> distance_map;
//     std::pair<size_t,size_t> end;
//     std::set<std::pair<size_t,size_t>> walls;
//     std::size_t i = 0;
//     size_t max_i, max_j;
//     while (getline(cin,line)) {
//         max_j = line.size();
//         for (std::size_t j = 0; j<line.size(); j++) {
//             if (line[j] == '#')
//                 walls.insert({i,j});
//             else if (line[j]=='S')
//                 current = std::pair<size_t,size_t>({i,j});
//             else if (line[j]=='E')
//                 end = std::pair<size_t,size_t>({i,j});
//         }
//         i++;
//     }
//     max_i = i;
//     std::pair<size_t,size_t> start=current;
//     distance_map[current] = 0;

//     std::set<std::pair<size_t,size_t>> all_neighbours;
//     std::set<std::pair<size_t,size_t>> visited;
//     std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> parent_map;
//     std::vector<std::pair<size_t, size_t> path;

//     while (current.first != end.first || current.second != end.second) {
//             visited.insert(current);
//             auto neighbours = find_neighbours(current, end, visited, walls, max_i, max_j);

//             for (auto neighbour : neighbours) {
//                 distance_map[neighbour] = distance_map[current]+1;
//                 parent_map[neighbour] = current;
//             }
//             all_neighbours.insert(neighbours.begin(), neighbours.end());

//             current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
//             all_neighbours.erase(current);
//     }
//     cout << "Final distance is " << distance_map[current] << endl;
//     std::size_t start_distance = distance_map[current];
//     std::set<std::pair<size_t,size_t>> visited_walls;
//     find_walls_in_path(current, parent_map, start, walls, visited_walls);
//     cout << "number of visited walls " << visited_walls.size() << endl;
//     std::map<size_t,size_t> count_map;
//     std::size_t count = 0;
//     for (auto wall : visited_walls) {
//         count++;
//         auto new_wall_set = walls;
//         new_wall_set.erase(wall);
//         // auto second_wall = wall;
//         // for (auto move : possible_moves) {
//         //     auto new_i = wall.first+move.first;
//         //     auto new_j = wall.second+move.second;
//         //     std::pair<size_t,size_t> neighbour_wall({new_i, new_j});
//         //     if (new_wall_set.find(neighbour_wall) != new_wall_set.end()) {
//         //         // new_wall_set.erase(neighbour_wall);
//         //         second_wall = neighbour_wall;
//         //         break;
//         //     } else
//         //     {
//         //         continue;
//         //     }
//         // }

//         current = start;
//         visited.clear();
//         all_neighbours.clear();
//         distance_map.clear();
//         std::size_t new_sum = 0;
//         while (current.first != end.first || current.second != end.second) {
//             // cout << "current is " << current.first << " " << current.second << endl;
//                 visited.insert(current);
//                 auto neighbours = find_neighbours(current, end, visited, new_wall_set, max_i, max_j);

//                 for (auto neighbour : neighbours) {
//                     distance_map[neighbour] = distance_map[current]+1;
//                 }
//                 all_neighbours.insert(neighbours.begin(), neighbours.end());

//                 current = *min_element(all_neighbours.begin(), all_neighbours.end(), [&](const auto& l, const auto& r) { return distance_map[l] < distance_map[r]; });
//                 all_neighbours.erase(current);
//         }
//          cout << count << "/" << visited_walls.size() <<  " final distance is " << distance_map[current] << endl;

//         auto diff = start_distance - distance_map[current];
//         if (diff >= 100)
//             sum++;
//         if (diff > 0) {
//             // rewrite this using diff:
//             if (count_map.find(diff) == count_map.end())
//                 count_map[diff] = 1;
//             else
//                 count_map[diff]++;
//         }
//     }
//     for (auto [key, value] : count_map) {
//         cout << "saved seconds " << key << " happened this many times: " << value << endl;
//     }

//     return std::to_string(sum);
// }