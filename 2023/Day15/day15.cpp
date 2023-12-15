
AOC_DAY(Day15_1){
    size_t sum = 0;
    std::string word;

    while(getline(cin,word,',')) {
        int current_value=0;
        for (auto c : word) {
            current_value += (int) c;
            current_value *= 17;
            current_value = current_value % 256;
        }
        sum += current_value;
    }
    return std::to_string(sum);
}

AOC_DAY(Day15_2){
    size_t sum = 0;
    std::string word;
    std::vector<std::vector<std::pair<string, int>>> boxes;
    boxes.resize(256);

    while(getline(cin,word,',')) {
        int current_value=0;
        std::string label={};
        for (int i=0; i<word.size(); i++) {
            if (word[i] != '-' && word[i] != '=') {
                current_value += (int) word[i];
                current_value *= 17;
                current_value = current_value % 256;
                label+=word[i];
            } else{
                break;
            }
        }
        auto find_label = [&label](std::pair<string, int>& p) {
                return p.first == label;
        };
        auto& box = boxes[current_value];
        if (word.back() == '-') {
            box.erase(std::remove_if(box.begin(), box.end(), find_label), box.end());
        }
        else {
            auto focal_length = (int) word.back()-'0';
            auto it = std::find_if(box.begin(), box.end(), find_label);
            if (it == box.end()) {
                box.push_back({label, focal_length});
            } else
            {
                it->second = focal_length;
            }
        }
    }
    for (int i =0; i<boxes.size(); i++)  {
        if (boxes[i].size()>0) {
            // cout << "Box " << i << ": ";
            for (int j = 0; j<boxes[i].size(); j++) {
                sum += (i+1)*(j+1)*boxes[i][j].second;
                // cout << "["<< boxes[i][j].first << " " << boxes[i][j].second << "] ";
            }
            // cout << endl;
        }
    }
    return std::to_string(sum);
}