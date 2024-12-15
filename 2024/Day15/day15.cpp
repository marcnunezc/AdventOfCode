
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

bool is_pos_in_set(const std::pair<int,int> pos, const std::set<std::pair<int,int>> set_to_check) {
        return set_to_check.find(pos) != set_to_check.end();
}

bool can_move_vertically(std::pair<int,int> current_pos,int delta, std::set<std::pair<int,int>>& to_move_list, std::set<std::pair<int,int>>& walls,  std::set<std::pair<int,int>>& balls,  std::set<std::pair<int,int>>& balls_closed) {
    auto new_pos = current_pos;
    new_pos.first+=delta;
    if (is_pos_in_set(new_pos, walls))
        return false;
    else if (is_pos_in_set(new_pos, balls) || is_pos_in_set(new_pos, balls_closed)) {
        auto other_pos = new_pos;
        if (is_pos_in_set(new_pos, balls))
            other_pos.second+=1;
        else
            other_pos.second-=1;
        to_move_list.insert(new_pos);
        to_move_list.insert(other_pos);
        if (!can_move_vertically(new_pos, delta, to_move_list, walls, balls, balls_closed))
            return false;
        if (!can_move_vertically(other_pos, delta, to_move_list, walls, balls, balls_closed))
            return false;
    }
    return true;
}


AOC_DAY(Day15_2){

    std::string line;
    std::set<std::pair<int,int>> walls;
    std::set<std::pair<int,int>> balls;
    std::set<std::pair<int,int>> balls_closed;
    std::pair<int,int> current;
    std::size_t sum = 0;
    int i = 0;
    int max_j;
    while(getline(cin, line)) {
        if (line.empty())
            break;
        max_j = line.size()*2;
        int j = 0;
        for (int k = 0; k<line.size(); k++) {
            auto ch = line[k];
            if (ch == '#') {
                walls.insert({i,j++});
                walls.insert({i,j++});
            }
            else if (ch=='O') {
                balls.insert({i,j++});
                balls_closed.insert({i,j++});
            }
            else if (ch == '@') {
                current = {i,j++};
                j++;
            }
            else {
                j += 2;
            }
        }
        i++;
    }
    int max_i = i;

    std::string instructions = "";
    while(getline(cin, line)) {
        instructions += line;
    }

    auto print_matrix = [&] () {

        for (int i = 0; i<max_i; i++) {
            for (int j=0; j<max_j; j++) {
                if (walls.find({i,j})!=walls.end())
                    cout << '#';
                else if (balls.find({i,j})!=balls.end()) {
                    cout << "[";
                }
                else if (balls_closed.find({i,j})!=balls_closed.end()) {
                    cout << "]";
                }
                else if (current.first ==i && current.second == j)
                    cout << '@';
                else
                    cout << '.';
            }
            cout << endl;
        }
        cout << endl;
    };

    for (auto ins : instructions) {
        auto delta = move_delta[ins];

        auto check_pos = current;
        int steps = 0;
        if (ins == '>' || ins == '<') {
            while (check_pos == current || is_pos_in_set(check_pos, balls) || is_pos_in_set(check_pos, balls_closed)) {
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
                        auto closed_pos = ball_pos;
                        closed_pos.second++;
                        balls_closed.erase(closed_pos);
                        closed_pos=new_pos;
                        closed_pos.second++;
                        balls_closed.insert(closed_pos);
                    } else if (is_pos_in_set(ball_pos, balls_closed)) {
                        balls_closed.erase(ball_pos);
                        balls_closed.insert(new_pos);
                        auto open_pos = ball_pos;
                        open_pos.second--;
                        balls.erase(open_pos);
                        open_pos=new_pos;
                        open_pos.second--;
                        balls.insert(open_pos);

                    }
                    new_pos = ball_pos;
                }

                current.first += delta.first;
                current.second += delta.second;
            }
        }
        else {
            std::set<std::pair<int,int>> to_move_list;
            if (can_move_vertically(check_pos, delta.first, to_move_list, walls, balls, balls_closed)) {
                std::vector<std::pair<int,int>> to_insert;
                std::vector<std::pair<int,int>> to_insert_closed;
                for (const auto move_pos : to_move_list) {
                    auto new_pos = move_pos;
                    new_pos.first += delta.first;
                    if (is_pos_in_set(move_pos, balls)) {
                        balls.erase(move_pos);
                        to_insert.push_back(new_pos);
                    } else if (is_pos_in_set(move_pos, balls_closed)) {
                        balls_closed.erase(move_pos);
                        to_insert_closed.push_back(new_pos);
                    }
                }
                for (auto pos : to_insert) {
                    balls.insert(pos);
                }
                for (auto pos : to_insert_closed) {
                    balls_closed.insert(pos);
                }
                current.first += delta.first;
                current.second += delta.second;
            }
        }
        // print_matrix();
    }

    for (auto ball : balls) {
        sum+= 100*ball.first+ball.second;
    }
    return std::to_string(sum);
}
