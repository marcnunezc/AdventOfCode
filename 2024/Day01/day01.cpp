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

    std::ranges::sort(list1);
    std::ranges::sort(list2);

    std::size_t sum=0;
    for (std::size_t i = 0; i<list1.size(); i++)
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
    std::size_t sum=0;

    for (auto num : list2) {
        number_apperance[num]++;
    }

    for (auto num : list1) {
        sum += num * number_apperance[num];
    }

    return std::to_string(sum);
}
