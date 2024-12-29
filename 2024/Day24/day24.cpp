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

    // solving part 2 by reconstructing the bit sum. When the next step in the sum is not found in the list of operations, the conflicting wires are added to the list.
    std::string line;
    std::size_t sum = 0;

    std::map<std::string, bool> gates;
    std::set<std::string> registered_gates;
    std::vector<std::tuple<std::string, std::string, std::string>> operands_list;
    std::map<std::tuple<std::string, std::string, std::string>, std::string> operands_map;
    std::vector<std::string> results_list;


    std::set<std::string> x_set;
    std::set<std::string> y_set;
    std::set<std::string> z_set;
    while(getline(cin,line)) {
        if (line.empty()) {
            break;
        }
        std::string gate = line.substr(0,line.find(':'));
        bool value = (bool) std::stoi(line.substr(line.find(':')+2));
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
        operands_list.push_back(std::make_tuple(oper1, bool_operator, oper2));
        results_list.push_back(result);
        if (oper1 < oper2)
            operands_map[std::make_tuple(oper1, bool_operator, oper2)] = result;
        else
            operands_map[std::make_tuple(oper2, bool_operator, oper1)] = result;
    }


    bool carry_bit = 0;
    std::string carry_str;
    std::set<string> wrong_set;
    std::string previous_carry;
    for (size_t i_bit = 0; i_bit < z_set.size()-1; i_bit++) {
        std::string bit_str=std::to_string(i_bit);
        if (bit_str.size() == 1)
            bit_str = "0"+bit_str;

        std::string x_str = "x"+bit_str;
        std::string y_str = "y"+bit_str;
        std::string z_str = "z"+bit_str;

        auto xor_oper = std::make_tuple(x_str, "XOR", y_str);
        auto and_oper = std::make_tuple(x_str, "AND", y_str);

        if (operands_map.find(xor_oper) == operands_map.end() || operands_map.find(and_oper) == operands_map.end())
        {
            cout << " fail " << x_str << " " <<  y_str << endl;
            break;
        }

        auto xor_result = operands_map[xor_oper];
        auto and_result = operands_map[and_oper];
        gates[xor_result] = gates[x_str] != gates[y_str];
        gates[and_result] = gates[x_str] & gates[y_str];
        if (i_bit > 0) {
            auto carry_and_oper = std::make_tuple(xor_result, "AND", carry_str);
            if (xor_result > carry_str)
                carry_and_oper = std::make_tuple(carry_str, "AND", xor_result);

            if (operands_map.find(carry_and_oper) == operands_map.end())
            {
                std::string wrong_oper;
                std::string wrong_xor;
                std::string new_oper;
                for (size_t i = 0; i < operands_list.size(); i++) {
                    auto [oper1, bool_operator, oper2] = operands_list[i];
                    if (oper1 == carry_str && bool_operator == "AND")
                    {
                        new_oper = oper1;
                        wrong_oper = oper2;
                        wrong_xor = xor_result;
                        break;
                    }
                    if (oper1 == xor_result && bool_operator == "AND")
                    {
                        new_oper = oper1;
                        wrong_oper = oper2;
                        wrong_xor = carry_str;
                        break;
                    }
                    if (oper2 == carry_str && bool_operator == "AND")
                    {
                        new_oper = oper2;
                        wrong_oper = oper1;
                        wrong_xor = xor_result;
                        break;
                    }
                    if (oper2 == xor_result && bool_operator == "AND")
                    {
                        new_oper = oper2;
                        wrong_oper = oper1;
                        wrong_xor = carry_str;
                        break;
                    }
                }
                wrong_set.insert(wrong_oper);
                wrong_set.insert(wrong_xor);
                carry_and_oper = std::make_tuple(new_oper, "AND", wrong_oper);
                if (new_oper > wrong_oper)
                    carry_and_oper = std::make_tuple(wrong_oper, "AND", new_oper);

            }
            auto carry_and_oper_result = operands_map[carry_and_oper];
            gates[carry_and_oper_result] = gates[carry_str] & gates[xor_result];
            gates[z_str] = gates[carry_str] != gates[xor_result];

            previous_carry = carry_and_oper_result;
            auto carry_or_oper = std::make_tuple(previous_carry, "OR", and_result);
            if (previous_carry > and_result)
                carry_or_oper = std::make_tuple(and_result, "OR", previous_carry);

            if (operands_map.find(carry_or_oper) == operands_map.end())
            {
                std::string wrong_oper;
                std::string wrong_and;
                std::string new_oper;
                for (size_t i = 0; i < operands_list.size(); i++) {
                    auto [oper1, bool_operator, oper2] = operands_list[i];
                    if (oper1 == previous_carry && bool_operator == "OR")
                    {
                        new_oper = oper1;
                        wrong_oper = oper2;
                        wrong_and = and_result;
                        break;
                    }
                    if (oper1 == and_result && bool_operator == "OR")
                    {
                        new_oper = oper1;
                        wrong_oper = oper2;
                        wrong_and = previous_carry;
                        break;
                    }
                    if (oper2 == previous_carry && bool_operator == "OR")
                    {
                        new_oper = oper2;
                        wrong_oper = oper1;
                        wrong_and = and_result;
                        break;
                    }
                    if (oper2 == and_result && bool_operator == "OR")
                    {
                        new_oper = oper2;
                        wrong_oper = oper1;
                        wrong_and = previous_carry;
                        break;
                    }
                }
                wrong_set.insert(wrong_oper);
                wrong_set.insert(wrong_and);
                carry_or_oper = std::make_tuple(new_oper, "OR", wrong_oper);
                if (new_oper > wrong_oper)
                    carry_or_oper = std::make_tuple(wrong_oper, "OR", new_oper);
            }

            auto carry_or_oper_result = operands_map[carry_or_oper];
            gates[carry_or_oper_result] = gates[and_result] || gates[previous_carry];
            carry_str = carry_or_oper_result;

        } else {
            carry_str = and_result;
        }
    }
    std::stringstream ss;
    for (auto z : wrong_set) {
        ss << z << ",";
    }
    return ss.str().substr(0,ss.str().size()-1);
}