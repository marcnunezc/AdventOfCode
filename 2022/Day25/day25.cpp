std::unordered_map<char, int> digit_map = {
    {'2', 2},
    {'1', 1},
    {'0', 0},
    {'-', -1},
    {'=', -2}
};

std::unordered_map<int, char> inverse_map = {
    {2,'2'},
    {1,'1'},
    {0,'0'},
    {-1,'-'},
    {-2,'='}
};

AOC_DAY(Day25_1) {
    std::string line;
    long long int sum = 0;
    while(getline(cin, line)) {
        for (int i=0; i<line.size(); i++) {
            sum += digit_map[line[i]]*std::pow(5, line.size()-i-1);
        }
    }

    std::vector<int> conversion;
    auto div = sum / 5;
    auto rem = sum % 5;
    while (div > 0) {
        conversion.push_back(rem);
        sum = div;
        div = sum / 5;
        rem = sum % 5;
    }
    conversion.push_back(rem);

    for (int i=0; i<conversion.size()-1; i++) {
        if (conversion[i] > 2) {
            conversion[i] = conversion[i]-5;
            conversion[i+1]++;
        }
    }
    if (conversion[conversion.size()-1] > 2) {
        conversion[conversion.size()-1] = conversion[conversion.size()-1]-5;
        conversion.push_back(1);
    }
    std::stringstream ss;
    for (int i=conversion.size()-1; i>-1; i--) {
        ss << inverse_map[conversion[i]];
    }

    return ss.str();
}