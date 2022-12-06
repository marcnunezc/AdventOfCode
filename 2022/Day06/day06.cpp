std::size_t compute_day_06_solution(size_t packet_length) {
    std::string line;
    getline(cin, line);
    std::deque<char> packet_marker;
    std::unordered_map<char, size_t> counters;
    size_t counter=0;
    for (size_t i=0; i < line.length(); i++) {
        packet_marker.push_back(line[i]);
        if (counters[line[i]]++ == 0) {
            counter++;
        }
        if (counter == packet_length)
            return i+1;
        if (packet_marker.size() == packet_length) {
            if (--counters[packet_marker.front()]==0) {
                counter--;
            }
            packet_marker.pop_front();
        }
    }
    return -1;
}

AOC_DAY(Day06_1){
    return std::to_string(compute_day_06_solution(4));
}

AOC_DAY(Day06_2) {
    return std::to_string(compute_day_06_solution(14));
}
