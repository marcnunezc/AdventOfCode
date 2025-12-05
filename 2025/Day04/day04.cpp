AOC_DAY(Day04_1) {

    std::size_t sum = 0;
    std::string line;
    std::set<std::pair<int,int>> paper_positions;
    int i = 0;
    while (getline(cin, line)) {
        for (int j=0; j<line.length(); j++){
            if (line[j]=='@'){
                paper_positions.insert({i,j});
            }
        }
        i++;
    }

    for (auto pos : paper_positions) {

        std::vector<std::pair<int,int>> neighbour_check = {
            {0,1}, {1,0}, {1,1},
            {0,-1}, {-1,0}, {-1,-1},
            {1,-1}, {-1,1}
        };
        int neighbour_count = 0;
        bool is_valid = true;
        for (auto offset : neighbour_check) {
            int ni = pos.first + offset.first;
            int nj = pos.second + offset.second;
            if (paper_positions.find({ni,nj}) != paper_positions.end()){
                neighbour_count++;
            }
            if (neighbour_count >= 4){
                is_valid = false;
                break;
            }
        }
        if (is_valid)
            sum += 1;
    }

    return std::to_string(sum);
}

AOC_DAY(Day04_2){
    std::size_t sum = 0;
    std::string line;
    std::set<std::pair<int,int>> paper_positions;
    int i = 0;
    while (getline(cin, line)) {
        for (int j=0; j<line.length(); j++){
            if (line[j]=='@'){
                paper_positions.insert({i,j});
            }
        }
        i++;
    }

    bool stopping_criteria = false;
    while(!stopping_criteria) {
        std::set<std::pair<int,int>> positions_to_remove;

        for (auto pos : paper_positions) {

            std::vector<std::pair<int,int>> neighbour_check = {
                {0,1}, {1,0}, {1,1},
                {0,-1}, {-1,0}, {-1,-1},
                {1,-1}, {-1,1}
            };
            int neighbour_count = 0;
            bool is_valid = true;
            for (auto offset : neighbour_check) {
                int ni = pos.first + offset.first;
                int nj = pos.second + offset.second;
                if (paper_positions.find({ni,nj}) != paper_positions.end()){
                    neighbour_count++;
                }
                if (neighbour_count >= 4){
                    is_valid = false;
                    break;
                }
            }
            if (is_valid) {
                positions_to_remove.insert(pos);
            }
        }
        if (positions_to_remove.empty()) {
            stopping_criteria = true;
        }
        sum += positions_to_remove.size();
        for (auto pos : positions_to_remove) {
            paper_positions.erase(pos);
        }
    }

    return std::to_string(sum);
}
