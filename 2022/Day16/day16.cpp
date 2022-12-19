int compute_pressure(std::set<std::string> open_valves, std::map<std::string, int> flow_rate_map) {
    int pressure = 0;
    for (auto it = open_valves.begin(); it != open_valves.end(); it++) {
        pressure += flow_rate_map[*it];
    }
    return pressure;
}

int get_depth_of(std::string target, std::string current, std::vector<std::string>& history, std::map<std::string, std::vector<std::string>>& neigh_map, int depth=1) {
    history.push_back(current);
    bool all_visited = true;
    std::vector<std::string> valves_to_explore;
    for (auto neigh : neigh_map[current]) {
        if (target.compare(neigh)==0)
            return depth;
        if (find(history.begin(), history.end(), neigh) == history.end()) {
            valves_to_explore.push_back(neigh);
            all_visited = false;
        }
    }

    if (all_visited)
        return -1;
    auto min_ret = 10000;

    for (auto neigh : valves_to_explore) {
        std::vector<std::string> new_history = history;
        int ret = get_depth_of(target, neigh, new_history, neigh_map, depth+1);
        if (ret != -1 && ret < min_ret)
            min_ret = ret;
    }
    if (min_ret == 10000)
        return -1;
    else
        return min_ret;
}

bool compare_valves(std::string start, std::string first, std::string second, std::map<std::string, int>& flow_rate_map, std::map<std::string, std::vector<std::string>>& neigh_map) {
    std::vector<std::string> history;
    auto first_depth = get_depth_of(first, start, history, neigh_map);
    history.clear();
    auto second_depth = get_depth_of(second, start, history, neigh_map);
    int diff = std::abs(first_depth - second_depth);
    // cout << "comparing " <<first << "-" << first_depth <<  "x"<< flow_rate_map[first]<< " and " << second << "-" << second_depth <<  "x"<< flow_rate_map[second] << endl;
    if (diff == 0) {
        return flow_rate_map[first] > flow_rate_map[second];
    }
    else {
       if (first_depth < second_depth) {
            int multp = diff*flow_rate_map[first];
            bool ret = multp > flow_rate_map[second];
            return (diff*flow_rate_map[first]) > std::abs(flow_rate_map[second]-flow_rate_map[first]);
       } else {
            return (diff*flow_rate_map[second]) < std::abs(flow_rate_map[second]-flow_rate_map[first]);
       }
    }
}
            // return (diff*flow_rate_map[first]) > flow_rate_map[second];
            // return (diff*flow_rate_map[second]) < flow_rate_map[first];


std::vector<std::string> sort_valves(std::string start, std::map<std::string, int>& flow_rate_map, std::map<std::string, std::vector<std::string>>& neigh_map, std::vector<std::string>& target_valves) {
    std::vector<std::string> sorted_values;
    while(target_valves.size() > 0) {
        std::string min_valve = target_valves.front();
        for (auto valve : target_valves) {
            if (!compare_valves(start, min_valve, valve, flow_rate_map, neigh_map)) {
                min_valve = valve;
            }
        }

        target_valves.erase(std::remove(target_valves.begin(), target_valves.end(), min_valve), target_valves.end());
        sorted_values.push_back(min_valve);
        start = min_valve;
    }
    return sorted_values;
}

int compute_sum_pressure(std::string start, std::vector<std::string>& sorted_target_valves, std::map<std::string, int>& flow_rate_map,std::map<std::string, std::vector<std::string>>& neigh_map) {
    int sum=0;
    int budget=30;
    std::set<std::string> open_valves;
    for (auto valve : sorted_target_valves) {
        std::vector<string> history;
        auto current_depth = get_depth_of(valve, start, history, neigh_map);
        //move
        for (int i=0; i<current_depth; i++) {
            budget--;
            sum += compute_pressure(open_valves, flow_rate_map);
            if (budget == 0)
                break;


        }
        if (budget <= 0)
            break;
        cout << "== Minute "<<30-budget<<" =="<<endl;
        cout << "Moved to " << valve << " flow rate: " << compute_pressure(open_valves, flow_rate_map) << " budget: " << budget <<  endl;

        sum += compute_pressure(open_valves, flow_rate_map);
        open_valves.insert(valve);
        budget--;


        cout << "== Minute "<<30-budget<<" =="<<endl;
        cout << "Opened " << valve << " flow rate: " << compute_pressure(open_valves, flow_rate_map) << " budget: " << budget <<  endl;

        start = valve;


        if (budget <= 0)
            break;
    }
    while (budget > 0) {
        budget--;
        cout << "== Minute "<<30-budget<<" =="<<endl;
        sum += compute_pressure(open_valves, flow_rate_map);
        cout << "Releasing flow rate: " << compute_pressure(open_valves, flow_rate_map) << " budget: " << budget <<  endl;

    }
    return sum;

}

std::string find_optimal_next(std::string start, std::map<std::string, int>& flow_rate_map, std::map<std::string, std::vector<std::string>>& neigh_map, std::vector<std::string>& target_valves) {
    std::string min_valve = target_valves.front();
    for (auto valve : target_valves) {
        if (!compare_valves(start, min_valve, valve, flow_rate_map, neigh_map)) {
            min_valve = valve;
        }
    }
    return min_valve;
}
int compute_sum_pressure2(std::string start, std::vector<std::string>& my_picks, std::vector<std::string>& elph_picks, std::map<std::string, int>& flow_rate_map,std::map<std::string, std::vector<std::string>>& neigh_map, int n_targets) {
    int sum=0;
    int budget=26;

    std::set<std::string> open_valves;
    std::string my_start = start;
    std::string elph_start = start;
    std::vector<string> history;
    int my_i = 0;
    int elph_i = 0;

    auto my_depth = get_depth_of(my_picks[my_i], my_start, history, neigh_map);
    history.clear();
    auto elph_depth = get_depth_of(elph_picks[elph_i], elph_start, history, neigh_map);
    // int n_targets = my_picks.size()*2;

    for (int b=1; b<budget+1; b++ ){
        // cout << "== Minute "<<b<<" =="<<endl;
        // cout << "Releasing flow rate: " << compute_pressure(open_valves, flow_rate_map)  <<  endl;

        sum += compute_pressure(open_valves, flow_rate_map);

        if (open_valves.size()==n_targets) {
            continue;
        }

        //move
        if (my_depth > 0 ) {
            my_depth--;
            // if (my_depth > 0 )
                // cout << "You are moving to " << my_picks[my_i] <<  endl;
            // else
                // cout << "You moved to " << my_picks[my_i] <<  endl;
        } else if (my_i < my_picks.size()) {
            open_valves.insert(my_picks[my_i]);
            // cout << "You opened " << my_picks[my_i] <<  endl;
            my_start = my_picks[my_i];
            my_i++;
            history.clear();
            if (my_i < my_picks.size())
                my_depth = get_depth_of(my_picks[my_i], my_start, history, neigh_map);
        }

        if (elph_depth > 0 ) {
            elph_depth--;
            // if (elph_depth > 0 )
            //     cout << "Elph is moving to " << elph_picks[elph_i] <<  endl;
            // else
            //     cout << "Elph moved to " << elph_picks[elph_i] <<  endl;
        } else if (elph_i < elph_picks.size()) {
            open_valves.insert(elph_picks[elph_i]);
            // cout << "Elph opened " << elph_picks[elph_i] <<  endl;
            elph_start = elph_picks[elph_i];
            elph_i++;
            history.clear();
            if (elph_i < elph_picks.size())
                elph_depth = get_depth_of(elph_picks[elph_i], elph_start, history, neigh_map);
        }
    }
    return sum;

}



AOC_DAY(Day16_1) {

    std::string line;
    std::map<std::string, int> flow_rate_map;
    std::map<std::string, std::vector<std::string>> neigh_map;
    std::string start = "AA";
    while (getline(cin,line)) {
        std::stringstream ss(line);

        std::string buf;
        std::string valve;
        std::string s_flow_rate;
        std::vector<std::string> valve_neighs;
        ss >> buf >> valve >> buf >> buf >> s_flow_rate >> buf >> buf >> buf >> buf;
        while (getline(ss, buf, ',')) {
            buf.erase(remove(buf.begin(), buf.end(), ' '), buf.end());
            valve_neighs.push_back(buf);
        }
        int flow_rate = stoi(s_flow_rate.substr(s_flow_rate.find("=")+1, s_flow_rate.length()-s_flow_rate.find("=")-1));
        flow_rate_map[valve]=flow_rate;
        neigh_map[valve]=valve_neighs;
    }

    std::vector<std::string> target_valves;
    for (auto it = flow_rate_map.begin(); it != flow_rate_map.end(); it++) {
        if (it->second > 0)
            target_valves.push_back(it->first);
    }
    int max_sum = 0;
    for (auto target : target_valves) {

        std::vector<std::string> new_target_valves = target_valves;
        new_target_valves.erase(remove(new_target_valves.begin(), new_target_valves.end(), target), new_target_valves.end());
        auto sorted_target_valves = sort_valves(target, flow_rate_map, neigh_map, new_target_valves);
        // sorted_target_valves.insert(target);
        int sum = compute_sum_pressure(start, sorted_target_valves, flow_rate_map, neigh_map);
        max_sum = max(max_sum, sum);
    }
    return std::to_string(max_sum);
}


std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> comb(int N, int K)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
    std::vector<std::vector<int>> result;
    std::vector<std::vector<int>> inverse_result;
    result.reserve(N);
    inverse_result.reserve(N);
    // print integers and permute bitmask
    do {
        std::vector<int> combination;
        std::vector<int> inv_combination;
        combination.reserve(K);
        inv_combination.reserve(K);
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i])
                combination.push_back(i);
            else
                inv_combination.push_back(i);
        }
        result.push_back(combination);
        inverse_result.push_back(inv_combination);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return {result, inverse_result};
}

AOC_DAY(Day16_2) {
    std::string line;
    std::map<std::string, int> flow_rate_map;
    std::map<std::string, std::vector<std::string>> neigh_map;
    std::string start = "AA";
    while (getline(cin,line)) {
        std::stringstream ss(line);
        std::string buf;
        std::string valve;
        std::string s_flow_rate;
        std::vector<std::string> valve_neighs;
        ss >> buf >> valve >> buf >> buf >> s_flow_rate >> buf >> buf >> buf >> buf;
        while (getline(ss, buf, ',')) {
            buf.erase(remove(buf.begin(), buf.end(), ' '), buf.end());
            valve_neighs.push_back(buf);
        }
        int flow_rate = stoi(s_flow_rate.substr(s_flow_rate.find("=")+1, s_flow_rate.length()-s_flow_rate.find("=")-1));
        flow_rate_map[valve]=flow_rate;
        neigh_map[valve]=valve_neighs;
    }

    std::vector<std::string> target_valves;
    for (auto it = flow_rate_map.begin(); it != flow_rate_map.end(); it++) {
        if (it->second > 0)
            target_valves.push_back(it->first);
    }
    int max_sum = 0;

    cout << "size target valves " << target_valves.size() << endl;
    for (auto valve : target_valves)
        cout << valve << " ";
    cout << endl;
    std::vector<std::vector<int>> combinations, inv_combinations;
    std::tie(combinations, inv_combinations) = comb(target_valves.size(), target_valves.size()/2);
    cout << "combinations " << combinations.size() << endl;

    for (int i=0; i<combinations.size(); i++) {
        std::vector<string> subgroup;
        std::vector<string> inv_subgroup;

        for (int j=0; j<combinations[i].size(); j++){
            subgroup.push_back(target_valves[combinations[i][j]]);
        }
        for (int j=0; j<inv_combinations[i].size(); j++){
            inv_subgroup.push_back(target_valves[inv_combinations[i][j]]);
        }
        auto ordered_combination = sort_valves(start, flow_rate_map, neigh_map, subgroup);
        auto ordered_inv_combination = sort_valves(start, flow_rate_map, neigh_map, inv_subgroup);

        for (auto value : ordered_combination)
            cout << value << " ";
        cout << ": ";
        for (auto value : ordered_inv_combination)
            cout << value << " ";
        cout << i+1 << "/" << combinations.size() << " "<< max_sum << endl;
        int sum = compute_sum_pressure2(start, ordered_combination, ordered_inv_combination, flow_rate_map, neigh_map, target_valves.size());
        if (sum>max_sum) {
            max_sum = sum;
            cout << "Current max " << max_sum << endl;
        }
        break;
    }

    return std::to_string(max_sum);
}