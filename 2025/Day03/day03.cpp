AOC_DAY(Day03_1) {

    std::size_t sum = 0;
    std::string line;
    while (getline(cin, line)) {
        auto it_left_digit = std::max_element(line.begin(), line.end()-1);
        size_t pos = std::distance(line.begin(), it_left_digit);

        auto right_string = line.substr(pos + 1);
        auto it_right_digit = std::max_element(right_string.begin(), right_string.end());

        char left_digit = *it_left_digit;
        char right_digit = *it_right_digit;


        auto number = (left_digit - '0') * 10 + (right_digit- '0');

        sum += number;
    }
    return std::to_string(sum);
}

AOC_DAY(Day03_2){
    std::size_t sum = 0;
    std::string line;
    while (getline(cin, line)) {

        std::string current_string = line;
        std::array<char, 12> numbers;
        for (size_t digit_pos = 12; digit_pos > 0; digit_pos--) {
            auto it_max_digit = std::max_element(current_string.begin(), current_string.end()-digit_pos+1);
            size_t pos = std::distance(current_string.begin(), it_max_digit);
            char max_digit = *it_max_digit;
            numbers[digit_pos-1] = max_digit;

            current_string = current_string.substr(pos + 1);
        }
        std::size_t multiplier = 1;
        size_t number = 0;
        for (int i=0; i<numbers.size(); i++){
            number += multiplier*(numbers[i] - '0');
            multiplier*=10;
        }

        sum += number;
    }
    return std::to_string(sum);
}
