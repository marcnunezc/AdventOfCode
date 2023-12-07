AOC_DAY(Day07_1){
    std::unordered_map<char,int> card_rank={{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'T',10},{'J',11},{'Q',12},{'K',13},{'A',14},};
    size_t sum = 0;
    std::string line;
    std::vector<std::pair<std::string, int>> hand_list;

    std::unordered_map<std::string,std::vector<int>> apperances_map;
    auto compute_apperances = [] (std::string s) {
        std::unordered_map<char, int> apperances;
        for (auto& ch : s) apperances[ch]++;

        std::vector<int> sorted_apperances;
        for (auto& values : apperances) sorted_apperances.push_back(values.second);
        sort(sorted_apperances.begin(),sorted_apperances.end(), greater<int>());
        return sorted_apperances;
    };

    while (getline(cin, line)) {
        std::istringstream ss(line);
        std::string hand;
        int bid;
        ss >> hand >> bid;
        hand_list.push_back({hand,bid});
        apperances_map[hand] = compute_apperances(hand);
    }

    auto sort_hand = [&] (std::pair<std::string, int> a, std::pair<std::string, int> b) {
        auto& apperances_a = apperances_map[a.first];
        auto& apperances_b = apperances_map[b.first];
        for (int i=0; i<std::min(apperances_a.size(), apperances_b.size()); i++) {
            if (apperances_a[i] != apperances_b[i])
                return apperances_a[i] < apperances_b[i];
        }
        for (int i=0; i<a.first.length();i++) {
            if (a.first[i] != b.first[i])
                return card_rank[a.first[i]] < card_rank[b.first[i]];
        }
        return true;
    };
    std::sort(hand_list.begin(), hand_list.end(), sort_hand);
    int rank = 0;
    for (auto hand : hand_list) {
        sum += hand.second*(++rank);
    }


    return std::to_string(sum);
}

AOC_DAY(Day07_2){
    std::unordered_map<char,int> card_rank={{'J',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'T',10},{'Q',12},{'K',13},{'A',14},};
    size_t sum = 0;
    std::string line;
    std::vector<std::pair<std::string, int>> hand_list;

    std::unordered_map<std::string,std::vector<int>> apperances_map;
    auto compute_apperances = [] (std::string s) {
        std::unordered_map<char, int> apperances;
        for (auto& ch : s) apperances[ch]++;


        std::vector<int> sorted_apperances;
        for (auto& values : apperances) sorted_apperances.push_back(values.second);
        sort(sorted_apperances.begin(),sorted_apperances.end(), greater<int>());
        if (apperances.find('J')!=apperances.end()) {
            if (sorted_apperances[0] == 4) {
                sorted_apperances[0] = 5;
                sorted_apperances[1] = 0;
            }
            else if (sorted_apperances[0] == 3) {
                sorted_apperances[0] = sorted_apperances[1]+3;
                sorted_apperances[1] = 2-sorted_apperances[1];
                sorted_apperances[2] = 0;
            }
            else if (sorted_apperances[0]==2 && sorted_apperances[1] == 1) {
                sorted_apperances[0] = 3;
                sorted_apperances[3] = 0;
            }
            else if (sorted_apperances[0] == 2 && sorted_apperances[1] == 2) {
                if (apperances['J'] == 2) {
                    sorted_apperances[0] = 4;
                    sorted_apperances[1] = 1;
                    sorted_apperances[2] = 0;
                } else {
                    sorted_apperances[0] = 3;
                    sorted_apperances[1] = 2;
                    sorted_apperances[2] = 0;

                }

            } else if (sorted_apperances[0]==1) {
                sorted_apperances[0] = 2;
            }
        }
        return sorted_apperances;
    };

    while (getline(cin, line)) {
        std::istringstream ss(line);
        std::string hand;
        int bid;
        ss >> hand >> bid;
        hand_list.push_back({hand,bid});
        apperances_map[hand] = compute_apperances(hand);
    }

    auto sort_hand = [&] (std::pair<std::string, int> a, std::pair<std::string, int> b) {
        auto& apperances_a = apperances_map[a.first];
        auto& apperances_b = apperances_map[b.first];
        for (int i=0; i<std::min(apperances_a.size(), apperances_b.size()); i++) {
            if (apperances_a[i] != apperances_b[i])
                return apperances_a[i] < apperances_b[i];
        }
        for (int i=0; i<a.first.length();i++) {
            if (a.first[i] != b.first[i])
                return card_rank[a.first[i]] < card_rank[b.first[i]];
        }
        return true;
    };
    std::sort(hand_list.begin(), hand_list.end(), sort_hand);
    int rank = 0;
    for (auto hand : hand_list) {
        sum += hand.second*(++rank);
    }


    return std::to_string(sum);
}