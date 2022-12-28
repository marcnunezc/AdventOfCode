typedef long long int IntType;

IntType do_operation(IntType left, string oper, IntType right) {
    if (oper.compare("+") == 0)
        return left + right;
    else if (oper.compare("-")==0)
        return left - right;
    else if (oper.compare("*")==0)
        return left * right;
    else if (oper.compare("/")==0)
        return left / right;
    else
        return 0;
}

AOC_DAY(Day21_1) {
    std::string line;
    std::unordered_map<string, IntType> monkey_to_num;
    std::unordered_map<string,string> monkey_to_oper;
    int total_monkeys = 0;
    while(getline(cin, line)) {
        total_monkeys++;
        stringstream ss(line);
        std::string monkey;
        ss>>monkey;
        monkey = monkey.substr(0,4);
        std::string buf;
        ss>>buf;
        if (isdigit(buf[0]))
            monkey_to_num[monkey]=stoi(buf);
        else {
            monkey_to_oper[monkey] = ss.str().substr(6);
        }
    }

    while (monkey_to_num.size() < total_monkeys) {
        for (auto it=monkey_to_oper.begin(); it!=monkey_to_oper.end(); it++){
            stringstream ss(it->second);
            std::string left, oper, right;
            ss >> left >> oper >> right;
            if (monkey_to_num.find(left) != monkey_to_num.end() && monkey_to_num.find(right) != monkey_to_num.end())
                monkey_to_num[it->first]=do_operation(monkey_to_num[left], oper, monkey_to_num[right]);
        }
    }

    return std::to_string(monkey_to_num["root"]);
}

void fill_monkey_to_num(IntType human, std::unordered_map<string, IntType>& monkey_to_num, std::unordered_map<string,string> monkey_to_oper, int total_monkeys) {
    monkey_to_num["humn"]=human;
    while (monkey_to_num.size() < total_monkeys) {
        // cout << monkey_to_num.size() << endl;
        for (auto it=monkey_to_oper.begin(); it!=monkey_to_oper.end(); it++){
                stringstream ss(it->second);
                std::string left, oper, right;
                ss >> left >> oper >> right;
                if (monkey_to_num.find(left) != monkey_to_num.end() && monkey_to_num.find(right) != monkey_to_num.end())
                    monkey_to_num[it->first]=do_operation(monkey_to_num[left], oper, monkey_to_num[right]);
        }
    }
}

AOC_DAY(Day21_2) {

    std::string line;
    std::unordered_map<string, IntType> monkey_to_num;
    std::unordered_map<string,string> monkey_to_oper;
    int total_monkeys = 0;
    while(getline(cin, line)) {
        total_monkeys++;
        stringstream ss(line);
        std::string monkey;
        ss>>monkey;
        monkey = monkey.substr(0,4);
        std::string buf;
        ss>>buf;
        if (isdigit(buf[0]))
            monkey_to_num[monkey]=stoi(buf);
        else {
            monkey_to_oper[monkey] = ss.str().substr(6);
        }
    }
    stringstream ss_root(monkey_to_oper["root"]);
    std::string left_root, oper, right_root;
    ss_root >> left_root >> oper >> right_root;
    auto aux_monkey_to_num = monkey_to_num;
    IntType human = monkey_to_num["humn"];
    fill_monkey_to_num(human, aux_monkey_to_num, monkey_to_oper, total_monkeys);
    auto f = aux_monkey_to_num[left_root]-aux_monkey_to_num[right_root];
    auto f_old = f;
    aux_monkey_to_num = monkey_to_num;
    auto human_old = human;
    human += 10;
    fill_monkey_to_num(human, aux_monkey_to_num, monkey_to_oper, total_monkeys);
    double alpha = 0.8;
    while (aux_monkey_to_num[left_root] != aux_monkey_to_num[right_root]) {
        f = aux_monkey_to_num[left_root]-aux_monkey_to_num[right_root];
        auto derivative = (f-f_old) && (human - human_old) ? (double)(f-f_old) /(human - human_old) : (f<0)  - (f>0);

        f_old=f;
        human_old = human;
        human -= alpha*f/derivative;
        aux_monkey_to_num = monkey_to_num;
        fill_monkey_to_num(human, aux_monkey_to_num, monkey_to_oper, total_monkeys);
    }

    return std::to_string(human);
}