struct Button {
    int x;
    int y;
};

struct Prize {
    int x;
    int y;
};

struct Claw {
    Button buttonA;
    Button buttonB;
    Prize prize;
};

AOC_DAY(Day13_1) {
    std::string line;
    std::vector<Claw> machines;
    std::size_t sum = 0;

    while (getline(cin, line)) {
        if (line.find("Button A:") != std::string::npos) {
            Claw claw;
            sscanf(line.c_str(), "Button A: X+%d, Y+%d", &claw.buttonA.x, &claw.buttonA.y);

            // Parse Button B
            getline(cin, line);
            sscanf(line.c_str(), "Button B: X+%d, Y+%d", &claw.buttonB.x, &claw.buttonB.y);

            // Parse Prize
            getline(cin, line);
            sscanf(line.c_str(), "Prize: X=%d, Y=%d", &claw.prize.x, &claw.prize.y);

            machines.push_back(claw);
        }
    }

    for (auto& claw : machines) {
        std::size_t max_presses = 100;

        long int a1,b1,a2,b2,c1,c2;
        a1=claw.buttonA.x;
        b1=claw.buttonB.x;
        a2=claw.buttonA.y;
        b2=claw.buttonB.y;
        c1=claw.prize.x;
        c2=claw.prize.y;
        auto num_i = b2*c1-b1*c2;
        auto num_j = a1*c2-a2*c1;
        auto den = a1*b2-b1*a2;
        if ((num_i) % (den) == 0 && (num_j) % (den) == 0 ){
            auto i = num_i/den;
            auto j = num_j/den;
            if (i<= max_presses && j <= max_presses)
                sum += 3*i+j;
        }
    }


    return std::to_string(sum);
}

AOC_DAY(Day13_2){
    std::string line;
    std::vector<Claw> machines;
    std::size_t sum = 0;

    while (getline(cin, line)) {
        if (line.find("Button A:") != std::string::npos) {
            Claw claw;
            sscanf(line.c_str(), "Button A: X+%d, Y+%d", &claw.buttonA.x, &claw.buttonA.y);

            // Parse Button B
            getline(cin, line);
            sscanf(line.c_str(), "Button B: X+%d, Y+%d", &claw.buttonB.x, &claw.buttonB.y);

            // Parse Prize
            getline(cin, line);
            sscanf(line.c_str(), "Prize: X=%d, Y=%d", &claw.prize.x, &claw.prize.y);

            machines.push_back(claw);
        }
    }

    for (auto& claw : machines) {
        long int a1,b1,a2,b2,c1,c2;
        a1=claw.buttonA.x;
        b1=claw.buttonB.x;
        a2=claw.buttonA.y;
        b2=claw.buttonB.y;
        c1=claw.prize.x + 10000000000000;
        c2=claw.prize.y + 10000000000000;
        auto num_i = b2*c1-b1*c2;
        auto num_j = a1*c2-a2*c1;
        auto den = a1*b2-b1*a2;
        if ((num_i) % (den) == 0 && (num_j) % (den) == 0 ){
            auto i = num_i/den;
            auto j = num_j/den;
            sum += 3*i+j;
        }
    }


    return std::to_string(sum);
}
