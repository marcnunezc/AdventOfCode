AOC_DAY(Day24_1) {
    std::string line;
    std::size_t sum = 0;

    std::map<std::string, bool> gates;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> operands_list;


    std::set<std::string> z_set;
    while(getline(cin,line)) {
        if (line.empty()) {
            break;
        }
        std::string gate = line.substr(0,line.find(':'));
        bool value = (bool) std::stoi(line.substr(line.find(':')+2));
        gates[gate] = value;
        cout << "Gate: " << gate << " Value: " << value << endl;
    }

    while(getline(cin,line)) {
        std::stringstream ss(line);
        std::string oper1, bool_operator, oper2, arrow, result;

        ss >> oper1 >> bool_operator >> oper2 >> arrow >> result;
        if (result.find('z') != std::string::npos) {
            z_set.insert(result);
        }

        operands_list.push_back(std::make_tuple(oper1, bool_operator, oper2, result));
    }
    for (size_t i = 0; i < operands_list.size(); i++) {
        auto [oper1, bool_operator, oper2, result] = operands_list[i];
        cout << oper1 << " " <<bool_operator << " "<<oper2 << " " << result << endl;
        cout << gates[oper1] << " " << gates[oper2] << endl;
        if (bool_operator == "AND") {
            gates[result] = gates[oper1] & gates[oper2];
        } else if (bool_operator == "OR") {
            gates[result] = gates[oper1] | gates[oper2];
        } else if (bool_operator == "XOR") {
            gates[result] = gates[oper1] != gates[oper2];
        }
        cout << "Result: " << gates[result] << endl;
    }
    for (auto z : z_set) {
        cout << z << " " << gates[z] << endl;
    }

    return std::to_string(sum);
}


AOC_DAY(Day24_2) {
    std::size_t sum = 0;
    return std::to_string(sum);
}