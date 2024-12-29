
AOC_DAY(Day23_1) {

    std::string line;
    std::size_t sum = 0;
    std::map<std::string, std::vector<std::string>> connections;
    std::set<std::string> chief_connections;

    while(getline(cin,line)) {

        std::string cpu1 = line.substr(0,line.find('-'));
        std::string cpu2 = line.substr(line.find('-')+1);

        connections[cpu1].push_back(cpu2);
        connections[cpu2].push_back(cpu1);

        if (cpu1[0] == 't') {
            chief_connections.insert(cpu1);
        }
        if (cpu2[0] == 't') {
            chief_connections.insert(cpu2);
        }

    }
    std::set<std::set<std::string>> triads_set;

    for (auto chief : chief_connections) {

        for (auto chief_conn : connections[chief]) {
            auto sub_chief_connections = connections[chief_conn];
            for (auto sub_chief_conn : sub_chief_connections) {
                if (std::find(connections[chief].begin(), connections[chief].end(), sub_chief_conn) != connections[chief].end()) {
                    std::set<string> triad;
                    triad.insert(chief);
                    triad.insert(chief_conn);
                    triad.insert(sub_chief_conn);
                    triads_set.insert(triad);
                }
            }
        }
    }

    return std::to_string(triads_set.size());
}

AOC_DAY(Day23_2) {
    std::string line;
    std::size_t sum = 0;
    std::map<std::string, std::vector<std::string>> connections;
    std::set<std::string> chief_connections;

    while(getline(cin,line)) {

        std::string cpu1 = line.substr(0,line.find('-'));
        std::string cpu2 = line.substr(line.find('-')+1);

        connections[cpu1].push_back(cpu2);
        connections[cpu2].push_back(cpu1);

        if (cpu1[0] == 't') {
            chief_connections.insert(cpu1);
        }
        if (cpu2[0] == 't') {
            chief_connections.insert(cpu2);
        }

    }
    std::set<std::string> max_set;

    for (const auto& [chief, chief_connections] : connections) {

        for (size_t i = 0; i < chief_connections.size(); i++)
        {
            auto chief_conn = chief_connections[i];
            std::set<std::string> candidate_set;
            candidate_set.insert(chief);
            candidate_set.insert(chief_conn);
            for (size_t j = 0; j < chief_connections.size(); j++) {
                if (i == j) continue;
                auto other_conn = chief_connections[j];
                // check if other conn is also in the rest of the connections vector in candidate set
                bool to_insert = true;
                for (auto current_candidate : candidate_set) {
                    if (std::find(connections[current_candidate].begin(), connections[current_candidate].end(), other_conn) == connections[current_candidate].end()) {
                        to_insert = false;
                        break;
                    }
                }

                if (to_insert) {
                    candidate_set.insert(other_conn);
                }
            }

            if (candidate_set.size() > max_set.size()) {
                max_set = candidate_set;
            }
        }
    }
    std::string result;
    size_t count = 0;
    for (auto cpu : max_set) {
        result += cpu;
        if (count < max_set.size() - 1) {
            result += ",";
        }
        count++;
    }
    return result;
}