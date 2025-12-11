#include <queue>
struct Machine {
    std::string target;
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltage_values;
};

size_t count_required_buttons(Machine& machine, const std::string target_state) {
    std::string current_state = std::string(machine.target.size(), '.');
    std::queue<std::pair<std::string, size_t>> neighbour_queue;
    std::unordered_set<std::string> visited_neighbours;
    neighbour_queue.push({current_state, 0});
    visited_neighbours.insert(current_state);
    while (!neighbour_queue.empty()) {
        auto [state, dist] = neighbour_queue.front();
        neighbour_queue.pop();

        for (auto& button_group : machine.buttons) {
            std::string new_state = state;
            for (auto& button : button_group) {
                new_state[button] = (new_state[button] == '.') ? '#' : '.';
            }

            if (new_state == target_state)
                return dist + 1;

            if (!visited_neighbours.count(new_state)) {
                visited_neighbours.insert(new_state);
                neighbour_queue.push({new_state, dist + 1});
            }
        }
    }

    return 1e9;
}

AOC_DAY(Day10_1) {

    std::size_t sum = 0;
    std::string line;
    std::vector<Machine> machine_list;


    // PARSING DONE BY CHATGPT
    while (std::getline(cin, line)) {
        if (line.empty()) continue;

        Machine machine;
        size_t i = 0;
        size_t start = 1;

        while (line[i] != ']') {
            i++;
        }
        machine.target = line.substr(start, i - start);
        i++;

        while (i < line.size()) {

            if (line[i] == ' ') {
                i++;
                continue;
            }

            if (line[i] == '{') {
                break;
            }

            if (line[i] == '(') {
                i++; // skip '('
                start = i;

                while (line[i] != ')') i++;
                std::string inside = line.substr(start, i - start);

                i++; // skip ')'

                // parse comma-separated integers
                std::vector<int> btn;
                size_t p = 0;

                while (p < inside.size()) {
                    // skip spaces
                    while (p < inside.size() && inside[p] == ' ') p++;

                    size_t q = p;
                    while (q < inside.size() && inside[q] != ',') q++;

                    if (q > p) {
                        btn.push_back(std::stoi(inside.substr(p, q - p)));
                    }

                    p = q + 1; // move past comma, or end
                }

                machine.buttons.push_back(std::move(btn));
            }
        }

        machine_list.push_back(machine);
    }
    // PARSING DONE BY CHATGPT


    for (auto& machine : machine_list) {
        size_t count = count_required_buttons(machine,  machine.target);
        sum += count;
    }

    return std::to_string(sum);
}



size_t count_required_buttons_joltage(Machine& machine, const std::vector<int> target_state) {
    std::vector<int> current_state= std::vector<int>(machine.joltage_values.size(), 0);
    for (int i_joltage=0; i_joltage<target_state.size(); i_joltage++) {
        std::queue<std::pair<std::vector<int>, size_t>> neighbour_queue;
        std::set<std::vector<int>> visited_neighbours;
        neighbour_queue.push({current_state, 0});
        visited_neighbours.insert(current_state);
        cout << "Target joltage " << i_joltage << ": " << target_state[i_joltage] << endl;
        size_t final_dist =0;
        while (!neighbour_queue.empty()) {
            auto [state, dist] = neighbour_queue.front();
            cout << "Checking state: ";
            for (auto& s : state) {
                cout << s << " ";
            }
            cout << " at distance: " << dist << endl;
            neighbour_queue.pop();

            for (auto& button_group : machine.buttons) {
                std::vector<int> new_state = state;
                for (auto& button : button_group) {
                    if(i_joltage == button)
                        new_state[button]++;
                }

                if (new_state[i_joltage] == target_state[i_joltage]) {
                    final_dist = dist+1;
                    break;
                    // return dist + 1;
                }

                if (!visited_neighbours.count(new_state)) {
                    visited_neighbours.insert(new_state);
                    neighbour_queue.push({new_state, dist + 1});
                }
            }
        }
        cout << "Final distance for joltage " << i_joltage << ": " << final_dist << endl;
    }

    return 1e9;
}

AOC_DAY(Day10_2) {
    std::size_t sum = 0;
    std::string line;
    std::vector<Machine> machine_list;


    // PARSING DONE BY CHATGPT
    while (std::getline(cin, line)) {
        if (line.empty()) continue;

        Machine machine;
        size_t i = 0;

        // ----------------------------------------------------
        // IGNORE: content in square brackets [...]
        // ----------------------------------------------------
        while (i < line.size() && line[i] == ' ') i++;
        if (i < line.size() && line[i] == '[') {
            i++;
            // skip until closing ']'
            while (i < line.size() && line[i] != ']') i++;
            if (i < line.size()) i++; // skip ']'
        }

        // ----------------------------------------------------
        // PARSE button groups and curly values
        // ----------------------------------------------------

        while (i < line.size()) {

            // skip whitespace
            if (line[i] == ' ') {
                i++;
                continue;
            }

            // ----------------------------
            // CURLY BRACES: {a,b,c,...}
            // ----------------------------
            if (line[i] == '{') {
                i++; // skip '{'
                size_t start = i;

                // find matching '}'
                while (i < line.size() && line[i] != '}') i++;

                std::string inside = line.substr(start, i - start);

                if (i < line.size()) i++; // skip '}'

                // parse integers in "inside"
                std::vector<int> values;
                size_t p = 0;

                while (p < inside.size()) {
                    // skip whitespace
                    while (p < inside.size() && isspace(inside[p])) p++;

                    size_t q = p;
                    while (q < inside.size() && inside[q] != ',') q++;

                    if (q > p) {
                        values.push_back(std::stoi(inside.substr(p, q - p)));
                    }

                    p = (q < inside.size() ? q + 1 : q);
                }

                machine.joltage_values = std::move(values);
                break;
            }

            // ----------------------------
            // BUTTON GROUP: (a,b,c,...)
            // ----------------------------
            if (line[i] == '(') {
                i++; // skip '('
                size_t start = i;

                while (i < line.size() && line[i] != ')') i++;
                std::string inside = line.substr(start, i - start);
                if (i < line.size()) i++; // skip ')'

                // parse comma-separated ints
                std::vector<int> btn;
                size_t p = 0;

                while (p < inside.size()) {
                    // skip whitespace
                    while (p < inside.size() && inside[p] == ' ')
                        p++;

                    size_t q = p;
                    while (q < inside.size() && inside[q] != ',')
                        q++;

                    if (q > p) {
                        btn.push_back(std::stoi(inside.substr(p, q - p)));
                    }

                    p = (q < inside.size()) ? q + 1 : q;
                }

                machine.buttons.push_back(std::move(btn));
                continue;
            }

            // any other character → skip
            i++;
        }

        machine_list.push_back(std::move(machine));
    }
    // PARSING DONE BY CHATGPT


    for (auto& machine : machine_list) {
        // std::vector<std::vector<int>> A(machine.joltage_values.size(),std::vector<int>(machine.buttons.size(),0));
        // std::vector<int> b(machine.joltage_values.size(), 0);

        // for (int i=0; i<machine.joltage_values.size(); i++) {
        //     for (int j=0; j<machine.buttons.size(); j++) {
        //         for (auto& btn : machine.buttons[j]) {
        //             if (btn == i) {
        //                 A[i][j] = 1;
        //             }
        //         }
        //     }
        //     b[i] = machine.joltage_values[i];
        // }
        // // print A
        // cout << "Matrix A:" << endl;
        // for (auto& row : A) {
        //     for (auto& val : row) {
        //         cout << val << " ";
        //     }
        //     cout << endl;
        // }
        // // print b
        // cout << "Vector b:" << endl;
        // for (auto& val : b) {
        //     cout << val << " ";
        // }
        // cout << endl;
        size_t count = count_required_buttons_joltage(machine,  machine.joltage_values);
        sum += count;
        break;

    }

    return std::to_string(sum);

}
