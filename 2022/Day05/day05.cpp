std::vector<std::vector<char>> get_inital_stacks() {
    std::vector<std::vector<char>> stacks;
    std::string line;

    while(getline(cin, line)) {
        if (line.find("1") != string::npos) {
            break;
        }
        else {
            size_t pos = line.find("[", 0);
            while(pos != string::npos)
            {
                int stack_number = pos/4 + 1;
                if (stacks.size() < stack_number)
                        stacks.resize(stack_number);
                stacks[stack_number-1].push_back(line[pos+1]);
                pos = line.find("[",pos+1);

            }
        }
    }
    for (int i = 0; i < stacks.size(); i++) {
        reverse(stacks[i].begin(), stacks[i].end());
    }
    return stacks;
}

void rearrange_stacks(std::vector<std::vector<char>>& stacks , std::function<int(int, int)> compute_index) {
    std::string line;
    while(getline(cin, line)) {
        if (line.empty())
            continue;
        int n_moves, source, destination;
        sscanf(line.c_str(), "move %i from %i to %i", &n_moves, &source, &destination);

        std::vector<char> tmp_stack(n_moves, ' ');
        for (int i=0; i<tmp_stack.size(); i++) {
            tmp_stack[compute_index(i, n_moves)] = stacks[source-1].back();
            stacks[source-1].pop_back();
        }
        stacks[destination-1].insert(stacks[destination-1].end(), tmp_stack.begin(), tmp_stack.end());
    }
}

AOC_DAY(Day05_1){

    std::vector<std::vector<char>> stacks = get_inital_stacks();
    rearrange_stacks(stacks, [](int j, int total) {return j;});
    std::stringstream ss;
    for (auto vec : stacks) {
        ss << vec.back();
    }
    return ss.str();
}

AOC_DAY(Day05_2) {

    std::vector<std::vector<char>> stacks = get_inital_stacks();
    rearrange_stacks(stacks, [](int j, int total) {return total-j-1;});
    std::stringstream ss;
    for (auto vec : stacks) {
        ss << vec.back();
    }
    return ss.str();
}
