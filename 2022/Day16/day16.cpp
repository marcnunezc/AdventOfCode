int compute_pressure(std::set<std::string> open_valves, std::map<std::string, int> flow_rate_map) {
    int pressure = 0;
    for (auto it = open_valves.begin(); it != open_valves.end(); it++) {
        pressure += flow_rate_map[*it];
    }
    return pressure;
}

// int explore(std::string current, int budget, int sum, std::set<std::string> open_valves, std::map<std::string, int> flow_rate_map,
//     std::map<std::string, std::vector<std::string>> neigh_map) {
//     if (!budget) {
//         cout << "finished budget with sum " << sum << endl;
//         return sum;
//     }
//     cout << "moved to valve " << current <<endl;
//     sum += flow_rate_map[current];
//     cout << "opened valve " << current <<" releasing " << sum << endl;

//     for (auto neigh : neigh_map[current]) {

//         auto ret =  explore(neigh, budget-2, sum, flow_rate_map, neigh_map);
//     }
// }

int get_depth_of(std::string target, std::string current, std::vector<std::string>& history, std::map<std::string, std::vector<std::string>>& neigh_map, int depth=1) {
    history.push_back(current);
    // cout << "exploring " << current << endl;
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
    // cout << "all visited " << all_visited << endl;
    // cout << "current history ";
    // for (auto value : history)
        // cout << value << " ";
    // cout << endl;

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

bool compare_valves(std::string first, std::string second, std::map<std::string, int>& flow_rate_map, std::map<std::string, int>& depth_map) {

    int diff = std::abs(depth_map[first] - depth_map[second]);

    // cout << "diff " << diff << endl;

    if (diff == 0) {
        return flow_rate_map[first] > flow_rate_map[second];
    }
    else {
       if (depth_map[first] < depth_map[second]) {
            int multp = diff*flow_rate_map[first];
            bool ret = multp > flow_rate_map[second];
            // cout << "diff*flow_rate_map[first] > flow_rate_map[second]: " <<  multp << " > " << flow_rate_map[second] << endl;
            return (diff*flow_rate_map[first]) > std::abs(flow_rate_map[second]-flow_rate_map[first]);
       } else {
            return (diff*flow_rate_map[second]) < std::abs(flow_rate_map[second]-flow_rate_map[first]);
       }
    }
}

std::vector<std::string> sort_valves(std::map<std::string, int>& flow_rate_map, std::map<std::string, int>& depth_map) {
    std::vector<std::string> target_valves;

    for (auto it = depth_map.begin(); it != depth_map.end(); it++) {
        target_valves.push_back(it->first);
        // cout << it->first << " flow rate: " << flow_rate_map[it->first] << " depth: " << depth_map[it->first] << endl;
    }

    bool is_vector_ordered = true;
    int index=0;
    // cout << "size target valves "<< target_valves.size() << endl;
    while (true) {
        index++;
        if (index==target_valves.size()) {
            index=1;
            if (is_vector_ordered)
                break;
            is_vector_ordered = true;

        }

        bool good_order = compare_valves(target_valves[index-1],target_valves[index], flow_rate_map, depth_map);

        if (!good_order) {
            // cout << target_valves[index-1] << " and "<<target_valves[index] << " in bad ordert" << endl;
            is_vector_ordered = false;
            auto aux = target_valves[index];
            target_valves[index] = target_valves[index-1];
            target_valves[index-1] = aux;
        } else {
        // cout << "indez "<< index<< " "<<target_valves[index-1] << " and "<<target_valves[index] << "   in good order" << endl;

        }
    }
    return target_valves;
}

AOC_DAY(Day16_1) {

    std::string line;
    std::map<std::string, int> flow_rate_map;
    std::map<std::string, std::vector<std::string>> neigh_map;
    std::string start = "null";
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

        if (start.compare("null")==0) {
            start = valve;
        }

        cout << valve << " " << flow_rate << " ";
        for (auto neigh : valve_neighs)
            cout <<  neigh << " ";
        cout <<  endl;

        flow_rate_map[valve]=flow_rate;
        neigh_map[valve]=valve_neighs;
    }

    int budget = 30;
    std::map<std::string, int> depth_map;
    std::set<std::string> open_valves;
    for (auto it = flow_rate_map.begin(); it != flow_rate_map.end(); it++) {
        if (it->second > 0) {
            std::vector<string> history;
            depth_map[it->first] = get_depth_of(it->first, start, history, neigh_map);
        }
    }
    cout << "START SORT" <<endl;

    auto sorted_target_valves = sort_valves(flow_rate_map, depth_map);

    cout << "SORTED" <<endl;
    int sum=0;
    for (auto valve : sorted_target_valves) {
        std::vector<string> history;
        auto current_depth = get_depth_of(valve, start, history, neigh_map);
        // cout << "Im at " <<  start << " target is " << valve << " at " << current_depth << " steps" <<endl;
        //move
        for (int i=0; i<current_depth; i++) {
            budget--;
            sum += compute_pressure(open_valves, flow_rate_map);

        }
        cout << "== Minute "<<30-budget<<" =="<<endl;
        cout << "Moved to " << valve << " flow rate: " << compute_pressure(open_valves, flow_rate_map) << " budget: " << budget <<  endl;

        sum += compute_pressure(open_valves, flow_rate_map);
        open_valves.insert(valve);
        budget--;


        cout << "== Minute "<<30-budget<<" =="<<endl;
        cout << "Opened " << valve << " flow rate: " << compute_pressure(open_valves, flow_rate_map) << " budget: " << budget <<  endl;

        start = valve;


        if (budget == 0)
            break;
    }
    while (budget != 0) {
        budget--;
        cout << "== Minute "<<30-budget<<" =="<<endl;
        sum += compute_pressure(open_valves, flow_rate_map);
        cout << "Releasing flow rate: " << compute_pressure(open_valves, flow_rate_map) << " budget: " << budget <<  endl;

    }


    return std::to_string(sum);
}


AOC_DAY(Day16_2) {

   return std::to_string(2);
}