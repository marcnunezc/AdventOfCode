void compute_day_06_solution(size_t packet_length) {
    std::string line;
    getline(cin, line);
    size_t i;
    std::unordered_set<char> packet_marker;
    for (i = 0; i<line.length(); i++) {
        for (size_t j=0; j<packet_length; j++) {
            packet_marker.insert(line[i+j]);
        }
        if (packet_marker.size() == packet_length) {
            break;
        }
        packet_marker.clear();
    }
    cout << i+packet_length << endl;
}

AOC_DAY(Day06_1){
    compute_day_06_solution(4);
}

AOC_DAY(Day06_2) {
    compute_day_06_solution(14);
}
