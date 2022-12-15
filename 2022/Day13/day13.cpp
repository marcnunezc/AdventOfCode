
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
    // cout << "analyzin string " << clean_list << endl;
    int start = 0;
    size_t pos = clean_list.find(",", start);
    while (pos != std::string::npos) {
        substr = clean_list.substr(start, pos-start);
        // cout << "got substring " << substr << " start: " << start << " pos " << pos<<endl ;

        for (auto c : substr) {
            if (c == '[')
                open++;
            if (c == ']')
                close++;
        }
        // cout << "open close "<< open << " " << close << endl;
        if (open == close) {
            // cout << "pushing " << clean_list.substr(0, pos) << endl;
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
    for (auto packet_pair :packet_vector) {
        cout << packet_pair.first << endl;
        cout << " content: ";
        int count=0;
        for (auto value : get_list_content(packet_pair.first)) {
            count++;
            cout << value << " ";
        }
        cout << " size: "<< count<<endl;
        cout << packet_pair.second << endl;
        cout << endl;
    }

    return std::to_string(1);
}

AOC_DAY(Day13_2) {


    return std::to_string(2);
}
