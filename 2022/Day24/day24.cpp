void advance_blizzards(std::vector<char>& blizzard_vector, std::vector<std::pair<int,int>>& coord_vector, int max_i, int max_j) {
    for (int i = 0; i<coord_vector.size(); i++) {
        if (blizzard_vector[i]=='<') {
            coord_vector[i].second--;
            if (coord_vector[i].second == 0)
                coord_vector[i].second = max_j-1;
        }
        else if (blizzard_vector[i]=='>') {
            coord_vector[i].second++;
            if (coord_vector[i].second == max_j)
                coord_vector[i].second = 1;
        }
        else if (blizzard_vector[i]=='^') {
            coord_vector[i].first--;
            if (coord_vector[i].first == 0)
                coord_vector[i].first = max_i-1;
        }
        else {
            coord_vector[i].first++;
            if (coord_vector[i].first == max_i)
                coord_vector[i].first = 1;
        }
    }
}

std::vector<std::pair<int,int>> neighbours_delta = {
    {0,0},
    {0,1},
    {0,-1},
    {1,0},
    {-1,0}
};

AOC_DAY(Day24_1) {

    std::string line;
    std::vector<std::pair<int,int>> start_end;
    std::vector<char> blizzard_vector;
    std::vector<std::pair<int,int>> coord_vector;
    std::unordered_set<std::pair<int,int>, pair_hash> coord_set;
    int i=0, id=0;
    int max_j, max_i;
    while(getline(cin, line)) {
        if (count(line.begin(), line.end(), '#') > 2) {
            int j = line.find(".");
            start_end.push_back({i,j});
            max_j = line.size()-1;
        }
        else {
            for (int j=0; j<line.size(); j++) {
                if (line[j] != '#' && line[j] != '.') {
                    blizzard_vector.push_back(line[j]);
                    coord_vector.push_back({i,j});
                }
            }
        }
        i++;
    }
    max_i = i-1;

    int minutes = 0;
    std::deque<std::pair<std::pair<int,int>, int>> queue;
    queue.push_back({start_end[0],0});
    int previous_distance = 0;
    advance_blizzards(blizzard_vector, coord_vector, max_i, max_j);

    while (queue.size() > 0) {
        auto current = queue.front().first;
        auto current_distance = queue.front().second;

        if (current == start_end[1])
            break;
        queue.pop_front();

        if (previous_distance < current_distance) {
            advance_blizzards(blizzard_vector, coord_vector, max_i, max_j);
            previous_distance = current_distance;

            coord_set.clear();
            for (auto coord : coord_vector) {
                coord_set.insert(coord);
            }
        }
        for (auto neigh_delta : neighbours_delta) {
            int new_i = current.first + neigh_delta.first;
            int new_j = current.second + neigh_delta.second;
            std::pair<int,int> new_pos = {new_i, new_j};
            std::pair<std::pair<int,int>, int> new_pair = {new_pos, current_distance+1};

            if (new_pos == start_end[1] || (new_i > 0 && new_j > 0 && new_i < max_i && new_j < max_j && coord_set.find({new_i, new_j}) == coord_set.end()) && find(queue.begin(), queue.end(), new_pair) == queue.end()) {
                queue.push_back(new_pair);
            }
        }
    }

    return std::to_string(queue.front().second);
}

AOC_DAY(Day24_2) {

    std::string line;
    std::vector<std::pair<int,int>> start_end;
    std::vector<char> blizzard_vector;
    std::vector<std::pair<int,int>> coord_vector;
    std::unordered_set<std::pair<int,int>, pair_hash> coord_set;
    int i=0, id=0;
    int max_j, max_i;
    while(getline(cin, line)) {
        if (count(line.begin(), line.end(), '#') > 2) {
            int j = line.find(".");
            start_end.push_back({i,j});
            max_j = line.size()-1;
        }
        else {
            for (int j=0; j<line.size(); j++) {
                if (line[j] != '#' && line[j] != '.') {
                    blizzard_vector.push_back(line[j]);
                    coord_vector.push_back({i,j});
                }
            }
        }
        i++;
    }
    max_i = i-1;

    int minutes = 0;
    std::deque<std::pair<std::pair<int,int>, int>> queue;
    queue.push_back({start_end[0],0});
    int previous_distance = 0;
    advance_blizzards(blizzard_vector, coord_vector, max_i, max_j);
    bool back = false, forth = false;

    while (queue.size() > 0) {
        auto current = queue.front().first;
        auto current_distance = queue.front().second;

        queue.pop_front();
        if (current == start_end[1]) {
            if (!back) {
                back = true;
                auto aux = start_end[0];
                start_end[0] = start_end[1];
                start_end[1] = aux;
                queue.clear();
            } else if (!forth) {
                forth = true;
                auto aux = start_end[1];
                start_end[1] = start_end[0];
                start_end[0] = aux;
                queue.clear();
            }
            else
                break;
        }

        if (previous_distance < current_distance) {
            advance_blizzards(blizzard_vector, coord_vector, max_i, max_j);
            previous_distance = current_distance;

            coord_set.clear();
            for (auto coord : coord_vector) {
                coord_set.insert(coord);
            }
        }
        for (auto neigh_delta : neighbours_delta) {
            int new_i = current.first + neigh_delta.first;
            int new_j = current.second + neigh_delta.second;
            std::pair<int,int> new_pos = {new_i, new_j};
            std::pair<std::pair<int,int>, int> new_pair = {new_pos, current_distance+1};

            if (new_pos == start_end[0] || new_pos == start_end[1] || (new_i > 0 && new_j > 0 && new_i < max_i && new_j < max_j && coord_set.find({new_i, new_j}) == coord_set.end()) && find(queue.begin(), queue.end(), new_pair) == queue.end()) {
                queue.push_back(new_pair);
            }
        }

    }

    return std::to_string(queue.front().second);
}