
std::vector<std::string> get_list_content(std::string input) {
    int close=0,open=1,i=1;
    for (i=1; i<input.length();i++) {
        if (input[i] == '[')
            open++;
        if (input[i] == ']')
            close++;

        if(open == close)
            break;
    }
    std::string clean_list = input.substr(1, i-1);
    std::vector<std::string> output;
    std::string substr;
    open=0;close=0;
    int start = 0;
    size_t pos = clean_list.find(",", start);
    while (pos != std::string::npos) {
        substr = clean_list.substr(start, pos-start);

        for (auto c : substr) {
            if (c == '[')
                open++;
            if (c == ']')
                close++;
        }
        if (open == close) {
            output.push_back(clean_list.substr(0, pos));
            clean_list.erase(0, pos + 1);
            pos = clean_list.find(",");
            start = 0;
        }
        else {
            start = pos+1;
            pos = clean_list.find(",", pos+1);
        }
    }
    output.push_back(clean_list);

    return output;
}


enum RESULT {
    RIGHT,
    WRONG,
    DRAW
};

bool is_integer(std::string input) {
    if (input.find("[") == string::npos && input.find("]") == string::npos)
        return true;
    else
        return false;
}

int compare_values(std::string first_packet, std::string second_packet) {
    auto first_content = get_list_content(first_packet);
    auto second_content = get_list_content(second_packet);
    int max_size = max(first_content.size(), second_content.size());
    for (int i = 0; i<max_size; i++) {
        if (first_content[i].empty() && second_content[i].empty())
            return RESULT::DRAW;
        if ((i+1)>first_content.size() || first_content[i].empty()) {
            return RESULT::RIGHT;
        }
        if ((i+1)>second_content.size() || second_content[i].empty()) {
            return RESULT::WRONG;
        }
        if (is_integer(first_content[i]) && is_integer(second_content[i])) {
            bool compare = stoi(first_content[i]) < stoi(second_content[i]);

            if (stoi(first_content[i]) < stoi(second_content[i])) {
               return RESULT::RIGHT;
            }
            else if (stoi(first_content[i]) > stoi(second_content[i])) {
                return RESULT::WRONG;
            }
        }
        else {
            std::string first_to_send = first_content[i];
            std::string second_to_send = second_content[i];
            if (is_integer(first_content[i])) {
                first_to_send = "["+first_content[i]+"]";
            }
            if (is_integer(second_content[i])) {
                second_to_send = "["+second_content[i]+"]";
            }
            auto ret = compare_values(first_to_send, second_to_send);
            if (ret != RESULT::DRAW)
                return ret;
        }

    }
    return RESULT::DRAW;
}

AOC_DAY(Day13_1) {

    std::string line;
    std::vector<std::pair<std::string, std::string>> packet_vector;
    while(getline(cin, line)) {
        if (!line.empty()) {
            std::pair<std::string, std::string> packet_pair;
            packet_pair.first = line;
            getline(cin, line);
            packet_pair.second = line;
            packet_vector.push_back(packet_pair);
        }
    }
    int index = 0, sum = 0;
    for (auto packet_pair :packet_vector) {
        index++;
        auto ret = compare_values(packet_pair.first, packet_pair.second);
        if (ret == RESULT::RIGHT) {
            sum += index;
        }
    }

    return std::to_string(sum);
}

AOC_DAY(Day13_2) {
    std::string line;
    std::vector<std::string> packet_vector;
    while(getline(cin, line)) {
        if (!line.empty()) {
            packet_vector.push_back(line);
        }
    }
    packet_vector.push_back("[[2]]");
    packet_vector.push_back("[[6]]");
    int index = 0, sum = 0;
    bool is_ordered = true;
    while (true) {
        index++;
        if (index==packet_vector.size()) {
            index=1;
            if (is_ordered)
                break;
            is_ordered = true;
            
        }
        auto ret = compare_values(packet_vector[index-1], packet_vector[index]);
        if (ret != RESULT::RIGHT) {
            is_ordered = false;
            auto aux = packet_vector[index];
            packet_vector[index] = packet_vector[index-1];
            packet_vector[index-1] = aux;
        }
    }
    int first_index = find(packet_vector.begin(), packet_vector.end(), "[[2]]") - packet_vector.begin() + 1;
    int second_index = find(packet_vector.begin(), packet_vector.end(), "[[6]]") - packet_vector.begin() + 1;

    return std::to_string(first_index*second_index);
}
