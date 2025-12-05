AOC_DAY(Day05_1) {

    std::size_t sum = 0;
    std::string line;
    std::vector<std::pair<size_t, size_t>> list_of_ranges;

    while(getline(cin,line)) {
        if (line.empty())
            break;
        std::size_t left = std::stoul(line.substr(0, line.find('-')));
        std::size_t right = std::stoul(line.substr(line.find('-')+1));

        list_of_ranges.push_back({left, right});
    }

    while(getline(cin,line)) {
        std::size_t value = std::stoul(line);
        for (auto [left, right] : list_of_ranges) {
            if (left <= value && value <= right) {
                sum++;
                break;
            }
        }
    }

    return std::to_string(sum);
}

AOC_DAY(Day05_2){
    std::size_t sum = 0;
    std::string line;
    std::vector<std::pair<size_t, size_t>> list_of_ranges;

    while(getline(cin,line)) {
        if (line.empty())
            break;
        std::size_t left = std::stoul(line.substr(0, line.find('-')));
        std::size_t right = std::stoul(line.substr(line.find('-')+1));

        list_of_ranges.push_back({left, right});
    }

    bool found = true;
    std::set<std::pair<size_t, size_t>> new_ranges;
    auto current_list_of_ranges = list_of_ranges;
    while (found) {
        found = false;
        new_ranges.clear();
        for (int i=0; i<current_list_of_ranges.size(); i++) {
            for (int j = i; j<current_list_of_ranges.size(); j++) {
                if (i == j)
                    continue;
                auto [i_left, i_right] = current_list_of_ranges[i];
                auto [j_left, j_right] = current_list_of_ranges[j];
                if (i_left <= j_left && j_left <= i_right) {
                    if (i_right < j_right)  {
                        new_ranges.insert({i_left, j_right});
                        found = true;
                    }
                    else {
                        new_ranges.insert({i_left, i_right});
                        found = true;
                    }
                } else if  (i_left <= j_right && j_right <= i_right) {
                    if (j_left < i_left)  {
                        new_ranges.insert({j_left, i_right});
                        found = true;
                    }
                    else {
                        new_ranges.insert({i_left, i_right});
                        found = true;
                    }
                } else {
                    new_ranges.insert({i_left, i_right});
                    new_ranges.insert({j_left, j_right});
                }
            }
        }

        current_list_of_ranges.assign(new_ranges.begin(), new_ranges.end());

        std::vector<size_t> index_fully_included_to_remove;
        for (size_t i = 0; i < current_list_of_ranges.size(); ++i) {
            for (size_t j = 0; j < current_list_of_ranges.size(); ++j) {
                if (i == j) continue;

                auto [i_left, i_right] = current_list_of_ranges[i];
                auto [j_left, j_right] = current_list_of_ranges[j];

                if (j_left <= i_left && i_right <= j_right) {
                    index_fully_included_to_remove.push_back(i);
                    break;
                }
            }
        }
        std::sort(index_fully_included_to_remove.rbegin(), index_fully_included_to_remove.rend());
        for (auto i : index_fully_included_to_remove) {
            current_list_of_ranges.erase(current_list_of_ranges.begin() + i);
        }

    }
    for (auto [left, right] : current_list_of_ranges) {
        sum += right-left+1;
    }

    return std::to_string(sum);
}
