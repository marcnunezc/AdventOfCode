bool disable_drawing = true;

std::vector<pair<int,int>> shape_one = {
    // #### //
    {2,0}, //left
    {3,0},
    {4,0},
    {5,0}, //right
};


std::vector<pair<int,int>> shape_two = {
    // ·#· //
    // ### //
    // ·#· //
    {3,2},  //top
    {3,1}, //center
    {3,0}, //bottom
    {2,1}, //left
    {4,1}, //right
};

std::vector<pair<int,int>> shape_three = {
    // ··# //
    // ··# //
    // ### //
    {4,2},  //top
    {4,1},
    {4,0}, //bottom right
    {3,0},
    {2,0}, //bottom left
};

std::vector<pair<int,int>> shape_four = {
    // # //
    // # //
    // # //
    // # //
    {2,3},   //top
    {2,2},
    {2,1},
    {2,0},  //bottom
};

std::vector<pair<int,int>> shape_five = {
    // ## //
    // ## //
    {2,1},   //top
    {3,1},   //top
    {2,0},  //bottom
    {3,0},  //bottom
};

std::vector<std::vector<pair<int,int>>> shape_vector = {
    shape_one,
    shape_two,
    shape_three,
    shape_four,
    shape_five
};

int get_start_height(std::unordered_set<pair<int,int>, pair_hash>& solid_rock_map) {

    if (solid_rock_map.size() == 0)
        return 0;

    return std::max_element(solid_rock_map.begin(), solid_rock_map.end(),
            [] (auto l, auto r) {
                return l.second < r.second;
            })->second + 1;
}

bool is_collision(std::vector<pair<int,int>>& shape, std::unordered_set<pair<int,int>, pair_hash>& solid_rock_map) {
    for (auto& coords : shape) {
        if (coords.second == 0)
            return true;
        auto coords_to_check = coords;
        coords_to_check.second -= 1;
        if (solid_rock_map.find(coords_to_check) != solid_rock_map.end())
            return true;
    }

    return false;
}

bool is_wall(std::vector<pair<int,int>>& shape, std::unordered_set<pair<int,int>, pair_hash>& solid_rock_map, int increment) {
    int coord_to_check = increment == 1 ? 6 : 0;
    for (auto& coords : shape) {
        if (coords.first == coord_to_check)
            return true;
        auto coords_to_check = coords;
        coords_to_check.first += increment;
        if (solid_rock_map.find(coords_to_check) != solid_rock_map.end())
                return true;
    }

    return false;
}

void draw(std::unordered_set<pair<int,int>, pair_hash>& solid_rock_map, std::vector<pair<int,int>>& shape) {
    if (disable_drawing)
        return;
    int max_j = std::max_element(shape.begin(), shape.end(),
            [] (auto l, auto r) {
                return l.second < r.second;
            })->second;

    for (int j=max_j; j>=0; j--) {
        cout << "|" ;

        for (int i = 0; i<7; i++) {
            pair <int,int> current = {i,j};
            bool rock_found = solid_rock_map.find(current) != solid_rock_map.end();
            bool shape_found = find(shape.begin(), shape.end(), current) != shape.end();
            if (rock_found)
                cout << "#";
            else if (shape_found)
                cout << "@";
            else
                cout << "·";
        }
        cout << "|" << endl;
    }

    cout <<"+-------+" << endl;
    cout << endl;

}


void do_loop(std::unordered_set<pair<int,int>, pair_hash>& solid_rock_map, std::vector<std::vector<pair<int,int>>>& shape_vector, std::string& jet, int& i, int& j) {
        // spawn
        int start_j = get_start_height(solid_rock_map);
        auto shape = shape_vector[i % shape_vector.size()];

        // move to top
        for (auto& coords : shape) {
            coords.second += start_j + 3;
        }

        draw(solid_rock_map, shape);

        auto jet_dir = jet[j++ % jet.size()];
        int increment = jet_dir == '>' ? 1 : -1;
        std::string word = jet_dir == '>' ? "right" : "left";

        if (!is_wall(shape, solid_rock_map, increment)) {
            for (auto& coords : shape) {
                coords.first += increment;
            }
        }

        while (!is_collision(shape, solid_rock_map)) {
            draw(solid_rock_map, shape);
            for (auto& coords : shape) {
                coords.second -= 1;
            }

            draw(solid_rock_map, shape);
            auto jet_dir = jet[j++ % jet.size()];
            int increment = jet_dir == '>' ? 1 : -1;
            std::string word = jet_dir == '>' ? "right" : "left";

            if (!is_wall(shape, solid_rock_map, increment)) {
                for (auto& coords : shape) {
                    coords.first += increment;
                }
            }
        }

        draw(solid_rock_map, shape);
        for (auto& coords : shape) {
            solid_rock_map.insert(coords);
        }
        draw(solid_rock_map, shape);
}

AOC_DAY(Day17_1) {

    std::string jet;
    getline(cin, jet);

    std::unordered_set<pair<int,int>, pair_hash> solid_rock_map;
    int j = 0;
    for (int i=0; i<2022; i++) {
        do_loop(solid_rock_map, shape_vector, jet,  i, j);
    }

    return std::to_string(get_start_height(solid_rock_map));
}


AOC_DAY(Day17_2) {
    std::string jet;
    getline(cin, jet);

    std::unordered_set<pair<int,int>, pair_hash> solid_rock_map;
    int j = 0;
    int previous = 0;
    int check_length=4;
    int base_check=1000;
    int check_every=100;

    // run first "base_check" to ensure is stable
    for (int i=0; i<base_check; i++) {

        if (i % check_every == 0) {
            int current = get_start_height(solid_rock_map);

            previous = current;
        }

        do_loop(solid_rock_map, shape_vector, jet,  i, j);

    }
    int base_j = get_start_height(solid_rock_map);
    auto base_state_rock_map = solid_rock_map;
    auto base_j_copy=j;

    int k = 0;
    std::vector<int> key_heights(check_length,0);
    for (int i=base_check; i<(base_check+check_every*check_length); i++) {
         if (i % check_every == 0) {
            int current = get_start_height(solid_rock_map);
            key_heights[k++]=current-previous;
            previous = current;
        }
        do_loop(solid_rock_map, shape_vector, jet,  i, j);

    }


    std::vector<int> to_check(check_length,0);
    k=0;
    for (int i=(base_check+check_every*check_length); i<base_check+check_every*check_length*2; i++) {
         if (i % check_every == 0) {
            int current = get_start_height(solid_rock_map);
            to_check[k++]=current-previous;
            previous = current;
        }
        do_loop(solid_rock_map, shape_vector, jet,  i, j);

    }
    auto are_equal = [](std::vector<int> a, std::vector<int> b) {
        for (int i=0; i<a.size(); i++) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    };

    int steps = check_length*2;
    int i = base_check+check_every*8;
    std::vector<int> summatory;
    summatory.insert(summatory.end(), key_heights.begin(), key_heights.end());
    summatory.insert(summatory.end(), to_check.begin(), to_check.end());
    bool found = are_equal(key_heights, to_check);
    while(!found) {

        if (i % check_every == 0) {
            int current = get_start_height(solid_rock_map);
            for (int j = 0; j < check_length-1; j++) {
                to_check[j] = to_check[j+1];
            }

            to_check[check_length-1]=current-previous;
            summatory.push_back(current-previous);
            previous = current;
            steps++;
            found = are_equal(key_heights, to_check);
        }
        do_loop(solid_rock_map, shape_vector, jet,  i, j);
        i++;
    }

    long int test = 1000000000000;
    long int factor = (test-base_check)/check_every/(steps-check_length) ;
    long int sum = std::accumulate(summatory.begin(), summatory.end()-check_length, 0);
    long int result = base_j+factor*std::accumulate(summatory.begin(), summatory.end()-check_length, 0);
    long int loops_per_step = (check_every*(steps-check_length));
    long int actual_steps = base_check + factor*loops_per_step;
    int remaining_steps =  (test-actual_steps);
    previous=base_j;
    for (int i=base_check; i<base_check+remaining_steps; i++) {
        do_loop(base_state_rock_map, shape_vector, jet,  i, base_j_copy);
    }
    int final_height = get_start_height(base_state_rock_map);

    result += final_height-base_j;
    return std::to_string(result);
}