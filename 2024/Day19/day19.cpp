bool match_design(const std::string& stripe, const std::string& pattern, const std::vector<std::string>& possible_stripes) {
    if (pattern.find(stripe) == std::string::npos)
        return false;

    if (pattern.find(stripe) == 0) {
        auto new_pattern = pattern.substr(stripe.size());
        if (new_pattern.empty())
            return true;
        for (const auto& next_stripe : possible_stripes) {
            if (match_design(next_stripe, new_pattern, possible_stripes))
                return true;
        }
    }

    return false;
}


AOC_DAY(Day19_1) {
    std::string line;
    std::size_t sum = 0;


    getline(cin, line);
    std::stringstream ss(line);

    std::vector<std::string> stripes;
    std::string stripe;
    while(getline(ss, stripe, ',')) {
        stripe.erase(std::remove(stripe.begin(), stripe.end(), ' '), stripe.end());
        stripes.push_back(stripe);
    }


    std::vector<std::string> patterns;
    while (getline(cin,line)) {
        if (line.empty())
            continue;
        patterns.push_back(line);
    }


    for (const auto& pattern : patterns) {
        std::vector<std::string> possible_stripes;
        for (auto& stripe : stripes) {
            // check if stripe is contained in pattern
            if (pattern.find(stripe) != std::string::npos) {
                possible_stripes.push_back(stripe);
            }
        }

        for (auto& stripe : stripes) {
            if (match_design(stripe, pattern, possible_stripes)) {
                sum++;
                break;
            }
        }
    }


    return std::to_string(sum);
}

void match_design_and_count(const std::string& stripe, const std::string& pattern, const std::vector<std::string>& possible_stripes, std::size_t& sum, std::map<std::pair<std::string, std::string>, std::size_t>& cache) {
    size_t starting_sum = sum;
    if (pattern.find(stripe) == std::string::npos)
        return;

    if (cache.find({stripe, pattern}) != cache.end()) {
        sum += cache[{stripe, pattern}];
        return;
    }

    if (pattern.find(stripe) == 0) {
        auto new_pattern = pattern.substr(stripe.size());
        if (new_pattern.empty()) {
            sum++;

            return;
        }
        for (const auto& next_stripe : possible_stripes) {
            match_design_and_count(next_stripe, new_pattern, possible_stripes, sum, cache);
        }
    }
    cache[{stripe, pattern}] = sum-starting_sum;
}

AOC_DAY(Day19_2){
    std::string line;
    std::size_t sum = 0;


    getline(cin, line);
    std::stringstream ss(line);

    std::vector<std::string> stripes;
    std::string stripe;
    while(getline(ss, stripe, ',')) {
        stripe.erase(std::remove(stripe.begin(), stripe.end(), ' '), stripe.end());
        stripes.push_back(stripe);
    }


    std::vector<std::string> patterns;
    while (getline(cin,line)) {
        if (line.empty())
            continue;
        patterns.push_back(line);
    }


    for (const auto& pattern : patterns) {
        std::vector<std::string> possible_stripes;
        for (auto& stripe : stripes) {
            // check if stripe is contained in pattern
            if (pattern.find(stripe) != std::string::npos) {
                possible_stripes.push_back(stripe);
            }
        }
        std::map<std::pair<std::string, std::string>, std::size_t> cache;
        for (auto& stripe : stripes) {
            match_design_and_count(stripe, pattern, possible_stripes, sum, cache);
        }
    }


    return std::to_string(sum);
}