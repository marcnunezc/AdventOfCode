bool load_workflow(std::string workflow, std::unordered_map<char, int>& values, std::unordered_map<std::string, std::vector<std::string>>& workflows) {
    if (workflow.compare("A") == 0)
        return true;
    else if (workflow.compare("R") == 0)
        return false;

    auto instruction_list = workflows[workflow];
    for (auto& instruction : instruction_list) {
        auto pos = instruction.find(':');
        if (pos != string::npos) {
            auto comparison = instruction.substr(0, pos);
            auto number = stoi(instruction.substr(2, pos));
            if (comparison.find('<') != string::npos) {
                if (values[comparison[0]] < number)
                    return load_workflow(instruction.substr(pos+1), values, workflows);
                else
                    continue;
            } else {
                if (values[comparison[0]] > number)
                    return load_workflow(instruction.substr(pos+1), values, workflows);
                else
                    continue;
            }
        } else {
            return load_workflow(instruction, values, workflows);
        }
    }
    return false;
}

AOC_DAY(Day19_1){
    std::unordered_map<std::string, std::vector<std::string>> workflows;
    std::string line;
    size_t sum = 0;
    while(getline(cin,line)) {
        if (line.empty())
            break;
        auto hash = line.substr(0, line.find('{'));
        line.pop_back();
        std::stringstream ss(line.substr(line.find('{')+1));
        std::string instruction;
        std::vector<std::string> instruction_list;
        while (getline(ss, instruction, ',')) {
            instruction_list.push_back(instruction);
        }
        workflows[hash] = instruction_list;
    }
    while(getline(cin,line)) {
        int local_sum = 0;
        std::stringstream ss(line.substr(1, line.size()-2));
        std::unordered_map<char, int> values;
        std::string init_value;
        while (getline(ss, init_value, ',')) {
            values[init_value[0]] = stoi(init_value.substr(init_value.find('=')+1));
            local_sum += values[init_value[0]];
        }
        if (load_workflow("in", values, workflows)) {
            sum += local_sum;
        }
    }

    return std::to_string(sum);
}

AOC_DAY(Day19_2){
    size_t sum = 0;

    return std::to_string(sum);
}