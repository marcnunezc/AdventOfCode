typedef std::unordered_map<std::pair<int,int>, int, pair_hash> UnordMapPairIntType;
typedef std::unordered_map<std::pair<int, char>, std::pair<int,char>, pair_hash> TransformationType;
std::unordered_map<char, char> clockwise_turn = {
    {'n', 'e'},
    {'e', 's'},
    {'s', 'w'},
    {'w', 'n'},
};

std::unordered_map<char, char> counterclockwise_turn = {
    {'n', 'w'},
    {'w', 's'},
    {'s', 'e'},
    {'e', 'n'},
};

char turn(char current, char dir) {
    if (dir == 'R')
        return clockwise_turn[current];
    else
        return counterclockwise_turn[current];
}
bool move(std::pair<int,int>& pos, char dir, UnordMapPairIntType& map)  {
    auto next_pos = pos;
    if (dir == 'n')
        next_pos.second--;
    else if (dir == 's')
        next_pos.second++;
    else if (dir == 'e')
        next_pos.first++;
    else if (dir == 'w')
        next_pos.first--;

    auto is_wall = [&](std::pair<int,int> pos_to_check) {
        if (map[pos_to_check]) // wall
            return false;
        else {
            pos = pos_to_check;
            return true;
        }
    };

    if (map.find(next_pos) == map.end()) {
        //wrap around
        if (dir == 'n') {
            int j=0;
            while (map.find({next_pos.first, j}) == map.end())
                j++;
            while (map.find({next_pos.first, j}) != map.end())
                j++;
            next_pos.second = j-1;
            return is_wall(next_pos);
        }
        else if (dir == 's') {
            int j=0;
            while (map.find({next_pos.first, j}) == map.end())
                j++;
            next_pos.second = j;
            return is_wall(next_pos);
        }
        else if (dir == 'w') {
            int i=0;
            while (map.find({i, next_pos.second}) == map.end())
                i++;
            while (map.find({i, next_pos.second}) != map.end())
                i++;
            next_pos.first = i-1;
            return is_wall(next_pos);
        }
        else if (dir == 'e') {
            int i=0;
            while (map.find({i, next_pos.second}) == map.end())
                i++;
            next_pos.first = i;
            return is_wall(next_pos);
        }
    }
    return is_wall(next_pos);
}

AOC_DAY(Day22_1) {

    UnordMapPairIntType map;
    std::string line;
    std::string instruction;
    int j = 0;
    while(getline(cin, line)) {
        if (line.empty()) {
            getline(cin, instruction);
            break;
        }

        for (int i=0; i<line.size();i++) {
            if (line[i] == '.')
                map[{i,j}] = 0;
            else if (line[i] == '#')
                map[{i,j}] = 1;
        }
        j++;
    }

    std::pair<int,int> pos;
    int i = 0;
    while (++i) {
        if (map.find({i, 0}) != map.end()) {
            pos = {i,0};
            break;
        }
    }

    int head = 0;
    i = 0;
    char current_dir = 'e';
    char next_dir;
    while (head < instruction.size()-1) {
        while(isdigit(instruction[i]) && i < instruction.size())
            i++;
        char next_dir=instruction[i];

        int steps = stoi(instruction.substr(head, i-head));
        for (int step : std::ranges::iota_view{0, steps}) {
            if (!move(pos, current_dir, map))
                break;
        }
        if (i < instruction.size())
            current_dir = turn(current_dir, next_dir);
        head = ++i;
    }
    std::unordered_map<char,int> dir_to_points = {
        {'e', 0},
        {'s', 1},
        {'w', 2},
        {'n', 3},
    };

    return std::to_string(1000*(pos.second+1)+4*(pos.first+1)+dir_to_points[current_dir]);
}


bool move_2(std::pair<int,int>& pos, char& dir, UnordMapPairIntType& map, UnordMapPairIntType& cube_map, TransformationType& transformation, int cube_size)  {
    auto next_pos = pos;
    if (dir == 'n')
        next_pos.second--;
    else if (dir == 's')
        next_pos.second++;
    else if (dir == 'e')
        next_pos.first++;
    else if (dir == 'w')
        next_pos.first--;

    auto is_wall = [&](std::pair<int,int> pos_to_check) {
        if (map[pos_to_check]) // wall
        {
            return false;
        }
        else {
            pos = pos_to_check;
            return true;
        }
    };

    if (map.find(next_pos) == map.end()) {
        auto current_face = cube_map[pos];
        auto new_face = transformation[{current_face, dir}];
        std::pair<int,int> new_face_pos;
        for (auto it = cube_map.begin(); it!=cube_map.end(); it++) {
            if (it->second == new_face.first)
            {
                new_face_pos = it->first;
                break;
            }
        }

        int x_delta = (pos.first % cube_size);
        int y_delta = (pos.second % cube_size);

        if (dir == new_face.second) {
            if (dir == 'n' || dir == 's') {
                next_pos.first = (new_face_pos.first / cube_size)*cube_size +  cube_size - x_delta - 1;
                next_pos.second = (new_face_pos.second / cube_size)*cube_size;
            }
            else {
                next_pos.first = (new_face_pos.first / cube_size)*cube_size;
                next_pos.second = (new_face_pos.second / cube_size)*cube_size +  cube_size - y_delta - 1;
            }
            if (new_face.second == 'e')
                next_pos.first += cube_size-1;
            else if (new_face.second == 's')
                next_pos.second += cube_size-1;
        }
        else if (dir == clockwise_turn[clockwise_turn[new_face.second]]) {
            if (new_face.second == 'e' || new_face.second == 'w' ) {
                next_pos.first = (new_face_pos.first / cube_size)*cube_size;
                next_pos.second = (new_face_pos.second  / cube_size)*cube_size + y_delta;
            }
            else {
                next_pos.first = (new_face_pos.first / cube_size)*cube_size + x_delta;
                next_pos.second = (new_face_pos.second / cube_size)*cube_size;
            }
            if (new_face.second == 'e')
                next_pos.first += cube_size - 1;
            else if (new_face.second == 's')
                next_pos.second += cube_size - 1 ;
        }
        else if (dir == 'w' && new_face.second == 's' || dir == 'e' && new_face.second == 'n') {
            next_pos.first = (new_face_pos.first / cube_size)*cube_size +  cube_size - y_delta -1;
            next_pos.second = (new_face_pos.second  / cube_size)*cube_size;
            if (new_face.second == 's')
                next_pos.second += cube_size-1;
        }
        else if (dir == 's' && new_face.second == 'w' || dir == 'n' && new_face.second == 'e') {
            next_pos.first = (new_face_pos.first / cube_size)*cube_size;
            next_pos.second = (new_face_pos.second  / cube_size)*cube_size + cube_size + x_delta -1;
            if (new_face.second == 'e')
                next_pos.first += cube_size-1;

        }
        else {
            if (new_face.second == 'e' || new_face.second == 'w' ) {
                next_pos.first = (new_face_pos.first / cube_size)*cube_size;
                next_pos.second = (new_face_pos.second  / cube_size)*cube_size + x_delta;
                if (new_face.second == 'e')
                    next_pos.first += cube_size-1;

            }
            else {
                next_pos.first = (new_face_pos.first / cube_size)*cube_size + y_delta;
                next_pos.second = (new_face_pos.second  / cube_size)*cube_size;
                if (new_face.second == 's')
                    next_pos.second += cube_size-1;
            }
        }
        if (!map[next_pos])
            dir = clockwise_turn[clockwise_turn[new_face.second]];
    }
    return is_wall(next_pos);
}

AOC_DAY(Day22_2) {

    UnordMapPairIntType map;
    UnordMapPairIntType cube;
    TransformationType transformation;

    std::string line;
    std::string instruction;
    int j = 0;
    int face = 0;
    int i_face = 0;
    int base_i = -1;
    bool is_test = false;
    int cube_size = 50;
    while(getline(cin, line)) {
        if (line.empty()) {
            getline(cin, instruction);
            break;
        }
        if (line.size() < 50 && !is_test)
            is_test = true;

        for (int i=0; i<line.size();i++) {
            if (line[i] == '.')
                map[{i,j}] = 0;
            else if (line[i] == '#')
                map[{i,j}] = 1;
        }
        j++;
    }
    if (is_test)
        cube_size = 4;

    int j_max = j;
    j = 0;
    while (j<j_max) {
        int i=0;
        while (map.find({i,j}) == map.end())
            i+=cube_size;

        while (map.find({i,j}) != map.end()) {
            face++;
            for (int col=i; col<i+cube_size; col++) {
                for (int row=j; row<j+cube_size; row++) {
                    cube[{col,row}] = face;
                }
            }
            i+=cube_size;
        }
        i=0;
        j+=cube_size;
    }

    j = 0;
    while (j<j_max) {
        int i=0;
        while (map.find({i,j}) == map.end())
            i+=cube_size;

        while (map.find({i,j}) != map.end()) {
            if (map.find({i+cube_size,j}) != map.end()) {
                transformation[{cube[{i,j}], 'e'}] = {cube[{i+cube_size,j}], 'w'};
                transformation[{cube[{i+cube_size,j}], 'w'}] = {cube[{i,j}], 'e'};
            }

            if (map.find({i,j+cube_size}) != map.end()) {
                transformation[{cube[{i,j}], 's'}] = {cube[{i,j+cube_size}], 'n'};
                transformation[{cube[{i,j+cube_size}], 'n'}] = {cube[{i,j}], 's'};
            }
            i+=cube_size;
        }
        i=0;
        j+=cube_size;
    }

    std::vector<char> dirs_vector = {'e', 'w', 'n', 's'};


    // fill all transformation maps (6 cubes * 4 faces)
    while(transformation.size() < 24) {
        // loop all cubes
        for (auto cube_id : std::ranges::iota_view{1, 7}) {
            // loop all dirs
            for (auto cube_dir : dirs_vector) {
                // check {cube_id, cube_dir} pair  does not exist
                if (transformation.find({cube_id, cube_dir}) == transformation.end() ) {
                    // find neighbours of cube_id
                    for (auto [neigh, current] : transformation) {
                        if (current.first == cube_id) {
                            // found neighbour. Check if neighbours contains a cube pointing to cube_dir.
                            for (auto [neigh_new_dir, destination_neigh] : transformation) {
                                bool pair_is_present = false;
                                // check cube_id pair is not present
                                for (auto [test1, test2] : transformation) {
                                    if (test1.first == cube_id && test2.first == destination_neigh.first) {
                                        pair_is_present = true;
                                        break;
                                    }
                                }
                                // avoid repeated pairs, cubes pointing to themselves and opposite faces (n to s, w to e, etc)
                                if (!pair_is_present && neigh.first == neigh_new_dir.first && neigh_new_dir.second == cube_dir && destination_neigh.first != cube_id && neigh_new_dir.second != clockwise_turn[clockwise_turn[neigh.second]]) {
                                    // is the rotation counterclockwise or not
                                    bool is_counterclockwise = clockwise_turn[cube_dir] == neigh.second;

                                    if (is_counterclockwise) {
                                        transformation[{cube_id, cube_dir}] = {destination_neigh.first, counterclockwise_turn[destination_neigh.second]};
                                        transformation[{destination_neigh.first, counterclockwise_turn[destination_neigh.second]}] = {cube_id, cube_dir};
                                    }
                                    else {
                                        transformation[{cube_id, cube_dir}] = {destination_neigh.first, clockwise_turn[destination_neigh.second]};
                                        transformation[{destination_neigh.first, clockwise_turn[destination_neigh.second]}] = {cube_id, cube_dir};
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::pair<int,int> pos;
    int i = 0;
    while (++i) {
        if (map.find({i, 0}) != map.end()) {
            pos = {i,0};
            break;
        }
    }

    int head = 0;
    i = 0;
    char current_dir = 'e';
    char next_turn;

    while (head < instruction.size()) {
        while(isdigit(instruction[i]) && i < instruction.size())
            i++;
        char next_turn=instruction[i];

        int steps = stoi(instruction.substr(head, i-head));
        for (int step : std::ranges::iota_view{0, steps}) {
            if (!move_2(pos, current_dir, map, cube, transformation, cube_size)) {
                break;
            }
        }
        if (i < instruction.size())
            current_dir = turn(current_dir, next_turn);
        head = ++i;
    }
    std::unordered_map<char,int> dir_to_points = {
        {'e', 0},
        {'s', 1},
        {'w', 2},
        {'n', 3},
    };

    return std::to_string(1000*(pos.second+1)+4*(pos.first+1)+dir_to_points[current_dir]);
}