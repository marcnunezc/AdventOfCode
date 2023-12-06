
AOC_DAY(Day06_1){
    std::string line;
    getline(cin,line);
    std::vector<int> times;
    std::vector<int> distances;
    int value;
    std::stringstream ss(line.substr(line.find(":")+1));
    while (ss>>value) times.push_back(value);
    getline(cin,line);
    std::stringstream ss_dist(line.substr(line.find(":")+1));
    while (ss_dist>>value) distances.push_back(value);

    size_t multiplication = 1;
    for (int i=0; i<times.size(); i++) {
        size_t sum = 0;
        for (int t=0; t<=times[i]; t++) {
            int waited_time = t;
            int remaining_time = times[i]-t;
            int distance_travelled = remaining_time*waited_time;
            if (distance_travelled > distances[i]) {
                sum++;
            }

        }
        multiplication *= sum;
    }
    return std::to_string(multiplication);
}

AOC_DAY(Day06_2){
    std::string line;

    getline(cin,line);
    line = line.substr(line.find(":")+1);
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    IntType total_time = stol(line);

    getline(cin,line);
    line = line.substr(line.find(":")+1);
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    IntType distance = stol(line);

    // solve for t: (total_time-t)*t > distance
    IntType t1 = (total_time-std::sqrt(total_time*total_time-4*distance))/2;
    IntType t2 = (total_time+std::sqrt(total_time*total_time-4*distance))/2;

    size_t sum = std::floor(t2)-std::ceil(t1);

    return std::to_string(sum);
}