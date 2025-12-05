AOC_DAY(Day02_1) {

    std::size_t sum = 0;
    std::string line;
    while (getline(cin, line, ','))
    {
        if (line[0]=='\n') continue;

        std::string left_str = line.substr(0, line.find('-'));
        std::string right_str = line.substr(line.find('-')+1);
        std::size_t left = std::stoul(left_str);
        std::size_t right = std::stoul(right_str);
        std::size_t len_left = left_str.length();
        std::size_t len_right = right_str.length();

        if (len_left == len_right && len_left % 2 == 1) {
            continue;
        }

        std::size_t test_number = left;

        while (right >= test_number) {
            std::size_t digits = std::to_string(test_number).length();
            if (digits % 2 == 0) {
                std::string first_half = std::to_string(test_number).substr(0, digits / 2);
                std::string second_half = std::to_string(test_number).substr(digits / 2);
                if (first_half == second_half) {
                    cout << "Found repeating number : " << test_number << endl;
                    sum += test_number;
                }
            }
            test_number++;
        }

    }
    return std::to_string(sum);
}

AOC_DAY(Day02_2){
    std::size_t sum = 0;
    std::string line;
    std::set<std::size_t> found_numbers;
    while (getline(cin, line, ','))
    {
        if (line[0]=='\n') continue;

        std::string left_str = line.substr(0, line.find('-'));
        std::string right_str = line.substr(line.find('-')+1);
        std::size_t left = std::stoul(left_str);
        std::size_t right = std::stoul(right_str);
        std::size_t len_left = left_str.length();
        std::size_t len_right = right_str.length();

        std::size_t test_number = left;

        while (right >= test_number) {
            std::size_t digits = std::to_string(test_number).length();

            for (int split = 1; split <= digits/2; split++) {

                std::size_t pos = 0;
                bool need_to_sum = true;

                while (pos + split < digits) {
                    std::string subdivision = std::to_string(test_number).substr(pos, split);
                    std::string next_subdivision = std::to_string(test_number).substr(pos+split, split);
                    if (subdivision != next_subdivision) {
                        need_to_sum = false;
                        break;
                    }
                    pos += split;
                }
                if (need_to_sum) {
                    found_numbers.insert(test_number);
                }
            }
            test_number++;
        }

    }
    sum = std::accumulate(found_numbers.begin(), found_numbers.end(), 0ULL);
    return std::to_string(sum);
}
