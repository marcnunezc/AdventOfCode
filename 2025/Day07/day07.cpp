AOC_DAY(Day07_1) {

    std::size_t sum = 0;
    std::string line;
    getline(cin,line);
    int start_pos = line.find('S');
    std::set<int> ray_pos;
    ray_pos.insert(start_pos);
    while (getline(cin, line)) {
        std::set<int> new_ray_pos;

        for (int i = 0; i<line.length(); i++) {
            if (ray_pos.find(i) != ray_pos.end()) {
                if (line[i] == '^') {
                    sum++;
                    if (i>0)
                        new_ray_pos.insert(i-1);
                    if (i < line.size()-1)
                        new_ray_pos.insert(i+1);
                }
                else {
                    new_ray_pos.insert(i);
                }
            }
        }
        ray_pos = new_ray_pos;
    }
    return std::to_string(sum);
}

size_t cast_ray(std::vector<std::string>& input, int current_depth, int i_ray, std::map<std::pair<size_t,size_t>, size_t>& cache) {

    if (current_depth == input.size())  {
        return 1;
    }

    if (cache.find({current_depth, i_ray}) != cache.end())
        return cache[{current_depth, i_ray}];

    size_t count = 0;
    if (input[current_depth][i_ray] == '^') {
        if (i_ray>0) {
            count += cast_ray(input, current_depth+1, i_ray-1, cache);

        }
        if (i_ray < input[current_depth].length()-1) {
            count += cast_ray(input, current_depth+1, i_ray+1, cache);
        }
    }
    else {
        count += cast_ray(input, current_depth+1, i_ray, cache);
    }
    cache[{current_depth, i_ray}] = count;
    return count;
}


AOC_DAY(Day07_2){
    size_t sum = 0;
    std::string line;
    getline(cin,line);
    int start_pos = line.find('S');
    std::vector<std::string> input;

    while (getline(cin, line)) {
        input.push_back(line);
    }

    std::map<std::pair<size_t,size_t>, size_t> cache;
    sum = cast_ray(input, 0, start_pos, cache);

    return std::to_string(sum);
}
