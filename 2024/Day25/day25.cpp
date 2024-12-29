AOC_DAY(Day25_1) {
    std::string line;
    std::size_t sum = 0;
    std::vector<std::vector<size_t>> locks;
    std::vector<std::vector<size_t>> keys;
    size_t key_length = 5;
    while(getline(cin,line)) {
        if (line[0] == '#') {
            std::vector<size_t> lock(line.size(), 0);
            while (!line.empty() &&  getline(cin, line)) {
                for (size_t i = 0; i<line.size(); i++) {
                    if (line[i] == '#')
                        lock[i]++;
                }
            }
            locks.push_back(lock);
        } else if (line[0]== '.') {
            std::vector<size_t> key(line.size(), 0);
            while (!line.empty() &&  getline(cin, line)) {
                for (size_t i = 0; i<line.size(); i++) {
                    if (line[i] == '#')
                        key[i]++;
                }
            }
            for (size_t i = 0; i<key.size(); i++) {
                key[i]--;
            }
            keys.push_back(key);
        }
    }

    for (auto lock : locks) {
        for (auto key : keys) {
            bool to_sum = true;
            for (size_t i = 0; i<key.size();i++) {
                if (key[i]+lock[i] > key_length) {
                    to_sum = false;
                    break;
                }
            }
            if (to_sum) {
                sum++;
            }
        }
    }

    return std::to_string(sum);
}
