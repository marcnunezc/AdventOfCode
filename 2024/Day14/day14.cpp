struct Robot {
    int x;
    int y;
    int vx;
    int vy;
};

AOC_DAY(Day14_1) {
    std::string line;
    std::vector<Robot> robot_list;
    std::size_t product = 1;
    int n_seconds = 100;

    while (getline(cin, line)) {
        Robot robot;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &robot.x, &robot.y, &robot.vx, &robot.vy);
        robot_list.push_back(robot);
    }

    int max_x,max_y;
    if (robot_list.size()>30) {
        max_x = 101; max_y = 103;
    }
    else {
        max_x = 11; max_y = 7;
    }

    // Q1 : Q2
    //.........
    // Q3 : Q4
    std::array<int, 4> quadrants({0,0,0,0});

    for (auto rt : robot_list) {
        rt.x += ( n_seconds * rt.vx ) % max_x;
        rt.y += ( n_seconds * rt.vy ) % max_y;
        rt.x = rt.x >= 0 ? rt.x % max_x : rt.x + max_x;
        rt.y = rt.y >= 0 ? rt.y % max_y : rt.y + max_y;

        if (rt.y < max_y/2) {
            if (rt.x < max_x/2)
                quadrants[0]++;
            else if (rt.x > max_x/2)
                quadrants[1]++;
        }
        else if (rt.y > max_y/2) {
            if (rt.x < max_x/2)
                quadrants[2]++;
            else if (rt.x > max_x/2)
                quadrants[3]++;
        }
    }

    for (auto value : quadrants) {
        product *= value;
    }

    return std::to_string(product);
}

AOC_DAY(Day14_2){

    std::string line;
    std::vector<Robot> robot_list;
    std::size_t product = 1;

    while (getline(cin, line)) {
        Robot robot;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &robot.x, &robot.y, &robot.vx, &robot.vy);
        robot_list.push_back(robot);
    }

    int max_x,max_y;
    if (robot_list.size()>30) {
        max_x = 101; max_y = 103;
    }
    else {
        max_x = 11; max_y = 7;
    }

    int n_seconds = 0;
    bool detected_large_continuous_line = false;
    while (!detected_large_continuous_line) {
        n_seconds++;
        std::array<int, 4> quadrants({0,0,0,0});
        std::set<std::pair<int,int>> positions;

        for (auto rt : robot_list) {
            rt.x += ( n_seconds * rt.vx ) % max_x;
            rt.y += ( n_seconds * rt.vy ) % max_y;
            rt.x = rt.x >= 0 ? rt.x % max_x : rt.x + max_x;
            rt.y = rt.y >= 0 ? rt.y % max_y : rt.y + max_y;

            positions.insert({{rt.x,rt.y}});
        }

        int target = 10; // search for 10 contiguous positions
        for (auto& [x, y] : positions) {

            bool is_large = true;
            for (int i = 1; i<target+1; i++) {
                if (positions.find({x+i, y}) == positions.end()){
                    is_large = false;
                    break;
                }
            }
            if (is_large) {
                detected_large_continuous_line = true;
                break;
            }

        }

    }


    return std::to_string(n_seconds);
}
