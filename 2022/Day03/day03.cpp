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
            auto found = line.find(c, line.length()/2);
            if (found != string::npos) {
                total += score[c];
                break;
            }
        }
    }
    cout << total << endl;
}

AOC_DAY(Day03_2){
    std::string line;
    std::map<char, int> score = compute_score();
    int total = 0, group = 0;
    std::vector<std::string> group_rucksack;
    while(getline(cin, line)) {
        group_rucksack.push_back(line);
        group++;
        if (group < 3)
            continue;
        else {
            std::string first = group_rucksack[0];
            for (char c : first) {
                char found1 = group_rucksack[1].find(c);
                char found2 = group_rucksack[2].find(c);
                if (found1 != string::npos && found2 != string::npos) {
                    total += score[c];
                    break;
                }
            }
            group = 0;
            group_rucksack.clear();
        }
    }
    cout << total << endl;
}
