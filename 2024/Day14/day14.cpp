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
    // Q1 : Q2
    //.........
    // Q3 : Q4

    bool simetric = false;
    // for (int n_seconds = 1; n_seconds<100;n_seconds++) {
    int n_seconds = 1;
    while (!simetric) {
        std::array<int, 4> quadrants({0,0,0,0});
        std::map<std::pair<int,int>, int> positions;

        for (auto rt : robot_list) {
            rt.x += ( n_seconds * rt.vx ) % max_x;
            rt.y += ( n_seconds * rt.vy ) % max_y;
            rt.x = rt.x >= 0 ? rt.x % max_x : rt.x + max_x;
            rt.y = rt.y >= 0 ? rt.y % max_y : rt.y + max_y;

            if (positions.find({rt.x,rt.y}) == positions.end())
                positions.insert({{rt.x,rt.y},1});
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
            else {
                positions[{rt.x,rt.y}]++;
            }
        }
        }

        cout << n_seconds << endl;
        cout <<  endl;
        for (int j = 0; j<max_y; j++) {
                for (int i =0; i<max_x; i++) {
                    if (positions.find({i,j}) == positions.end())
                        cout << '.';
                    else
                        cout << positions[{i,j}];
                }
                cout << endl;
        }
        cout <<  endl;
        cout <<  endl;
        if (quadrants[0] == quadrants[1]  || quadrants[2] == quadrants[3]) {

        break;

        }
    }


    return std::to_string(product);
}
