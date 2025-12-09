struct Box {
    long x,y,z;
};


double compute_distance(Box& a, Box& b) {
    auto dx = a.x - b.x;
    auto dy = a.y - b.y;
    auto dz = a.z - b.z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

AOC_DAY(Day08_1) {

    std::size_t sum = 0;
    std::string line;

    std::vector<Box> junction_boxes;
    while (getline(cin, line)) {
        Box box;
        sscanf(line.c_str(),"%ld,%ld,%ld", &box.x, &box.y, &box.z);
        junction_boxes.push_back(box);
    }
    std::map<std::pair<size_t, size_t>, double> distance_map;

    for (int i = 0; i<junction_boxes.size(); i++) {
        auto first_box = junction_boxes[i];
        for (int j = i+1; j<junction_boxes.size(); j++) {
            auto second_box = junction_boxes[j];
            distance_map[{i,j}] = compute_distance(first_box, second_box);
        }
    }
    std::vector<std::set<int>> circuit_list;

    int number_of_connections = 1000;
    for (int i = 0; i<number_of_connections; i++) {
        auto it = std::min_element(distance_map.begin(),distance_map.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
            }
        );
        auto min_pair = it->first;
        double min_dist = it->second;

        std::vector<size_t> circuits_matching;

        for (size_t i = 0; i < circuit_list.size(); ++i) {
            auto& circuit = circuit_list[i];
            if (circuit.find(min_pair.first) != circuit.end() ||
                circuit.find(min_pair.second) != circuit.end()) {
                circuits_matching.push_back(i);
            }
        }

        std::set<int> new_circuit;
        new_circuit.insert(min_pair.first);
        new_circuit.insert(min_pair.second);
        for (auto& i_circuit : circuits_matching) {
            auto circuit = circuit_list[i_circuit];
            new_circuit.insert(circuit.begin(), circuit.end());
        }
        circuit_list.push_back(new_circuit);

        for (auto it = circuits_matching.rbegin(); it != circuits_matching.rend(); ++it) {
            circuit_list.erase(circuit_list.begin() + *it);
        }
        distance_map.erase(it);
    }
    size_t product = 1;
    std::vector<size_t> sizes;

    for (auto& circuit : circuit_list) {
        sizes.push_back(circuit.size());
    }
    std::sort(sizes.begin(), sizes.end(), std::greater<size_t>());

    product = sizes[0]*sizes[1]*sizes[2];

    return std::to_string(product);
}



AOC_DAY(Day08_2) {
    std::size_t sum = 0;
    std::string line;

    std::vector<Box> junction_boxes;
    while (getline(cin, line)) {
        Box box;
        sscanf(line.c_str(),"%ld,%ld,%ld", &box.x, &box.y, &box.z);
        junction_boxes.push_back(box);
    }
    std::map<std::pair<size_t, size_t>, double> distance_map;

    for (int i = 0; i<junction_boxes.size(); i++) {
        auto first_box = junction_boxes[i];
        for (int j = i+1; j<junction_boxes.size(); j++) {
            auto second_box = junction_boxes[j];
            distance_map[{i,j}] = compute_distance(first_box, second_box);
        }
    }
    std::vector<std::set<int>> circuit_list;
    for (int i =0; i<junction_boxes.size(); i++) {
        circuit_list.push_back({i});
    }

    std::pair<size_t, size_t> min_pair;
    while(circuit_list.size() != 1) {
        auto it = std::min_element(distance_map.begin(),distance_map.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
            }
        );
        min_pair = it->first;
        double min_dist = it->second;

        std::vector<size_t> circuits_matching;

        for (size_t i = 0; i < circuit_list.size(); ++i) {
            auto& circuit = circuit_list[i];
            if (circuit.find(min_pair.first) != circuit.end() ||
                circuit.find(min_pair.second) != circuit.end()) {
                circuits_matching.push_back(i);
            }
        }

        std::set<int> new_circuit;
        new_circuit.insert(min_pair.first);
        new_circuit.insert(min_pair.second);
        for (auto& i_circuit : circuits_matching) {
            auto circuit = circuit_list[i_circuit];
            new_circuit.insert(circuit.begin(), circuit.end());
        }
        circuit_list.push_back(new_circuit);

        for (auto it = circuits_matching.rbegin(); it != circuits_matching.rend(); ++it) {
            circuit_list.erase(circuit_list.begin() + *it);
        }

        distance_map.erase(it);
    }
    size_t product = junction_boxes[min_pair.first].x*junction_boxes[min_pair.second].x;

    return std::to_string(product);
}
