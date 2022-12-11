struct Monkey {
    int id, id_true, id_false, test, operation_number, item_count=0;
    char operation_string[64];
    char operation;
    std::deque<unsigned long int> items;
    std::deque<std::unordered_map<int,int>> item_map;
};
std::vector<Monkey> get_monkey_list() {
    std::string line;
    std::vector<Monkey> monkey_list;
    while(getline(cin, line)) {
        if (line.find("Monkey") != string::npos) {
            Monkey monkey;
            sscanf(line.c_str(), "Monkey %i:", &monkey.id);

            getline(cin, line);
            stringstream ss(line);
            string tmp;
            int found;
            while (!ss.eof()) {
                ss >> tmp;
                if (stringstream(tmp) >> found)
                    monkey.items.push_back(found);
            }

            getline(cin,line);
            sscanf(line.c_str(), "  Operation: new = old %c %s", &monkey.operation, &monkey.operation_string[0]);
            if (isdigit(monkey.operation_string[0]))
                monkey.operation_number = std::stoi(monkey.operation_string);
            else
                monkey.operation_number = -1;

            getline(cin,line);
            sscanf(line.c_str(), "  Test: divisible by %i", &monkey.test);

            getline(cin,line);
            sscanf(line.c_str(), "    If true: throw to monkey %i", &monkey.id_true);

            getline(cin,line);
            sscanf(line.c_str(), "    If false: throw to monkey %i", &monkey.id_false);

            monkey_list.push_back(monkey);
        }
    }
    return monkey_list;
}

unsigned long int compute_monkey_business(std::vector<Monkey> monkey_list) {
    std::vector<unsigned long int> counts_vector;
    for (auto& monkey : monkey_list) {
        counts_vector.push_back(monkey.item_count);
    }
    sort(counts_vector.begin(), counts_vector.end(), greater<unsigned long>());

    return counts_vector[0]*counts_vector[1];
}

AOC_DAY(Day11_1) {

    auto monkey_list = get_monkey_list();

    const int rounds = 20;
    for (int i = 0; i<rounds; i++) {

        for (int j = 0; j<monkey_list.size(); j++) {
            Monkey& monkey =monkey_list[j];

            while (monkey.items.size() > 0) {
                monkey.item_count++;
                auto item = monkey.items.front();
                monkey.items.pop_front();
                if (monkey.operation_number == -1)
                    item = item*item;
                else {
                    if (monkey.operation == '+')
                        item += monkey.operation_number;
                    else
                        item *= monkey.operation_number;
                }
                item = item/3;
                if (item % monkey.test == 0)
                    monkey_list[monkey.id_true].items.push_back(item);
                else
                    monkey_list[monkey.id_false].items.push_back(item);
            }
        }
    }
    return std::to_string(compute_monkey_business(monkey_list));
}

AOC_DAY(Day11_2) {
    std::string line;
    std::vector<Monkey> monkey_list = get_monkey_list();

    std::vector<int> test_list;
    for (auto& monkey : monkey_list) {
        test_list.push_back(monkey.test);
    }

    for (auto& monkey : monkey_list) {
        for (auto item : monkey.items) {
            std::unordered_map<int,int> new_item;
            for (auto test : test_list) {
                new_item[test] = item % test;
            }
            monkey.item_map.push_back(new_item);
        }
    }

    const int rounds = 10000;
    for (int i = 0; i<rounds; i++) {
        for (int j = 0; j<monkey_list.size(); j++) {
            Monkey& monkey = monkey_list[j];

            while (monkey.item_map.size() > 0) {
                monkey.item_count++;
                auto factor_map = monkey.item_map.front();
                monkey.item_map.pop_front();
                if (monkey.operation_number == -1) {
                    for (auto& [key, value] : factor_map) {
                        value = (value*value) % key;
                    }
                }
                else {
                    if (monkey.operation == '+') {
                        for (auto& [key, value] : factor_map) {
                            value = (value+monkey.operation_number) % key;
                        }
                    }
                    else {
                        for (auto& [key, value] : factor_map) {
                            value = (value*monkey.operation_number) % key;
                        }
                    }
                }
                if (factor_map[monkey.test] == 0)
                    monkey_list[monkey.id_true].item_map.push_back(factor_map);
                else
                    monkey_list[monkey.id_false].item_map.push_back(factor_map);
            }
        }
    }

    return std::to_string(compute_monkey_business(monkey_list));
}


AOC_DAY(Day11_2b) {
    std::string line;
    std::vector<Monkey> monkey_list = get_monkey_list();

    int mcm=1;
    for (auto& monkey : monkey_list) {
        mcm*=monkey.test;
    }

    const int rounds = 10000;
    for (int i = 0; i<rounds; i++) {

        for (int j = 0; j<monkey_list.size(); j++) {
            Monkey& monkey =monkey_list[j];

            while (monkey.items.size() > 0) {
                monkey.item_count++;
                auto item = monkey.items.front();
                monkey.items.pop_front();
                if (monkey.operation_number == -1)
                    item = item*item;
                else {
                    if (monkey.operation == '+')
                        item += monkey.operation_number;
                    else
                        item *= monkey.operation_number;
                }
                item = item % mcm;
                if (item % monkey.test == 0)
                    monkey_list[monkey.id_true].items.push_back(item);
                else
                    monkey_list[monkey.id_false].items.push_back(item);
            }
        }
    }
    return std::to_string(compute_monkey_business(monkey_list));
}
