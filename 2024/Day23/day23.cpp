
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

    for (auto chief_conn : chief_connections) {

        for (auto sub_conn : connections[chief_conn]) {
            auto subsub_connections = connections[sub_conn];
            for (auto subsub_conn : subsub_connections) {
                if (std::find(connections[chief_conn].begin(), connections[chief_conn].end(), subsub_conn) != connections[chief_conn].end()) {
                    std::set<string> triad;
                    triad.insert(chief_conn);
                    triad.insert(sub_conn);
                    triad.insert(subsub_conn);
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

    return "0";
}