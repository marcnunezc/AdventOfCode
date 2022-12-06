std::map<char, int> compute_score() {
    std::map<char, int> score;
    for (unsigned int i=0; i<26; i++) {
        char lower = 'a'+i;
        char upper = toupper('a'+i);
        score[lower] = i+1;
        score[upper] = i+27;
    }
    return score;
}

AOC_DAY(Day03_1){
    std::string line;
    int total = 0;
    std::map<char, int> score = compute_score();

    while(getline(cin, line)) {
        auto first_half = line.substr(0, line.length()/2);
        for (char c : first_half) {
            if (line.find(c, line.length()/2) != string::npos) {
                total += score[c];
                break;
            }
        }
    }
    return std::to_string(total);
}

AOC_DAY(Day03_2){
    std::string line;
    std::map<char, int> score = compute_score();
    int total = 0;
    std::vector<std::string> group_rucksack;
    while(getline(cin, line)) {
        group_rucksack.push_back(line);
        if (group_rucksack.size() < 3)
            continue;
        else {
            std::string first = group_rucksack[0];
            for (char c : first) {
                if (group_rucksack[1].find(c) != string::npos && group_rucksack[2].find(c) != string::npos) {
                    total += score[c];
                    break;
                }
            }
            group_rucksack.clear();
        }
    }
    return std::to_string(total);
}
