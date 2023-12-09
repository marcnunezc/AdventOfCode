AOC_DAY(Day09_1){
    std::size_t sum = 0;

    std::string line;
    while(getline(cin,line)) {
        std::vector<int> values;
        std::stringstream ss(line);
        int value;
        while (ss>>value) {
            values.push_back(value);
        }
        int iterations = 0;
        while (!std::all_of(values.begin(), values.end()-iterations, [](int i){return i==0;})) {
            for (int i=1; i<values.size()-iterations; i++) {
                values[i-1]=values[i]-values[i-1];
            }
            iterations++;
        }
        sum += std::accumulate(values.begin(), values.end(), 0);
    }

    return std::to_string(sum);
}

AOC_DAY(Day09_2){
    int sum = 0;

    std::string line;
    while(getline(cin,line)) {
        std::vector<int> values;
        std::stringstream ss(line);
        int value;
        while (ss>>value) {
            values.push_back(value);
        }
        std::reverse(values.begin(), values.end());
        int iterations = 0;
        while (!std::all_of(values.begin(), values.end()-iterations, [](int i){return i==0;})) {
            for (int i=1; i<values.size()-iterations; i++) {
                values[i-1]=values[i]-values[i-1];
            }
            iterations++;
        }
        sum += std::accumulate(values.begin(), values.end(), 0);
    }

    return std::to_string(sum);
}