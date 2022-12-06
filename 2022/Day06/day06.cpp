void compute_day_06_solution(size_t packet_length) {
    std::string line;
    getline(cin, line);
    size_t i;
    for (i = 0; i<line.length(); i++) {
        std::map<char, size_t> packet_marker;
        for (size_t j=0; j<packet_length; j++) {
            packet_marker[line[i+j]]=i+j;
        }
        if (packet_marker.size() == packet_length) {
            break;
        }
    }
    cout << i+packet_length << endl;
}

AOC_DAY(Day06_1){
    compute_day_06_solution(4);
}

AOC_DAY(Day06_2) {
    compute_day_06_solution(14);
}
