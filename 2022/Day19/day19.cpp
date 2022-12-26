typedef std::array<int, 9> StateType;
typedef std::array<int, 7> CostsType;

enum costs {
    ore_ore_robot,
    ore_clay_robot,
    ore_obsidian_robot,
    clay_obsidian_robot,
    ore_geode_robot,
    obsidian_geode_robot,
    id
};

enum state {
    minutes,
    ore,
    clay,
    obsidian,
    geode,
    ore_robot,
    clay_robot,
    obsidian_robot,
    geode_robot
};

void increase_materials(StateType& state) {
        state[state::ore] += state[state::ore_robot];
        state[state::clay] += state[state::clay_robot];
        state[state::obsidian] += state[state::obsidian_robot];
        state[state::geode] += state[state::geode_robot];
}
void reduce_material(StateType& state, CostsType& costs, int i) {
    if (i==state::ore_robot)
        state[state::ore] -= costs[costs::ore_ore_robot];
    else if (i==state::clay_robot)
        state[state::ore] -= costs[costs::ore_clay_robot];
    else if (i==state::obsidian_robot) {
        state[state::ore] -= costs[costs::ore_obsidian_robot];
        state[state::clay] -= costs[costs::clay_obsidian_robot];
    }
    else {
        state[state::ore] -= costs[costs::ore_geode_robot];
        state[state::obsidian] -= costs[costs::obsidian_geode_robot];
    }
}

bool possible_scenario(const StateType state, const CostsType costs, const int i) {
    if (i==state::ore_robot)
        return state[state::ore] >= costs[costs::ore_ore_robot];
    else if (i==state::clay_robot)
        return state[state::ore] >= costs[costs::ore_clay_robot];
    else if (i==state::obsidian_robot)
        return state[state::ore] >= costs[costs::ore_obsidian_robot] && state[state::clay] >= costs[costs::clay_obsidian_robot];
    else
        return state[state::ore] >= costs[costs::ore_geode_robot] && state[state::obsidian] >= costs[costs::obsidian_geode_robot];
}

int advance(StateType state, CostsType costs, std::vector<int>& max_geode_vector, int max_geode=0, int new_creation=0)
{

    if (state[state::ore_robot] > max(costs[costs::ore_clay_robot], max(costs[costs::ore_obsidian_robot], costs[costs::ore_geode_robot])))
        return max_geode;

    if (state[state::clay_robot] > costs[costs::clay_obsidian_robot])
        return max_geode;

    if (state[state::obsidian_robot] > costs[costs::obsidian_geode_robot])
        return max_geode;


    state[state::minutes]++;
    increase_materials(state);

    if (new_creation) {
        reduce_material(state, costs, new_creation);
        state[new_creation] += 1;

    }

    if (max_geode_vector[state[state::minutes]-1] > state[state::geode])
        return max_geode;
    else if (max_geode_vector[state[state::minutes]-1] < state[state::geode])
        max_geode_vector[state[state::minutes]-1]=state[state::geode];

    if (state[state::minutes]==max_geode_vector.size())
        return state[state::geode];

    // explore neighs
    for (int i = 0; i<5; i++) {
        if (i==4) {
            max_geode = max(max_geode, advance(state, costs, max_geode_vector, max_geode,0));
        }
        else {
            if (possible_scenario(state, costs, state::ore_robot+i)) {
                max_geode = max(max_geode, advance(state, costs, max_geode_vector, max_geode, state::ore_robot+i));
            }
        }
    }
    return max_geode;
};

AOC_DAY(Day19_1) {
    std::string line;
    std::vector<CostsType> costs_vector;
    while (getline(cin, line)) {
        CostsType blueprint;
        sscanf(line.c_str(),"Blueprint %i: Each ore robot costs %i ore. Each clay robot costs %i ore. Each obsidian robot costs %i ore and %i clay. Each geode robot costs %i ore and %i obsidian.",
        &blueprint[costs::id],
        &blueprint[costs::ore_ore_robot],
        &blueprint[costs::ore_clay_robot],
        &blueprint[costs::ore_obsidian_robot],
        &blueprint[costs::clay_obsidian_robot],
        &blueprint[costs::ore_geode_robot],
        &blueprint[costs::obsidian_geode_robot]);
        costs_vector.push_back(blueprint);
    }
    int quality_level = 0;
    for (auto costs : costs_vector) {
        StateType state({0,0,0,0,0,0,0,0});
        state[state::ore_robot] = 1;
        std::vector<int> max_geode_vector(24,0);
        int  max_geode = advance(state, costs, max_geode_vector);

        cout << "id max_geode " << costs[costs::id] << " " << max_geode << endl;

        quality_level += max_geode*costs[costs::id];
    }

    return std::to_string(quality_level);
}

AOC_DAY(Day19_2) {
    std::string line;
    std::vector<CostsType> costs_vector;
    while (getline(cin, line)) {
        CostsType blueprint;
        sscanf(line.c_str(),"Blueprint %i: Each ore robot costs %i ore. Each clay robot costs %i ore. Each obsidian robot costs %i ore and %i clay. Each geode robot costs %i ore and %i obsidian.",
        &blueprint[costs::id],
        &blueprint[costs::ore_ore_robot],
        &blueprint[costs::ore_clay_robot],
        &blueprint[costs::ore_obsidian_robot],
        &blueprint[costs::clay_obsidian_robot],
        &blueprint[costs::ore_geode_robot],
        &blueprint[costs::obsidian_geode_robot]);
        costs_vector.push_back(blueprint);
    }

    int multiplication = 1;
    int count = 0;
    for (auto costs : costs_vector) {
        count++;
        StateType state({0,0,0,0,0,0,0,0});
        state[state::ore_robot] = 1;
        std::vector<int> max_geode_vector(32,0);
        int  max_geode = advance(state, costs, max_geode_vector);

        cout << "id max_geode " << costs[costs::id] << " " << max_geode<< endl;

        multiplication *= max_geode;
        if (count == 3)
            break;
    }

    return std::to_string(multiplication);
}