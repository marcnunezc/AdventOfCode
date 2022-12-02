AOC_DAY(Day02_1){

    std::map<char, int> score = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };

    std::map<std::pair<char, char>, int> win_score = {
        {{'A','X'}, 3},
        {{'A','Y'}, 6},
        {{'A','Z'}, 0},
        {{'B','X'}, 0},
        {{'B','Y'}, 3},
        {{'B','Z'}, 6},
        {{'C','X'}, 6},
        {{'C','Y'}, 0},
        {{'C','Z'}, 3},
    };

    char him, me;
    int total = 0;
    while (cin >> him) {
        cin >> me;
        total += win_score[{him, me}] + score[me];
    }
    cout << total << endl;
}

AOC_DAY(Day02_2){

    std::map<char, int> score = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };

    std::map<char, int> action = {
        {'X', 0},
        {'Y', 3},
        {'Z', 6}
    };

    std::map<std::pair<char, char>, int> selected_move = {
        {{'A','X'}, 'Z'},
        {{'A','Y'}, 'X'},
        {{'A','Z'}, 'Y'},
        {{'B','X'}, 'X'},
        {{'B','Y'}, 'Y'},
        {{'B','Z'}, 'Z'},
        {{'C','X'}, 'Y'},
        {{'C','Y'}, 'Z'},
        {{'C','Z'}, 'X'},
    };

    char him, expected;
    int total = 0;
    while (cin >> him) {
        cin >> expected;
        char move = selected_move[{him, expected}];
        total += action[expected] + score[move];
    }
    cout << total << endl;
}
