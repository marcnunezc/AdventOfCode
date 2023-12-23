typedef std::unordered_set<std::pair<int,int>, pair_hash> UnorderedSetPairType;

void get_neighbours(std::pair<int,int>& current, std::vector<std::string>& matrix, UnorderedSetPairType& current_neighs, UnorderedSetPairType& previous_neighs)
{
    int i=current.first;
    int j=current.second;
    int size_i = matrix.size();
    int size_j = matrix[0].size();

    std::vector<std::pair<int,int>> neighbour_list = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1},
    };
    for (auto [neigh_i, neigh_j] : neighbour_list) {
        if (neigh_i+i<0 || neigh_i+i >= size_i)
            continue;
        if (neigh_j+j<0 || neigh_j+j >= size_j)
            continue;
        std::pair<int,int> new_pair = {neigh_i+i, neigh_j+j};
        if (matrix[new_pair.first][new_pair.second] != '#' && previous_neighs.find(new_pair) == previous_neighs.end()) {
            current_neighs.insert(new_pair);
        }
    }
}

AOC_DAY(Day21_1){
    size_t sum = 0;
    std::vector<std::string> matrix;
    int i = 0;
    std::string line;
    std::pair<int,int> start;
    int steps = 26501365;
    while(getline(cin, line)) {
        matrix.push_back(line);
        auto start_pos = line.find('S');
        if (start_pos != string::npos) {
            start.first = i; start.second = start_pos;
        }
        i++;
    }
    auto current = start;
    UnorderedSetPairType neighbours;
    UnorderedSetPairType aux_neighbours;
    get_neighbours(current, matrix, neighbours, aux_neighbours);
    for (int step = 1; step<steps; step++) {
        if (step % 1000 == 0)
            cout << step << endl;
        aux_neighbours.clear();
        for (auto neigh : neighbours) {
            get_neighbours(neigh, matrix, aux_neighbours, neighbours);
        }
        neighbours = aux_neighbours;
    }
    return std::to_string(neighbours.size());
}

AOC_DAY(Day21_2){
    size_t sum = 0;
    return std::to_string(sum);
}