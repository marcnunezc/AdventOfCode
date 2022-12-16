int get_distance(pair<int,int> a, pair<int,int> b) {
    return std::abs(a.first-b.first)+std::abs(a.second-b.second);
}

AOC_DAY(Day15_1) {
    int target_y = 2000000;

    std::map<pair<int,int>, pair<int,int>> sensor_beacon_map;
    std::set<pair<int,int>> beacon_set;

    std::string line;
    while(getline(cin,line)) {
        pair<int,int> sensor;
        pair<int,int> beacon;
        sscanf(line.c_str(), "Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i", &sensor.first, &sensor.second, &beacon.first, &beacon.second);
        sensor_beacon_map[sensor]=beacon;
        if (sensor.first>100 && target_y == 10)
            target_y = 2000000;
        if (beacon.second == target_y)
            beacon_set.insert(beacon);
    }

    std::set<pair<int,int>> free_spots;

    for (auto it = sensor_beacon_map.begin(); it!=sensor_beacon_map.end(); it++) {
        auto sensor = it -> first;
        auto beacon = it -> second;
        int distance = get_distance(sensor, beacon);
        pair<int,int> closest_y({sensor.first, target_y});
        int distance_closest = get_distance(sensor, closest_y);
        if (distance_closest < distance) {
            for (int i=0; i<(distance-distance_closest+1); i++) {
                if (beacon_set.find({closest_y.first+i, target_y})==beacon_set.end())
                    free_spots.insert({closest_y.first+i, target_y});
                if (beacon_set.find({closest_y.first-i, target_y})==beacon_set.end())
                    free_spots.insert({closest_y.first-i, target_y});
            }
        }
    }


    return std::to_string(free_spots.size());
}


AOC_DAY(Day15_2) {

    int max_coord = 20;
    std::map<pair<int,int>, int> sensor_distance_map;

    std::string line;
    while(getline(cin,line)) {
        pair<int,int> sensor;
        pair<int,int> beacon;
        sscanf(line.c_str(), "Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i", &sensor.first, &sensor.second, &beacon.first, &beacon.second);
        int distance = get_distance(sensor, beacon);
        sensor_distance_map[sensor] = distance;

        if (sensor.first>100 && max_coord == 20)
            max_coord = 4000000;
    }

    auto get_max_distance = [&](int x, int y) {
        bool all_smaller = true;
        int max_distance = 0;
        for (auto it = sensor_distance_map.begin(); it!=sensor_distance_map.end(); it++) {
            auto sensor = it -> first;
            auto distance_sensor_to_beacon = it -> second;
            auto distance = get_distance(sensor, {x,y});

            if (distance <= distance_sensor_to_beacon) {
                if ((distance_sensor_to_beacon-distance) > max_distance) {
                    max_distance = (distance_sensor_to_beacon-distance)+1;
                }
                all_smaller=false;
            }
        }
        if (all_smaller)
            return -1;
        else {
            if (max_distance)
                return max_distance;
            else
                return 1;
        }
    };
    long unsigned int tuning = 0;

    std::deque<pair<int,int>> candidate_points;
    candidate_points.push_back({0,0});
    int count = 0;
    while (tuning == 0) {
        count++;
        auto next_point = candidate_points.front();
        candidate_points.pop_front();
        auto max_distance = get_max_distance(next_point.first, next_point.second);
        if (max_distance== -1) {
            tuning = 4000000UL*next_point.first+next_point.second;
        } else {
            int x = next_point.first+max_distance;
            int y = next_point.second;
            if (x>max_coord) {
                x=0;
                y++;
            }
            candidate_points.push_back({x,y});
        }
    }
    return std::to_string(tuning);
}