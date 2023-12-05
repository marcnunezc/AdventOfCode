
typedef long int IntType;
AOC_DAY(Day05_1){
    std::string line;
    std::vector<IntType> seeds;
    std::vector<std::map<std::pair<IntType,IntType>, std::pair<IntType,IntType>>> map_list;
    getline(cin, line);
    std::stringstream ss(line.substr(line.find(':')+1));
    IntType seed;
    while(ss >> seed) {
        seeds.push_back(seed);
    }
    std::map<std::pair<IntType,IntType>, std::pair<IntType,IntType>> aux_map;
    // store conversions in a vector of maps
    while(getline(cin, line)) {
        if (line.empty()) {
            if (!aux_map.empty())
                map_list.push_back(aux_map);
            continue;
        }
        if (line.find(":") != string::npos) {
            aux_map.clear();
        } else {
            IntType source, destination,length;
            std::stringstream ss_line(line);
            ss_line >> destination >> source >> length;
            aux_map[{source, source+length-1}] = {destination, destination+length-1};
        }
    }
    map_list.push_back(aux_map);

    IntType min_location = std::numeric_limits<IntType>::max();
    //perform conversion of each seed and find minimum
    for (auto& seed : seeds) {
        IntType propagated_number = seed;
        for (auto& map : map_list) {
            for (auto& keys_values : map) {
                auto& source = keys_values.first;
                auto& dest = keys_values.second;
                if (source.first <= propagated_number && propagated_number <= source.second) {
                    propagated_number = dest.first + (propagated_number - source.first);
                    break;

                }
            }
        }
        min_location = min(min_location, propagated_number);
    }

    return std::to_string(min_location);
}

bool is_in_range(IntType value, IntType low, IntType high) {
    return low <= value && value <= high;
}

AOC_DAY(Day05_2){
    std::string line;
    std::vector<std::pair<IntType, IntType>> seeds;
    std::vector<std::map<std::pair<IntType,IntType>, std::pair<IntType,IntType>>> map_list;
    getline(cin, line);
    std::stringstream ss(line.substr(line.find(':')+1));
    IntType seed;
    IntType range;
    while(ss >> seed) {
        ss >> range;
        seeds.push_back({seed, seed+range-1});
    }
    std::map<std::pair<IntType,IntType>, std::pair<IntType,IntType>> aux_map;
    while(getline(cin, line)) {
        if (line.empty()) {
            if (!aux_map.empty())
                map_list.push_back(aux_map);
            continue;
        }

        if (line.find(":") != string::npos) {
            aux_map.clear();
        } else {
            IntType source, destination,length;
            std::stringstream ss_line(line);
            ss_line >> destination >> source >> length;
            aux_map[{source, source+length-1}] = {destination, destination+length-1};
        }
    };
    map_list.push_back(aux_map);

    IntType min_location = std::numeric_limits<IntType>::max();
    int i = 0;

    for ( auto& map : map_list) {
        for ( auto& keys_values : map) {
            auto& keys = keys_values.first;

            std::vector<std::pair<IntType, IntType>> aux_seeds;
            // split ranges in subranges
            for (auto& seed_range : seeds) {
                auto& low = seed_range.first;
                auto& high = seed_range.second;
                auto& keys = keys_values.first;
                if (is_in_range(keys.first, low, high) && is_in_range(keys.second, low, high)) {

                    if (low != keys.first){
                        aux_seeds.push_back({low, keys.first-1});
                    }
                    aux_seeds.push_back({keys.first, keys.second});
                    if (high != keys.second){
                        aux_seeds.push_back({keys.second+1, high});
                    }
                }
                else if (is_in_range(keys.first, low, high)) {
                    if (low != keys.first) {
                        aux_seeds.push_back({low, keys.first-1});
                    }
                    aux_seeds.push_back({keys.first, high});
                }
                else if (is_in_range(keys.second, low, high)) {
                    aux_seeds.push_back({low, keys.second});
                    if (high != keys.second)
                        aux_seeds.push_back({keys.second+1, high});
                } else{
                    aux_seeds.push_back({low, high});
                }
            }
            seeds=aux_seeds;
        }

        //perform conversion of each range
        std::vector<std::pair<IntType, IntType>> aux_seeds;
        for (auto& seed_range : seeds) {
            auto low = seed_range.first;
            auto high = seed_range.second;
            IntType new_low = low;
            IntType new_high = high;
            for ( auto& keys_values : map) {
                auto keys = keys_values.first;
                auto values = keys_values.second;
                if (is_in_range(low, keys.first, keys.second) && is_in_range(high, keys.first, keys.second)) {
                        new_low = values.first + (low - keys.first);
                        new_high = values.first + (high - keys.first);
                        break;
                }
            }
            aux_seeds.push_back({new_low,new_high});
        }
        //start again with new ranges
        seeds = aux_seeds;
    }

    for (auto& seed_range : seeds) {
        auto& low = seed_range.first;
        min_location = min(min_location, low);
    }

    return std::to_string(min_location);
}
