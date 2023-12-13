AOC_DAY(Day13_1){
    std::size_t sum = 0;
    std::vector<std::vector<std::vector<int>>> ash_rock_list;
    std::vector<std::vector<int>> ash_rock_matrix;
    std::string line;

    while(getline(cin, line)) {
        if (line.empty()) {
            ash_rock_list.push_back(ash_rock_matrix);
            ash_rock_matrix.clear();
            continue;
        }

        std::vector<int> ash_rock_line;
        for (auto c : line) {
            if (c == '#')
                ash_rock_line.push_back(1);
            else
                ash_rock_line.push_back(0);
        }
        ash_rock_matrix.push_back(ash_rock_line);
    }
    ash_rock_list.push_back(ash_rock_matrix);

    for (auto& matrix : ash_rock_list)  {
        bool failed_symmetry = false;
        // vertical symmetry
        for (int j = 1; j<matrix[0].size(); j++) {
            int right_ptr = j;
            int left_ptr = j-1;
            failed_symmetry = false;
            while (left_ptr>=0  && right_ptr <matrix[0].size() && !failed_symmetry) {
                for (int i=0; i<matrix.size(); i++) {
                    if (matrix[i][left_ptr] != matrix[i][right_ptr]) {
                        failed_symmetry = true;
                        break;
                    }
                }
                left_ptr--;
                right_ptr++;
            }
            if (!failed_symmetry) {
                sum += j;
                break;
            }
        }
        if (!failed_symmetry)
            continue;

        // horizontal symmetry
        for (int i = 1; i<matrix.size(); i++) {
            int down_ptr = i;
            int up_ptr = i-1;
            failed_symmetry = false;
            while (up_ptr>=0  && down_ptr <matrix.size() && !failed_symmetry) {
                for (int j=0; j<matrix[0].size(); j++) {
                    if (matrix[down_ptr][j] != matrix[up_ptr][j]) {
                        failed_symmetry = true;
                        break;
                    }
                }
                up_ptr--;
                down_ptr++;
            }
            if (!failed_symmetry) {
                sum += i*100;
                break;
            }
        }
    }
    return std::to_string(sum);
}

AOC_DAY(Day13_2){
    std::size_t sum = 0;
    std::vector<std::vector<std::vector<int>>> ash_rock_list;
    std::vector<std::vector<int>> ash_rock_matrix;
    std::string line;

    while(getline(cin, line)) {
        if (line.empty()) {
            ash_rock_list.push_back(ash_rock_matrix);
            ash_rock_matrix.clear();
            continue;
        }

        std::vector<int> ash_rock_line;
        for (auto c : line) {
            if (c == '#')
                ash_rock_line.push_back(1);
            else
                ash_rock_line.push_back(0);
        }
        ash_rock_matrix.push_back(ash_rock_line);
    }
    ash_rock_list.push_back(ash_rock_matrix);

    for (auto& matrix : ash_rock_list)  {
        bool failed_symmetry = false;
        int previous_i = -1;
        int previous_j = -1;
        // vertical symmetry
        for (int j = 1; j<matrix[0].size(); j++) {
            int right_ptr = j;
            int left_ptr = j-1;
            failed_symmetry = false;
            while (left_ptr>=0  && right_ptr <matrix[0].size() && !failed_symmetry) {
                for (int i=0; i<matrix.size(); i++) {
                    if (matrix[i][left_ptr] != matrix[i][right_ptr]) {
                        failed_symmetry = true;
                        break;
                    }
                }
                left_ptr--;
                right_ptr++;
            }
            if (!failed_symmetry) {
                previous_j = j;
                break;
            }
        }
        if (failed_symmetry) {
            // horizontal symmetry
            for (int i = 1; i<matrix.size(); i++) {
                int down_ptr = i;
                int up_ptr = i-1;
                failed_symmetry = false;
                while (up_ptr>=0  && down_ptr <matrix.size() && !failed_symmetry) {
                    for (int j=0; j<matrix[0].size(); j++) {
                        if (matrix[down_ptr][j] != matrix[up_ptr][j]) {
                            failed_symmetry = true;
                            break;
                        }
                    }
                    up_ptr--;
                    down_ptr++;
                }
                if (!failed_symmetry) {
                    previous_i = i;
                    break;
                }
            }
        }
        failed_symmetry = false;
        for (int m = 0; m<matrix.size(); m++) {
            for (int n = 0; n<matrix[m].size(); n++) {
                matrix[m][n] = !matrix[m][n];
                failed_symmetry = false;
                for (int j = 1; j<matrix[0].size(); j++) {
                    int right_ptr = j;
                    int left_ptr = j-1;
                    failed_symmetry = false;
                    while (left_ptr>=0  && right_ptr <matrix[0].size() && !failed_symmetry) {
                        for (int i=0; i<matrix.size(); i++) {
                            if (matrix[i][left_ptr] != matrix[i][right_ptr]) {
                                failed_symmetry = true;
                                break;
                            }
                        }
                        left_ptr--;
                        right_ptr++;
                    }
                    if (!failed_symmetry && j != previous_j) {
                        sum += j;
                        break;
                    } else {
                        failed_symmetry = true;
                    }
                }
                if (failed_symmetry) {
                    // horizontal symmetry
                    for (int i = 1; i<matrix.size(); i++) {
                        int down_ptr = i;
                        int up_ptr = i-1;
                        failed_symmetry = false;
                        while (up_ptr>=0  && down_ptr <matrix.size() && !failed_symmetry) {
                            for (int j=0; j<matrix[0].size(); j++) {
                                if (matrix[down_ptr][j] != matrix[up_ptr][j]) {
                                    failed_symmetry = true;
                                    break;
                                }
                            }
                            up_ptr--;
                            down_ptr++;
                        }
                        if (!failed_symmetry && i != previous_i) {
                            sum += i*100;
                            break;
                        } else {
                            failed_symmetry = true;
                        }
                    }
                }

                matrix[m][n] = !matrix[m][n];
                if (!failed_symmetry)
                    break;
            }
            if (!failed_symmetry)
                    break;
        }
    }
    return std::to_string(sum);
}