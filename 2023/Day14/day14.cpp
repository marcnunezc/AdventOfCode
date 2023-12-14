void shift_north(std::vector<string>& matrix) {
    for (int i = 1; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            if (matrix[i][j]=='O') {
                for (int row_down=i-1; row_down>=0; row_down--) {
                    if (matrix[row_down][j]=='.') {
                        matrix[row_down][j] = 'O';
                        matrix[row_down+1][j] = '.';
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

void shift_west(std::vector<string>& matrix) {
    for (int i = 0; i<matrix.size(); i++) {
        for (int j=1; j<matrix[i].size(); j++) {
            if (matrix[i][j]=='O') {
                for (int column_down=j-1; column_down>=0; column_down--) {
                    if (matrix[i][column_down]=='.') {
                        matrix[i][column_down] = 'O';
                        matrix[i][column_down+1] = '.';
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

void shift_south(std::vector<string>& matrix) {
    for (int i = matrix.size()-2; i>=0; i--) {
        for (int j=0; j<matrix[i].size(); j++) {
            if (matrix[i][j]=='O') {
                for (int row_up=i+1; row_up<matrix[i].size(); row_up++) {
                    if (matrix[row_up][j]=='.') {
                        matrix[row_up][j] = 'O';
                        matrix[row_up-1][j] = '.';
                    } else {
                        break;
                    }
                }
            }
        }
    }
}


void shift_east(std::vector<string>& matrix) {
    for (int i = 0; i<matrix.size(); i++) {
        for (int j=matrix[i].size()-2; j>=0; j--) {
            if (matrix[i][j]=='O') {
                for (int column_up=j+1; column_up<matrix[i].size(); column_up++) {
                    if (matrix[i][column_up]=='.') {
                        matrix[i][column_up] = 'O';
                        matrix[i][column_up-1] = '.';
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

std::size_t get_north_load(std::vector<string>& matrix) {
    std::size_t sum = 0;
    int multiplier = matrix.size();
    for (auto& row : matrix) {
        sum += std::count(row.begin(), row.end(), 'O')*multiplier--;
    }
    return sum;
}

AOC_DAY(Day14_1){
    std::vector<string> matrix;
    std::string line;
    while(getline(cin, line)) {
        matrix.push_back(line);
    }

    shift_north(matrix);

    return std::to_string(get_north_load(matrix));
}

AOC_DAY(Day14_2){
    std::vector<string> matrix;
    std::string line;
    while(getline(cin, line)) {
        matrix.push_back(line);
    }

    std::size_t aim=1000000000;
    int initial_cycles=150;
    int check_size=5;

    // initial cycles to reach repeating pattern
    for (int cycles=0; cycles<initial_cycles; cycles++) {
        shift_north(matrix); shift_west(matrix); shift_south(matrix); shift_east(matrix);
    }

    // start with a vector of N values (check_size)
    std::vector<int> check_values(check_size, 0);
    for (int cycles=0; cycles<check_size; cycles++) {
        shift_north(matrix); shift_west(matrix); shift_south(matrix); shift_east(matrix);

        check_values[cycles] = get_north_load(matrix);
    }


    // fill second vector until both vector match
    std::vector<int> to_check(check_size, 0);
    for (int cycles=0; cycles<check_size; cycles++) {
        shift_north(matrix); shift_west(matrix); shift_south(matrix); shift_east(matrix);

        to_check[cycles] = get_north_load(matrix);
    }
    int steps = 0;
    while (to_check != check_values) {
        steps++;
        shift_north(matrix); shift_west(matrix); shift_south(matrix); shift_east(matrix);
        for (int j = 0; j < to_check.size()-1; j++) {
            to_check[j] = to_check[j+1];
        }
        to_check[to_check.size()-1]=get_north_load(matrix);
    }

    // detected pattern, compute missing steps
    auto reminder = (aim-initial_cycles-check_size) % (check_size+steps);

    // run missing steps
    for (int cycles=0; cycles<reminder; cycles++) {
        shift_north(matrix); shift_west(matrix); shift_south(matrix); shift_east(matrix);
        to_check[to_check.size()-1]=get_north_load(matrix);
    }

    return std::to_string(to_check.back());
}