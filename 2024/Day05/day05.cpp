bool is_ordered(std::vector<int>& page_numbers, std::unordered_map<int, std::set<int>>& order_map) {
    bool failed=true;
    for (std::size_t i=0; i<page_numbers.size()-1; i++) {
        auto first = page_numbers[i];
        auto second = page_numbers[i+1];
        if (order_map[first].find(second) == order_map[first].end()) {
            std::swap(page_numbers[i], page_numbers[i+1]);
            failed=false;
        }
    }
    return failed;
}

AOC_DAY(Day05_1){

    std::string line;
    std::size_t sum = 0;
    std::unordered_map<int, std::set<int>> order_map;
    while(getline(cin, line)) {
        if (line.empty())
            break;
        int left, right;
        sscanf(line.c_str(), "%d|%d", &left, &right);
        if (order_map.find(left) == order_map.end()) {
            std::set<int> minor_numbers;
            minor_numbers.insert(right);
            order_map[left]=minor_numbers;
        } else {
            order_map[left].insert(right);
        }
    }
    while(getline(cin, line)) {
        std::vector<int> page_numbers;
        std::stringstream ss(line);
        int x;
        while (ss >> x) {
            if (ss.peek() == ',')
                ss.ignore();
            page_numbers.push_back(x);
        }

        if (is_ordered(page_numbers, order_map)) {
            sum += page_numbers[page_numbers.size()/2];
        }
    }
    return std::to_string(sum);
}


AOC_DAY(Day05_2){

    std::string line;
    std::size_t sum = 0;
    std::unordered_map<int, std::set<int>> order_map;
    while(getline(cin, line)) {
        if (line.empty())
            break;
        int left, right;
        sscanf(line.c_str(), "%d|%d", &left, &right);
        if (order_map.find(left) == order_map.end()) {
            std::set<int> minor_numbers;
            minor_numbers.insert(right);
            order_map[left]=minor_numbers;
        } else {
            order_map[left].insert(right);
        }
    }
    while(getline(cin, line)) {
        std::vector<int> page_numbers;
        std::stringstream ss(line);
        int x;
        while (ss >> x) {
            if (ss.peek() == ',')
                ss.ignore();
            page_numbers.push_back(x);
        }

        if (!is_ordered(page_numbers, order_map))
        {
            while(!is_ordered(page_numbers,order_map)) {}

            sum += page_numbers[page_numbers.size()/2];
        }
    }
    return std::to_string(sum);
}
