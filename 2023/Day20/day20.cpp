enum MOD_TYPE {
    broadcaster,
    flipflop,
    conjuction
};
enum PULSE {
    low=0,
    high=1
};

AOC_DAY(Day20_1){
    std::string line;
    size_t sum = 0;
    std::unordered_map<string, MOD_TYPE> module_types;
    std::unordered_map<string, PULSE> module_state;
    std::unordered_map<string, std::vector<string>> network;
    std::unordered_map<string, bool> flipflop_state;
    std::vector<string> list_of_conjunctions;
    std::unordered_map<string, std::vector<string>> conjuction_to_inputs;
    size_t number_of_pulses = 1000;
    while (getline(cin,line)) {
        std::string label = (line[0] == '%' || line[0] == '&') ? line.substr(1, line.find(' ')) : line.substr(0, line.find(' '));
        label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
        std::vector<string> children;
        std::stringstream ss(line.substr(line.find('>')+2));
        std::string child;
        while(getline(ss, child, ',')) {
            child.erase(std::remove_if(child.begin(), child.end(), ::isspace), child.end());
            children.push_back(child);
        }
        network[label] = children;
        if (line[0] == '%') {
            module_types[label] = MOD_TYPE::flipflop;
            flipflop_state[label] = false;
        } else if (line[0] == '&') {
            module_types[label] = MOD_TYPE::conjuction;
            list_of_conjunctions.push_back(label);
        } else {
            module_types[label] = MOD_TYPE::broadcaster;
        }
        module_state[label] = PULSE::low;
    }

    for (auto& conj : list_of_conjunctions) {
        std::vector<string> input_list;
        for (auto& values : network) {
            for (auto& input : values.second) {
                if (conj.compare(input) == 0) {
                    input_list.push_back(values.first);
                }
            }
        }
        conjuction_to_inputs[conj]=input_list;
    }
    std::vector<size_t> pulse_count(2, 0);
    std::function<void(std::vector<std::pair<string,PULSE>>)> send_pulse;
    send_pulse = [&] (std::vector<std::pair<std::string, PULSE>> list_of_commands) {
        if (list_of_commands.empty())
            return;
        std::vector<std::pair<std::string, PULSE>> next_pulses;
        for (auto current_command : list_of_commands) {
            auto source = current_command.first;
            auto received_pulse = current_command.second;
            auto& children = network[source];
            for (auto& child : children) {
                pulse_count[received_pulse]++;
                if (module_types[child] == MOD_TYPE::flipflop) {
                    if (received_pulse == PULSE::low) {
                        if (flipflop_state[child]) {
                            flipflop_state[child] = false;
                            next_pulses.push_back({child, PULSE::low});
                        } else {
                            flipflop_state[child] = true;
                            next_pulses.push_back({child, PULSE::high});
                        }
                    }
                }
                else if (module_types[child] == MOD_TYPE::conjuction) {
                    module_state[source]=received_pulse;
                    bool all_high = true;
                    for (auto& conj_input : conjuction_to_inputs[child]) {
                        if (module_state[conj_input] == PULSE::low) {
                            all_high = false;
                            break;
                        }
                    }
                    if (all_high)
                        next_pulses.push_back({child, PULSE::low});
                    else
                        next_pulses.push_back({child, PULSE::high});
                }
            }
        }
        send_pulse(next_pulses);
    };

    for (size_t i=0; i<number_of_pulses; i++) {
        pulse_count[PULSE::low]++;
        send_pulse(std::vector<std::pair<std::string, PULSE>>({{"broadcaster", PULSE::low}}));
    }
    return std::to_string(pulse_count[0]*pulse_count[1]);
}

AOC_DAY(Day20_2){
    std::string line;
    size_t sum = 0;
    std::unordered_map<string, MOD_TYPE> module_types;
    std::unordered_map<string, PULSE> module_state;
    std::unordered_map<string, std::vector<string>> network;
    std::unordered_map<string, bool> flipflop_state;
    std::vector<string> list_of_conjunctions;
    std::unordered_map<string, std::vector<string>> conjuction_to_inputs;
    size_t number_of_pulses = 0;
    std::string rx_parent;
    while (getline(cin,line)) {
        std::string label = (line[0] == '%' || line[0] == '&') ? line.substr(1, line.find(' ')) : line.substr(0, line.find(' '));
        label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
        std::vector<string> children;
        std::stringstream ss(line.substr(line.find('>')+2));
        std::string child;
        while(getline(ss, child, ',')) {
            if (child.compare("rx")==0) {
                rx_parent = label;
            }
            child.erase(std::remove_if(child.begin(), child.end(), ::isspace), child.end());
            children.push_back(child);
        }
        network[label] = children;
        if (line[0] == '%') {
            module_types[label] = MOD_TYPE::flipflop;
            flipflop_state[label] = false;
        } else if (line[0] == '&') {
            module_types[label] = MOD_TYPE::conjuction;
            list_of_conjunctions.push_back(label);
        } else {
            module_types[label] = MOD_TYPE::broadcaster;
        }
        module_state[label] = PULSE::low;
    }

    for (auto& conj : list_of_conjunctions) {
        std::vector<string> input_list;
        for (auto& values : network) {
            for (auto& input : values.second) {
                if (conj.compare(input) == 0) {
                    input_list.push_back(values.first);
                }
            }
        }
        conjuction_to_inputs[conj]=input_list;
    }
    std::vector<size_t> pulse_count(2, 0);
    size_t count_rx = 0;
    std::function<void(std::vector<std::pair<string,PULSE>>)> send_pulse;
    send_pulse = [&] (std::vector<std::pair<std::string, PULSE>> list_of_commands) {
        if (list_of_commands.empty())
            return;
        std::vector<std::pair<std::string, PULSE>> next_pulses;
        for (auto current_command : list_of_commands) {
            auto source = current_command.first;
            auto received_pulse = current_command.second;
            auto& children = network[source];
            for (auto& child : children) {
                pulse_count[received_pulse]++;
                if (module_types[child] == MOD_TYPE::flipflop) {
                    if (received_pulse == PULSE::low) {
                        if (flipflop_state[child]) {
                            flipflop_state[child] = false;
                            next_pulses.push_back({child, PULSE::low});
                        } else {
                            flipflop_state[child] = true;
                            next_pulses.push_back({child, PULSE::high});
                        }
                    }
                }
                else if (module_types[child] == MOD_TYPE::conjuction) {
                    module_state[source]=received_pulse;
                    bool all_high = true;
                    for (auto& conj_input : conjuction_to_inputs[child]) {
                        if (module_state[conj_input] == PULSE::low) {
                            all_high = false;
                            break;
                        }
                    }
                    if (all_high)
                        next_pulses.push_back({child, PULSE::low});
                    else
                        next_pulses.push_back({child, PULSE::high});
                }
            }
        }
        send_pulse(next_pulses);
    };

    std::unordered_map<string, size_t> first_high_occurance;
    std::unordered_map<string, size_t> end_of_first_high_occurance;

    // rx depends on 4 conjuctions -> all need to be HIGH to send a low to rx
    // these depend on 4 conjuctions that need to be LOW to send a high to each conjunction
    // and finally these depend on flipfops that all need to have HIGH state
    // in order to send a low signal to the conjutions. The pattern to get all flipflop to HIGH
    // is repeted by groups of flipflops, each repeating an odd number of times. The solution is the
    // lcm of every size of the pattern.
    for (auto level : conjuction_to_inputs[rx_parent]) {
        for (auto level2 : conjuction_to_inputs[level])
            for (auto level3 : conjuction_to_inputs[level2]) {
                first_high_occurance[level3]=0;
                end_of_first_high_occurance[level3]=0;
            }
    }

    while (std::any_of(end_of_first_high_occurance.begin(), end_of_first_high_occurance.end(), [] (const auto m) { return m.second == 0; })) {
        number_of_pulses++;
        count_rx = 0;
        pulse_count[PULSE::low]++;
        send_pulse(std::vector<std::pair<std::string, PULSE>>({{"broadcaster", PULSE::low}}));
        for (auto input : conjuction_to_inputs[rx_parent]) {
            for (auto input2 : conjuction_to_inputs[input]) {
                for (auto input3 : conjuction_to_inputs[input2]) {
                    if(module_state[input3] &&  first_high_occurance[input3] == 0) {
                        first_high_occurance[input3]=number_of_pulses;
                    } else if (first_high_occurance[input3] != 0 && !module_state[input3] &&  end_of_first_high_occurance[input3] == 0){
                        end_of_first_high_occurance[input3]=number_of_pulses;
                    }
                }
            }
        }
    }
    std::vector<size_t> appearances_vector;
    for (auto conj : conjuction_to_inputs[rx_parent]) {
        for (auto conj2 : conjuction_to_inputs[conj]) {
            for (auto flipflop3 : conjuction_to_inputs[conj2]) {
                if (end_of_first_high_occurance[flipflop3] % 2 == 1)
                    appearances_vector.push_back(end_of_first_high_occurance[flipflop3]);
            }
        }
    }

    return std::to_string(std::reduce(appearances_vector.begin(), appearances_vector.end(), 1L, std::lcm<IntType, IntType>));
}