AOC_DAY(Day01_1){

    std::string line;
    std::vector<int> list1, list2;
    while(getline(cin, line)) {
        int num1, num2;
        std::stringstream ss(line);
        ss >> num1 >> num2;
        list1.push_back(num1);
        list2.push_back(num2);
    }

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    unsigned int sum=0;
    for (unsigned int i = 0; i<list1.size(); i++)
    {
        sum += std::abs(list1[i]-list2[i]);
    }

    return std::to_string(sum);
}

AOC_DAY(Day01_2){

    std::string line;
    std::vector<int> list1, list2;
    while(getline(cin, line)) {
        int num1, num2;
        std::stringstream ss(line);
        ss >> num1 >> num2;
        list1.push_back(num1);
        list2.push_back(num2);
    }

    std::unordered_map<int, int> number_apperance;
    unsigned int sum=0;

    for (auto num : list2) {
        number_apperance[num]++;
    }

    for (auto num : list1) {
        sum += num * number_apperance[num];
    }

    return std::to_string(sum);
}
