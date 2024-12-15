
std::map<char, std::pair<int,int>> move_delta = {
                                                {'<', {0,-1}},
                                                {'>', {0,1}},
                                                {'v', {1,0}},
                                                {'^', {-1,0}},
                                                };
AOC_DAY(Day15_1) {
    std::string line;
    std::set<std::pair<int,int>> walls;
    std::set<std::pair<int,int>> balls;
    std::pair<int,int> current;
    std::size_t sum = 0;
    int i = 0;
    int max_j;
    while(getline(cin, line)) {
        if (line.empty())
            break;
        max_j = line.size();
        for (int j = 0; j<line.size(); j++) {
            auto ch = line[j];
            if (ch == '#')
                walls.insert({i,j});
            else if (ch=='O')
                balls.insert({i,j});
            else if (ch == '@')
                current = {i,j};
        }
        i++;
    }
    int max_i = i;

    std::string instructions = "";
    while(getline(cin, line)) {
        instructions += line;
    }
    auto is_pos_in_set = [] (const std::pair<int,int> pos, std::set<std::pair<int,int>>& set_to_check) {
        return set_to_check.find(pos) != set_to_check.end();
    };
    auto print_matrix = [&] () {

        for (int i = 0; i<max_i; i++) {
            for (int j=0; j<max_j; j++) {
                if (walls.find({i,j})!=walls.end())
                    cout << '#';
                else if (balls.find({i,j})!=balls.end())
                    cout << 'O';
                else if (current.first ==i && current.second == j)
                    cout << '@';
                else
                    cout << '.';
            }
            cout << endl;
        }
        cout << endl;
    };
    // print_matrix();

    // cout << instructions <<  endl;


    for (auto ins : instructions) {

        auto delta = move_delta[ins];

        auto check_pos = current;
        int steps = 0;
        while (check_pos == current || is_pos_in_set(check_pos, balls)) {
            check_pos.first += delta.first;
            check_pos.second += delta.second;
            steps++;
        }
        if (walls.find(check_pos) == walls.end()) {
            auto new_pos = check_pos;
            for (int i = 0; i<steps; i++) {
                auto ball_pos = new_pos;
                ball_pos.first -= delta.first;
                ball_pos.second -= delta.second;
                if (is_pos_in_set(ball_pos, balls)) {
                    balls.erase(ball_pos);
                    balls.insert(new_pos);
                }
                new_pos = ball_pos;
            }

            current.first += delta.first;
            current.second += delta.second;
        }

        // print_matrix();

        // break;
    }

    for (auto ball : balls) {
        sum+= 100*ball.first+ball.second;
    }
    return std::to_string(sum);
}

AOC_DAY(Day15_2){

    std::string line;
    std::size_t product = 1;


    return std::to_string(product);
}
