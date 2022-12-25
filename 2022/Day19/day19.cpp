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
        if (state[state::ore_robot])
            cout << "Ore robots collect " << state[state::ore_robot] << " total ore: " << state[state::ore] << endl;
        if (state[state::clay_robot])
            cout << "Clay robots collect " << state[state::clay_robot] << " total clay: " << state[state::clay] << endl;
        if (state[state::obsidian_robot])
            cout << "Obsidian robots collect " << state[state::obsidian_robot] << " total obsidian: " << state[state::obsidian] << endl;
        if (state[state::geode_robot])
            cout << "Geode robots collect " << state[state::geode_robot] << " total geode: " << state[state::geode] << endl;
}
void reduce_material(StateType& state, CostsType& costs, int i) {
    if (i==state::ore_robot)
        state[state::ore] -= costs[costs::ore_ore_robot];
    else if (i==state::clay_robot)
        state[state::ore] -= costs[costs::ore_clay_robot];
    else if (i==state::obsidian_robot) {
        state[state::ore] -= costs[costs::ore_obsidian_robot];
        state[state::clay] -= costs[costs::ore_clay_robot];
    }
    else {
        state[state::ore] -= costs[costs::ore_geode_robot];
        state[state::obsidian] -= costs[costs::ore_obsidian_robot];
    }
}

bool possible_scenario(const StateType state, const CostsType costs, const int i) {
    if (i==state::ore_robot)
        return state[state::ore] >= costs[costs::ore_ore_robot];
    else if (i==state::clay_robot)
        return state[state::ore] >= costs[costs::ore_clay_robot];
    else if (i==state::obsidian_robot)
        return state[state::ore] >= costs[costs::ore_obsidian_robot] && state[state::clay] >= costs[costs::ore_clay_robot];
    else
        return state[state::ore] >= costs[costs::ore_geode_robot] && state[state::obsidian] >= costs[costs::ore_obsidian_robot];
}

int advance(StateType state, CostsType costs, int max_geode=0)
{

    if (state[state::ore_robot] > 4)
        return max_geode;

    if (state[state::clay_robot] > costs[costs::clay_obsidian_robot])
        return max_geode;

    if (state[state::obsidian_robot] > costs[costs::obsidian_geode_robot])
        return max_geode;


    state[state::minutes]++;
    cout << "== Minute " << state[state::minutes] << "==" << endl;
    cout << "state: ";
    for (auto i : state) {
        cout << i << " ";
    }
    cout << endl;
    increase_materials(state);

    if (state[state::minutes]==24)
        return state[state::geode];

    // explore neighs
    for (int i = 0; i<5; i++) {
        if (i==4)
            max_geode = max(max_geode, advance(state, costs, max_geode));
        else {
            if (possible_scenario(state, costs, state::ore_robot+i)) {
                auto new_state = state;
                reduce_material(new_state, costs, state::ore_robot+i);
                new_state[state::ore_robot+i] += 1;
                max_geode = max(max_geode, advance(new_state, costs, max_geode));
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

        for (auto c : blueprint) {
            cout << c << " ";
        }
        cout << endl;
        costs_vector.push_back(blueprint);
    }
    cout.setstate(std::ios::failbit);
    int quality_level = 0;
    for (auto costs : costs_vector) {
        StateType state({0,0,0,0,0,0,0,0});
        state[state::ore_robot] = 1;
        int max_geode = advance(state, costs);

        quality_level += max_geode*costs[costs::id];
        break;
    }

    cout.clear();


    return std::to_string(quality_level);
}

AOC_DAY(Day19_2) {

    return std::to_string(3);
}




    //  for (int i = 1; i < max_ore+3; i++) {
    //         for (int j = 1; j < bp[costs::clay_obsidian_robot]+3; j++) {
    //             for (int k = 1; k < bp[costs::obsidian_geode_robot]+3; k++) {
    //                 int ore=0, clay=0, obsidian=0, geode=0;
    //                 int ore_robot=1, clay_robot=0, obsidian_robot=0, geode_robot=0;
    //                 auto increase_materials = [&] () {
    //                     ore += ore_robot;
    //                     clay += clay_robot;
    //                     obsidian += obsidian_robot;
    //                     geode += geode_robot;
    //                     if (ore_robot)
    //                         cout << "Ore robots collect " << ore_robot << " total ore: " << ore << endl;
    //                     if (clay_robot)
    //                         cout << "Clay robots collect " << clay_robot << " total clay: " << clay << endl;
    //                     if (obsidian_robot)
    //                         cout << "Obsidian robots collect " << obsidian_robot << " total obsidian: " << obsidian << endl;
    //                     if (geode_robot)
    //                         cout << "Geode robots collect " << geode_robot << " total geode: " << geode << endl;
    //                 };
    //                 int ore_aim = i;
    //                 cout << "Aiming for " << ore_aim << " ore robots" << endl;
    //                 int clay_aim = j;
    //                 cout << "Aiming for " << clay_aim << " clay robots" << endl;
    //                 int obsidian_aim = k;
    //                 cout << "Aiming for " << obsidian_aim << " obsidian robots" << endl;

    //                 for (int min=1; min<25; min++) {
    //                     cout << "== Minute " << min << "==" << endl;
    //                     if (obsidian>=bp[costs::obsidian_geode_robot] && ore>=bp[costs::ore_geode_robot]) {
    //                         ore -= bp[costs::ore_geode_robot];
    //                         obsidian -= bp[costs::obsidian_geode_robot];
    //                         cout << "Spend ore and obsidian creating a geode robot. Total ore: " << ore << " total obsidian: " << obsidian << endl;
    //                         increase_materials();
    //                         geode_robot++;
    //                         cout << ". Now there's " << geode_robot << " geode robots." << endl;
    //                         double turns_to_obsidian_geode = max(ceil((double)(bp[costs::obsidian_geode_robot]-obsidian)/obsidian_robot)+1,1.0);
    //                         double turns_to_ore_geode = max(ceil((double)(bp[costs::ore_geode_robot]-ore+bp[costs::ore_obsidian_robot])/ore_robot)+1,1.0);
    //                         double turns_to_clay_obsidian = max(ceil((double)(bp[costs::clay_obsidian_robot]-clay)/clay_robot)+1,1.0);
    //                         double turns_to_ore_obsidian = max(ceil((double)(bp[costs::ore_obsidian_robot]-ore)/ore_robot)+1,1.0);

    //                         if (turns_to_obsidian_geode >= turns_to_ore_geode && max(turns_to_clay_obsidian, turns_to_ore_obsidian)) {
    //                         cout << "turns 1: " << turns_to_obsidian_geode << " " << turns_to_ore_geode << " turns 2: " << turns_to_clay_obsidian<<" "<<turns_to_ore_obsidian<<endl;
    //                             obsidian_aim++;
    //                             cout << "Aiming for " << obsidian_aim << " obisidian robots" << endl;
    //                         }
    //                         continue;
    //                     }

    //                     if (clay>=bp[costs::clay_obsidian_robot] && ore>=bp[costs::ore_obsidian_robot] && obsidian_robot<obsidian_aim && clay_robot>=clay_aim && ore_robot>=ore_aim) {
    //                         ore -= bp[costs::ore_obsidian_robot];
    //                         clay -= bp[costs::clay_obsidian_robot];
    //                         cout << "Spend ore and clay creating a obsidian robot. Total ore: " << ore << " total clay: " << clay << endl;
    //                         increase_materials();
    //                         obsidian_robot++;
    //                         double turns_to_clay_obsidian = max(ceil((double)(bp[costs::clay_obsidian_robot]-clay)/clay_robot)+1, 1.0);
    //                         double turns_to_ore_obsidian = max(ceil((double)(bp[costs::ore_obsidian_robot]-ore+bp[costs::ore_geode_robot])/ore_robot)+1,1.0);
    //                         double turns_to_ore_clay = max(ceil((double)(bp[costs::ore_geode_robot]-ore)/ore_robot)+1,1.0);
    //                         if (turns_to_clay_obsidian >= turns_to_ore_obsidian && turns_to_clay_obsidian > turns_to_ore_clay) {
    //                             cout << "turns 1: " << turns_to_clay_obsidian << " " << turns_to_ore_obsidian << " turns 2: " << turns_to_ore_clay<<endl;
    //                             clay_aim++;
    //                             cout << "Aiming for " << clay_aim << " clay robots" << endl;
    //                         }
    //                         continue;
    //                     }
    //                     if (ore>=bp[costs::ore_clay_robot] && clay_robot<clay_aim && ore_robot>=ore_aim) {
    //                         double turns_to_obsidian = max(floor((double)(bp[costs::obsidian_geode_robot]-obsidian)/obsidian_robot)+1, 1.0);
    //                         double turns_to_ore = max(floor((double)(bp[costs::ore_geode_robot]-ore)/ore_robot)+1,1.0);
    //                         ore -= bp[costs::ore_clay_robot];
    //                         cout << "Spend ore creating a clay robot. Total ore: " << ore << endl;
    //                         increase_materials();
    //                         clay_robot++;
    //                         cout << ". Now there's " << clay_robot << " clay robots." << endl;
    //                         continue;

    //                     }
    //                     if (ore >= bp[costs::ore_ore_robot] && ore_robot<ore_aim) {
    //                         ore -= bp[costs::ore_ore_robot];
    //                         cout << "Spend ore creating a ore robot. Total ore: " << ore << endl;
    //                         increase_materials();
    //                         ore_robot++;
    //                         cout << ". Now there's " << ore_robot << " ore robots." << endl;
    //                         continue;
    //                     }
    //                     else
    //                         increase_materials();

    //                 }
    //                 cout << "FINAL GEODE: " << geode <<  endl;

    //                 max_geode = max(max_geode, geode);
    //             }
    //         }
    //     }