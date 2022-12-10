bool check_valid_cycle(int cycle) {

    for (int i : std::ranges::iota_view(0,64)) {
        int value = 40*i+20;
        if (cycle < value || value > 220)
            return false;
        else if (cycle == value)
            return true;
    }
    return false;
}

AOC_DAY(Day10_1) {

    int cycle=1, x=1, signal_strength=0;
    std::string line;
    while (getline(cin, line)) {
        if (line[0] == 'n') {
            cycle++;
        }
        else {
            cycle++;
            if (check_valid_cycle(cycle)) {
                signal_strength += cycle*x;
            }
            cycle++;
            int add;
            sscanf(line.c_str(), "addx %i", &add);
            x+=add;
        }
        if (check_valid_cycle(cycle)) {
            signal_strength += cycle*x;
        }
    }

    return std::to_string(signal_strength);
}

void draw_pixel(int cycle, int x) {
    int position = cycle%40-1;

    char output = std::abs(position-x) < 2 ? '#' : '.';
    if (std::abs(position-x)  == 39)
        output='#';
    cout << output;
    if (cycle % 40 == 0)
        cout << endl;
}

AOC_DAY(Day10_2){

    int cycle=1, x=1, signal_strength=0;
    std::string line;
    while (getline(cin, line)) {
        if (line[0] == 'n') {
            draw_pixel(cycle, x);
            cycle++;
        }
        else {
            draw_pixel(cycle, x);
            cycle++;
            draw_pixel(cycle, x);
            cycle++;
            int add;
            sscanf(line.c_str(), "addx %i", &add);
            x+=add;
        }
    }

    return "ELPLZGZL";
}
