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

std::deque<std::string> sort_valves(std::string start, std::map<std::string, int>& flow_rate_map, std::map<std::string, std::vector<std::string>>& neigh_map, std::vector<std::string>& target_valves) {
    std::deque<std::string> sorted_values;
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

int compute_sum_pressure(std::string start, std::deque<std::string>& sorted_target_valves, std::map<std::string, int>& flow_rate_map,std::map<std::string, std::vector<std::string>>& neigh_map) {
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
        sorted_target_valves.push_front(target);
        int sum = compute_sum_pressure(start, sorted_target_valves, flow_rate_map, neigh_map);
        max_sum = max(max_sum, sum);
    }
    return std::to_string(max_sum);
}


AOC_DAY(Day16_2) {

   return std::to_string(2);
}