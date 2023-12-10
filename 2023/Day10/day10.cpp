enum DIR {
    NONE,
    NS,
    EW,
    NE,
    NW,
    SW,
    SE,
    G,
    S,
    VOID
};

int read_input(std::array<std::array<DIR, 200>, 200>& pipe_array, std::pair<int, int>& start_point) {
    std::string line;
    int j=0;
    while (getline(cin, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i]=='.')
                pipe_array[i+1][j+1]=DIR::G;
            else if (line[i]=='|')
                pipe_array[i+1][j+1]=DIR::NS;
            else if (line[i]=='L')
                pipe_array[i+1][j+1]=DIR::NE;
            else if (line[i]=='J')
                pipe_array[i+1][j+1]=DIR::NW;
            else if (line[i]=='7')
                pipe_array[i+1][j+1]=DIR::SW;
            else if (line[i]=='F')
                pipe_array[i+1][j+1]=DIR::SE;
            else if (line[i]=='-')
                pipe_array[i+1][j+1]=DIR::EW;
            else if (line[i]=='S') {
                pipe_array[i+1][j+1]=DIR::S;
                start_point = {i+1,j+1};
            } else {
                pipe_array[i+1][j+1]=DIR::NONE;
            }
        }
        j++;
    }
    return line.size();

}
std::vector<std::pair<int,int>> get_starting_neighbours(std::pair<int,int>& current, std::array<std::array<DIR, 200>, 200>& pipe_array, std::unordered_set<std::pair<int,int>, pair_hash>& path_set) {
    std::vector<std::pair<int,int>> neighbour_list;
    path_set.insert(current);
    int i = current.first;
    int j = current.second;
    // connect south pipes
    if (pipe_array[i][j-1] == DIR::NS || pipe_array[i][j-1] == DIR::SW || pipe_array[i][j-1] == DIR::SE) {
        if (path_set.find({i,j-1})==path_set.end())
            neighbour_list.push_back({i, j-1});
    }
    // connect north pipes
    if (pipe_array[i][j+1] == DIR::NS || pipe_array[i][j+1] == DIR::NW || pipe_array[i][j+1] == DIR::NE) {
        if (path_set.find({i,j+1})==path_set.end())
            neighbour_list.push_back({i, j+1});
    }
    // connect east pipes
    if (pipe_array[i-1][j] == DIR::EW || pipe_array[i-1][j] == DIR::SE || pipe_array[i-1][j] == DIR::NE) {
        if (path_set.find({i-1,j})==path_set.end())
            neighbour_list.push_back({i-1, j});
    }
    // connect west pipes
    if (pipe_array[i+1][j] == DIR::EW || pipe_array[i+1][j] == DIR::SW || pipe_array[i+1][j] == DIR::NW) {
        if (path_set.find({i+1,j})==path_set.end())
            neighbour_list.push_back({i+1, j});
    }

    return neighbour_list;
}

std::pair<int,int> get_next(std::pair<int,int>& current, std::array<std::array<DIR, 200>, 200>& pipe_array, std::unordered_set<std::pair<int,int>, pair_hash>& path_set) {
    std::vector<std::pair<int,int>> neighbour_list;
    path_set.insert(current);
    int i = current.first;
    int j = current.second;
    if (pipe_array[i][j] == DIR::NS) {
        // connect south pipes
        if (pipe_array[i][j-1] == DIR::NS|| pipe_array[i][j-1] == DIR::SW || pipe_array[i][j-1] == DIR::SE) {
            if (path_set.find({i,j-1})==path_set.end())
                return std::make_pair(i, j-1);
        }
        // connect north pipes
        if (pipe_array[i][j+1] == DIR::NS || pipe_array[i][j+1] == DIR::NW || pipe_array[i][j+1] == DIR::NE) {
            if (path_set.find({i,j+1})==path_set.end())
                return std::make_pair(i, j+1);
        }
    } else if (pipe_array[i][j] == DIR::NE) {
        // connect south pipes
        if (pipe_array[i][j-1] == DIR::NS|| pipe_array[i][j-1] == DIR::SW || pipe_array[i][j-1] == DIR::SE) {
            if (path_set.find({i,j-1})==path_set.end())
                return std::make_pair(i, j-1);
        }
        // connect west pipes
        if (pipe_array[i+1][j] == DIR::EW || pipe_array[i+1][j] == DIR::SW || pipe_array[i+1][j] == DIR::NW) {
            if (path_set.find({i+1,j})==path_set.end())
                return std::make_pair(i+1, j);
        }
    } else if (pipe_array[i][j] == DIR::NW) {
        // connect south pipes
        if (pipe_array[i][j-1] == DIR::NS|| pipe_array[i][j-1] == DIR::SW || pipe_array[i][j-1] == DIR::SE) {
            if (path_set.find({i,j-1})==path_set.end())
                return std::make_pair(i, j-1);
        }
        // connect east pipes
        if (pipe_array[i-1][j] == DIR::EW || pipe_array[i-1][j] == DIR::SE || pipe_array[i-1][j] == DIR::NE) {
            if (path_set.find({i-1,j})==path_set.end())
                return std::make_pair(i-1, j);
        }
    } else if (pipe_array[i][j] == DIR::SE) {
        // connect north pipes
        if (pipe_array[i][j+1] == DIR::NS || pipe_array[i][j+1] == DIR::NW || pipe_array[i][j+1] == DIR::NE) {
            if (path_set.find({i,j+1})==path_set.end())
                return std::make_pair(i, j+1);
        }
        // connect west pipes
        if (pipe_array[i+1][j] == DIR::EW || pipe_array[i+1][j] == DIR::SW || pipe_array[i+1][j] == DIR::NW) {
            if (path_set.find({i+1,j})==path_set.end())
                return std::make_pair(i+1, j);
        }
    } else if (pipe_array[i][j] == DIR::SW) {
        // connect north pipes
        if (pipe_array[i][j+1] == DIR::NS || pipe_array[i][j+1] == DIR::NW || pipe_array[i][j+1] == DIR::NE) {
            if (path_set.find({i,j+1})==path_set.end())
                return std::make_pair(i, j+1);
        }
        // connect east pipes
        if (pipe_array[i-1][j] == DIR::EW || pipe_array[i-1][j] == DIR::SE || pipe_array[i-1][j] == DIR::NE) {
            if (path_set.find({i-1,j})==path_set.end())
                return std::make_pair(i-1, j);
        }
    } else if (pipe_array[i][j] == DIR::EW) {
        // connect east pipes
        if (pipe_array[i-1][j] == DIR::EW || pipe_array[i-1][j] == DIR::SE || pipe_array[i-1][j] == DIR::NE) {
            if (path_set.find({i-1,j})==path_set.end())
                return std::make_pair(i-1, j);
        }
        // connect west pipes
        if (pipe_array[i+1][j] == DIR::EW || pipe_array[i+1][j] == DIR::SW || pipe_array[i+1][j] == DIR::NW) {
            if (path_set.find({i+1,j})==path_set.end())
                return std::make_pair(i+1, j);
        }
    }
    return std::make_pair(-1,-1);
}

void look_for_neighs(std::pair<int,int> chunk, std::unordered_set<std::pair<int,int>, pair_hash>& chunk_set, std::unordered_set<std::pair<int,int>, pair_hash>& visited_chunks, std::unordered_set<std::pair<int,int>, pair_hash>& path_set, int array_length) {

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
        if (neigh.first > 0 && neigh.second > 0 && neigh.first < array_length+1 && neigh.second < array_length+1) {
            if (path_set.find(neigh) == path_set.end() && visited_chunks.find(neigh) == visited_chunks.end() ){
                look_for_neighs(neigh, chunk_set, visited_chunks, path_set, array_length);
            }
        }
    }
    return;
}

bool raycast_chunk(std::unordered_set<std::pair<int,int>, pair_hash> chunk,  std::unordered_set<std::pair<int,int>, pair_hash>& path_set, std::array<std::array<DIR, 200>, 200>& pipe_array, int array_length) {
    auto pipe = *chunk.begin();

    int crossings = 0;
    bool detected_ne = false;
    bool detected_se = false;
    for (int i=pipe.first+1; i<array_length+1; i++){
        int j = pipe.second;
        if (path_set.find({i,j}) != path_set.end() && pipe_array[i][j] != DIR::EW) {
            if (pipe_array[i][j] == DIR::SE) {
                detected_se = true;
            }
            else if(pipe_array[i][j] == DIR::NE) {
                detected_ne = true;
            }
            else if (pipe_array[i][j] == DIR::SW && detected_se) {
                detected_se = false;
            }
            else if (pipe_array[i][j] == DIR::NW && detected_ne){
                detected_ne = false;
            }
            else {
                detected_ne = false;
                detected_se = false;
                crossings++;
            }
        }
    }

    return crossings % 2 == 1;
}


AOC_DAY(Day10_1){
    std::array<std::array<DIR, 200>, 200> pipe_array = {};
    std::unordered_map<std::pair<int,int>,int, pair_hash> distance_map;
    std::unordered_set<std::pair<int,int>, pair_hash> path_set;
    std::pair<int, int> start_point;
    read_input(pipe_array, start_point);

    auto starting_neighbours = get_starting_neighbours(start_point, pipe_array, path_set);

    for (auto neigh : starting_neighbours) {
        auto& current=neigh;
        int distance = 0;
        path_set.clear();
        path_set.insert(start_point);
        while (current != start_point && (current.first != -1 && current.second != -1)) {
            if (distance_map[current] > 0)
                distance_map[current] = min(++distance, distance_map[current]);
            else
                distance_map[current] = ++distance;

            current = get_next(current, pipe_array, path_set);
        }
    }

    auto max_value = std::max_element(distance_map.begin(), distance_map.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );
    return std::to_string(max_value->second);
}


AOC_DAY(Day10_2) {
    std::size_t sum = 0;
    std::array<std::array<DIR, 200>, 200> pipe_array = {};
    std::unordered_map<std::pair<int,int>,int, pair_hash> distance_map;
    std::unordered_set<std::pair<int,int>, pair_hash> path_set;
    std::pair<int, int> start_point;
    int array_length = read_input(pipe_array, start_point);

    // Find path and store in set
    auto starting_neighbours = get_starting_neighbours(start_point, pipe_array, path_set);
    auto current=starting_neighbours[0];
    int distance = 0;
    while (current != start_point && (current.first != -1 && current.second != -1)) {
        if (distance_map[current] > 0)
            distance_map[current] = min(++distance, distance_map[current]);
        else
            distance_map[current] = ++distance;

        current = get_next(current, pipe_array, path_set);
    }

    // Group pipes in chunks
    std::vector<std::unordered_set<std::pair<int,int>, pair_hash>> chunks_list;
    std::unordered_set<std::pair<int,int>, pair_hash> visited_chunks;
    for (int j = 1; j< array_length+1; j++) {
        for (int i = 1; i< array_length+1; i++) {
            if (path_set.find({i,j}) == path_set.end() && visited_chunks.find({i,j}) == visited_chunks.end()) {
                std::unordered_set<std::pair<int,int>, pair_hash> chunk_set;
                look_for_neighs({i,j}, chunk_set, visited_chunks, path_set, array_length);
                chunks_list.push_back(chunk_set);

            }
        }
    }

    // Ray cast on every chunk
    for (auto& chunk : chunks_list) {
        if (raycast_chunk(chunk, path_set, pipe_array, array_length)) {
            sum+=chunk.size();
        }
    }

    return std::to_string(sum);
}