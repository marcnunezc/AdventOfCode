AOC_DAY(Day03_1){

    std::string line;
    std::size_t sum = 0;

    std::regex word_regex("mul\\(\\d{1,3},\\d{1,3}\\)");


    while (getline(cin, line)) {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
        auto words_end = std::sregex_iterator();

        int x,y;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();
            sscanf(match_str.c_str(), "mul(%d,%d)", &x, &y);
            sum += x*y;
        }
    }

    return std::to_string(sum);
}

AOC_DAY(Day03_2){

    std::string line;
    std::size_t sum = 0;

    std::regex word_regex("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don't\\(\\)");

    bool do_sum = true;
    while (getline(cin, line)) {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
        auto words_end = std::sregex_iterator();

        int x,y;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();
            if (!match_str.compare("do()")) {
                do_sum = true;
            } else if (!match_str.compare("don't()")) {
                do_sum = false;
            } else if (do_sum) {
                sscanf(match_str.c_str(), "mul(%d,%d)", &x, &y);
                sum += x*y;
            }
        }
    }

    return std::to_string(sum);
}
