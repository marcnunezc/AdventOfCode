

AOC_DAY(Day04_1){
    size_t sum = 0;
    std::string line;
    while(getline(cin, line)) {
        auto numbers_string = line.substr(line.find(":")+2);
        auto winning_numbers = numbers_string.substr(0,numbers_string.find("|"));
        auto my_numbers = numbers_string.substr(numbers_string.find("|")+1);
        std::unordered_set<int> my_numbers_set;
        std::stringstream ss(my_numbers);
        int number;
        // store my numbers
        while(ss >> number) {
            my_numbers_set.emplace(number);
        }
        int count=0;
        std::istringstream ss_win(winning_numbers);
        // count matching with winning
        while(ss_win >> number) {
            if (my_numbers_set.find(number) != my_numbers_set.end()) {
                count++;
            }
        }
        if (count > 0)
            sum += pow(2, count-1);
    }
    return std::to_string(sum);
}

AOC_DAY(Day04_2){
    size_t sum = 0;
    std::string line;
    std::vector<int> number_of_instances(215, 1);
    int card_id = 0;
    while(getline(cin, line)) {
        card_id++;
        auto numbers_string = line.substr(line.find(":")+2);
        auto winning_numbers = numbers_string.substr(0,numbers_string.find("|"));
        auto my_numbers = numbers_string.substr(numbers_string.find("|")+1);
        std::unordered_set<int> my_numbers_set;
        std::stringstream ss(my_numbers);
        int number;
        // store my numbers
        while(ss >> number) {
            my_numbers_set.emplace(number);
        }
        int count=0;
        std::istringstream ss_win(winning_numbers);
        // count matching with winning
        while(ss_win >> number) {
            if (my_numbers_set.find(number) != my_numbers_set.end()) {
                count++;
            }
        }
        if (count > 0) {
            for (int i=card_id+1; i<card_id+1+count; i++) {
                number_of_instances[i] += number_of_instances[card_id];
            }
        }
    }
    return std::to_string(std::accumulate(number_of_instances.begin()+1, number_of_instances.begin()+card_id+1, 0));
}
