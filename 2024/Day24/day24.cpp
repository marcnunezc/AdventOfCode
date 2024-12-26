AOC_DAY(Day24_1) {
    std::string line;
    std::size_t sum = 0;

    std::map<std::string, bool> gates;
    std::set<std::string> registered_gates;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> operands_list;


    std::set<std::string> z_set;
    while(getline(cin,line)) {
        if (line.empty()) {
            break;
        }
        std::string gate = line.substr(0,line.find(':'));
        bool value = (bool) std::stoi(line.substr(line.find(':')+2));
        gates[gate] = value;
        registered_gates.insert(gate);
    }

    while(getline(cin,line)) {
        std::stringstream ss(line);
        std::string oper1, bool_operator, oper2, arrow, result;

        ss >> oper1 >> bool_operator >> oper2 >> arrow >> result;
        if (result.find('z') != std::string::npos) {
            z_set.insert(result);
        }
        registered_gates.insert(result);
        operands_list.push_back(std::make_tuple(oper1, bool_operator, oper2, result));
    }

    while (registered_gates.size() != gates.size()) {
        for (size_t i = 0; i < operands_list.size(); i++) {
            auto [oper1, bool_operator, oper2, result] = operands_list[i];
            if (gates.find(oper1) == gates.end() || gates.find(oper2) == gates.end() || gates.find(result) != gates.end()) {
                continue;
            }
            if (bool_operator == "AND") {
                gates[result] = gates[oper1] & gates[oper2];
            } else if (bool_operator == "OR") {
                gates[result] = gates[oper1] | gates[oper2];
            } else if (bool_operator == "XOR") {
                gates[result] = gates[oper1] != gates[oper2];
            }
        }
    }
    size_t bit_pos = 0;
    for (auto z : z_set) {
        sum +=  (size_t) gates[z] << std::stoi(z.substr(1));
    }

    return std::to_string(sum);
}


AOC_DAY(Day24_2) {
    std::string line;
    std::size_t sum = 0;

    std::map<std::string, bool> gates;
    std::set<std::string> registered_gates;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> operands_list;


    std::set<std::string> x_set;
    std::set<std::string> y_set;
    std::set<std::string> z_set;
    while(getline(cin,line)) {
        if (line.empty()) {
            break;
        }
        std::string gate = line.substr(0,line.find(':'));
        bool value = (bool) std::stoi(line.substr(line.find(':')+2));
        gates[gate] = value;
        registered_gates.insert(gate);
        if (gate.find('x') != std::string::npos) {
            x_set.insert(gate);
        } else if (gate.find('y') != std::string::npos) {
            y_set.insert(gate);
        }
    }

    while(getline(cin,line)) {
        std::stringstream ss(line);
        std::string oper1, bool_operator, oper2, arrow, result;

        ss >> oper1 >> bool_operator >> oper2 >> arrow >> result;
        if (result.find('z') != std::string::npos) {
            z_set.insert(result);
        }
        registered_gates.insert(result);
        operands_list.push_back(std::make_tuple(oper1, bool_operator, oper2, result));
    }
    cout << "operands size " <<  operands_list.size() << endl;
    while (registered_gates.size() != gates.size()) {
        for (size_t i = 0; i < operands_list.size(); i++) {
            auto [oper1, bool_operator, oper2, result] = operands_list[i];
            if (gates.find(oper1) == gates.end() || gates.find(oper2) == gates.end() || gates.find(result) != gates.end()) {
                continue;
            }
            if (bool_operator == "AND") {
                gates[result] = gates[oper1] & gates[oper2];
            } else if (bool_operator == "OR") {
                gates[result] = gates[oper1] | gates[oper2];
            } else if (bool_operator == "XOR") {
                gates[result] = gates[oper1] != gates[oper2];
            }
            cout << oper1 << " " << bool_operator << " " << oper2 << " " << gates[result] << endl;
        }
    }
    size_t bit_pos = 0;
    size_t target = 0;
    for (auto x : x_set) {
        cout << x << " " << gates[x] << endl;
        target +=  (size_t) gates[x] << std::stoi(x.substr(1));
    }

    for (auto y : y_set) {
        cout << y << " " << gates[y] << endl;
        target +=  (size_t) gates[y] << std::stoi(y.substr(1));
    }
    cout << "target " << target << endl;
    // print target as binary:
    std::set<string> wrong_z_set;
    for (auto z : z_set) {
        cout << z << " " << gates[z] << endl;
        cout << "shifting target " << target << " by " << std::stoi(z.substr(1)) << endl;
        cout << "result " << ((target >> std::stoi(z.substr(1))) & 1) << endl;
        if (gates[z] != ((target >> std::stoi(z.substr(1))) & 1)) {
            wrong_z_set.insert(z);
        }
    }

    bool found = true;
    while (found) {
        found = false;
        for (size_t i = 0; i < operands_list.size(); i++) {
            auto [oper1, bool_operator, oper2, result] = operands_list[i];
            if (wrong_z_set.find(result) != wrong_z_set.end()) {
                if (wrong_z_set.find(oper1) == wrong_z_set.end() || wrong_z_set.find(oper2) == wrong_z_set.end()) {
                    found = true;
                    wrong_z_set.insert(oper1);
                    wrong_z_set.insert(oper2);
                }
            }

        }
    }
    for (auto z : wrong_z_set) {
        cout << " wrong z " << z << endl;
    }
    cout << " wrong z size " << wrong_z_set.size() << endl;
    cout << " oper list size " << operands_list.size() << endl;
    for (auto z : z_set) {
        sum +=  (size_t) gates[z] << std::stoi(z.substr(1));
    }

    return std::to_string(sum);
}