size_t prune(size_t secret_number) {
    return secret_number % 16777216;
}
size_t mix(size_t secret_number, size_t value) {
    return secret_number ^ value;
}

AOC_DAY(Day22_1) {

    std::string line;
    size_t n_conversions = 2000;
    std::size_t sum = 0;

    while (getline(cin, line)) {
        size_t number = std::stoul(line);
        for (size_t i = 0; i < n_conversions; i++) {
            number = prune(mix(number, number * 64));
            number = prune(mix(number, number / 32));
            number = prune(mix(number, number * 2048));
        }
        sum += number;

    }
    return std::to_string(sum);
}

AOC_DAY(Day22_2) {
    std::string line;
    size_t n_conversions = 2000;
    std::size_t sum = 0;
    std::vector<std::vector<int>> price_changes_list;
    std::vector<std::vector<size_t>> price_values_list;

    while (getline(cin, line)) {
        std::vector<int> price_changes;
        std::vector<size_t> price_values;
        size_t number = std::stoul(line);
        price_values.push_back(number % 10);
        price_changes.push_back(0);
        for (size_t i = 1; i < n_conversions+1; i++) {
            number = prune(mix(number, number * 64));
            number = prune(mix(number, number / 32));
            number = prune(mix(number, number * 2048));
            price_values.push_back(number % 10);
            size_t price = number % 10;
            size_t last_price = price_values[i-1];
            price_changes.push_back(price - last_price);
        }
        sum += number;
        price_changes_list.push_back(price_changes);
        price_values_list.push_back(price_values);
    }
    std::map<std::tuple<int,int,int,int>, size_t> banana_prices;

    for (size_t i = 0; i < price_changes_list.size(); i++) {
        auto price_changes = price_changes_list[i];
        size_t m = 1;
        std::set<std::tuple<int,int,int,int>> visited_permutations;
        while (m < price_changes.size()-3) {
            auto permutation = std::tuple<int,int,int,int>{price_changes[m], price_changes[m+1], price_changes[m+2], price_changes[m+3]};
            if (visited_permutations.find(permutation) != visited_permutations.end()) {
                m++;
                continue;
            }
            visited_permutations.insert(permutation);
            banana_prices[permutation] += price_values_list[i][m+3];
            m++;
        }
    }
    size_t max_banana = 0;
    for (const auto& [permutation, value] : banana_prices) {
        max_banana = std::max(max_banana, value);
    }

    return std::to_string(max_banana);
}