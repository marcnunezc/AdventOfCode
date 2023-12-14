std::vector<int> count_springs(std::string& spring) {
    std::vector<int> spring_sizes;
    char last = '.';
    int sum = 0;

    for (auto c : spring) {
        if (c == '#' && last == '.') {
            sum=1;
            last = '#';
        } else if (c == '#' && last == '#') {
            sum++;
        }
        else if (c == '.' && last == '#') {
            spring_sizes.push_back(sum);
            last = '.';
        }
    }
    if (last == '#')
        spring_sizes.push_back(sum);
    return spring_sizes;
}

void print_spring(std::string& spring) {
    cout << spring << endl;
}

AOC_DAY(Day12_1){
    std::size_t sum = 0;
    std::string line;
    std::vector<string> spring_list;
    std::vector<std::vector<int>> input_sizes_list;
    while(getline(cin, line)) {
        std::stringstream ss(line);
        std::string spring;
        ss >> spring;
        spring_list.push_back(spring);
        std::vector<int> input_sizes;
        std::string spring_size;
        while (getline(ss, spring_size, ',')) {
            input_sizes.push_back(stoi(spring_size));
        }
        input_sizes_list.push_back(input_sizes);
    }

    for (int m=0; m<spring_list.size(); m++) {
        auto spring = spring_list[m];
        std::vector<int> question_mark_ids ;
        auto base_sizes = input_sizes_list[m];
        auto id = spring.find('?');
        while (id != string::npos) {
            question_mark_ids.push_back(id);
            id = spring.find('?',id+1);
        }
        int number_of_question = question_mark_ids.size();
        int number_of_permutations = 1 << number_of_question;
        int number_of_valid_permuations = 0;

        for (int i = 0; i < number_of_permutations; ++i) {

            std::bitset<32> binary(i);

            std::string permutation = binary.to_string().substr(32 - number_of_question);

            std::replace(permutation.begin(), permutation.end(), '0', '.');
            std::replace(permutation.begin(), permutation.end(), '1', '#');

            for (int j=0; j<permutation.size(); j++) {
                spring[question_mark_ids[j]] = permutation[j];
            }


            auto computed_sizes = count_springs(spring);

            if (computed_sizes == base_sizes) {

                number_of_valid_permuations++;
            }

        }
        sum += number_of_valid_permuations;
    }
    return std::to_string(sum);
}

AOC_DAY(Day12_2){
    std::size_t sum = 0;

    return std::to_string(sum);
}