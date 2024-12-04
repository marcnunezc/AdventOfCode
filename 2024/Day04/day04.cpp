std::size_t searchNextChar(std::vector<std::string>& matrix, int i, int j, char current, int dx, int dy) {
    if (i < 0 || i >= matrix.size())
        return 0;
    if (j < 0 || j >= matrix[0].size())
        return 0;

    char next;
    if (current == 'M')
        next='A';
    else if (current == 'A')
        next='S';

    if (matrix[i][j] == current) {
        if (current != 'S') {
            return searchNextChar(matrix, i+dx, j+dy, next, dx, dy);
        }
        else {
            return 1;
        }
    }
    return 0;
}

AOC_DAY(Day04_1){

    std::string line;
    std::size_t sum = 0;
    std::vector<std::string> matrix;
    matrix.reserve(140);
    while(getline(cin, line)) {
        matrix.push_back(line);
    }

    for (std::size_t i = 0; i<matrix.size(); i++) {
        auto found = matrix[i].find('X');
        while (found != string::npos)
        {
            int j = (int) found;
            for (int dx = -1; dx < 2; dx++) {
                for (int dy = -1; dy < 2; dy++) {
                    if (dy == 0 && dx == 0)
                        continue;
                    sum += searchNextChar(matrix, i+dx, j+dy, 'M', dx, dy);
                }
            }
            found = matrix[i].find('X', found+1);
        }
    }

    return std::to_string(sum);
}

AOC_DAY(Day04_2){

    std::string line;
    std::size_t sum = 0;
    std::vector<std::string> matrix;
    matrix.reserve(140);
    while(getline(cin, line)) {
        matrix.push_back(line);
    }

    std::array<std::pair<int, int>, 4> corners = {{
                                                    {-1, -1},
                                                    {1, 1},
                                                    {-1, 1},
                                                    {1, -1},
                                                  }};

    for (std::size_t i = 1; i<matrix.size()-1; i++) {
        auto found = matrix[i].find('A');
        while (found != string::npos)
        {
            int j = (int) found;
            if (j == 0 || j == matrix[0].size()-1) {
                found = matrix[i].find('A', found+1);
                continue;
            }
            // upper left
            char ul = matrix[i+corners[0].first][j+corners[0].second];
            // down right
            char dr = matrix[i+corners[1].first][j+corners[1].second];
            // upper right
            char ur = matrix[i+corners[2].first][j+corners[2].second];
            // down left
            char dl = matrix[i+corners[3].first][j+corners[3].second];

            auto is_diagonal_valid = [](char a, char b) {
                return (a == 'M' && b == 'S') || (a == 'S' && b == 'M');
            };

            if  (is_diagonal_valid(ul, dr) && is_diagonal_valid(ur, dl))
            {
                sum++;
            }
            found = matrix[i].find('A', found+1);
        }
    }


    return std::to_string(sum);
}
