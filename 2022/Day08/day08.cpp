void check_row_column_visibility(int i, std::vector<std::string> tree_array, std::vector<std::vector<bool>>& visited) {

    int max_size = tree_array.size();
    // left to right
    int max=tree_array[i][0];
    for (int j : std::ranges::iota_view{0, max_size}) {
        if (tree_array[i][j]>max) {
            max=tree_array[i][j];
            visited[i][j]=true;
        }
    }

    // right to left
    max=tree_array[i][max_size-1];
    for (int j : std::ranges::iota_view{0, max_size} | std::views::reverse) {
        if (tree_array[i][j]>max) {
            max=tree_array[i][j];
            visited[i][j]=true;
        }
    }

    // top to bottom
    max=tree_array[0][i];
    for (int j : std::ranges::iota_view{0, max_size}) {
        if (tree_array[j][i]>max) {
            max=tree_array[j][i];
            visited[j][i]=true;
        }
    }

    // bottom to top
    max=tree_array[max_size-1][i];
    for (int j : std::ranges::iota_view{0, max_size} | std::views::reverse) {
        if (tree_array[j][i]>max) {
            max=tree_array[j][i];
            visited[j][i]=true;
        }
    }
}

int compute_dist(size_t i, size_t j, std::vector<std::string> tree_array) {
    int value = tree_array[i][j];
    int dist = 1;
    size_t start = 0;

    //left
    int trees = 0;
    for (size_t m : std::ranges::iota_view{start, i} | std::views::reverse) {
        trees++;
        if (tree_array[m][j]>=value || m == 0) {
            dist *= trees;
            break;
        }
    }

    //right
    trees = 0;
    for (size_t m : std::ranges::iota_view{i+1, tree_array.size()}) {
        trees++;
        if (tree_array[m][j]>=value || m == tree_array.size()-1) {
            dist *= trees;
            break;
        }
    }

    //up
    trees = 0;
    for (size_t m : std::ranges::iota_view{start, j} | std::views::reverse) {
        trees++;
        if (tree_array[i][m]>=value || m == 0) {
            dist *= trees;
            break;
        }
    }

    //down
    trees = 0;
    for (size_t m : std::ranges::iota_view{j+1, tree_array.size()}) {
        trees++;
        if (tree_array[i][m]>=value || m == tree_array.size()-1) {
            dist *= trees;
            break;
        }
    }

    return dist;
}


AOC_DAY(Day08_1){

    std::vector<std::string> tree_array;
    std::string line;
    int count=0;
    while(getline(cin, line)) {
        tree_array.push_back(line);
    }
    std::vector<std::vector<bool>> visited(tree_array.size(), std::vector<bool>(tree_array[0].length(), false));
    for (int i=1; i<tree_array.size()-1; i++) {
        check_row_column_visibility(i, tree_array, visited);
    }

    for (auto vec : visited) {
        for(bool val : vec)
            count += val;
    }

    return std::to_string(count+(tree_array.size()-1)*4);
}

AOC_DAY(Day08_2) {

    std::vector<std::string> tree_array;
    std::string line;
    int max_dist=0;
    while(getline(cin, line)) {
        tree_array.push_back(line);
    }
    for (int i=1; i<tree_array.size()-1; i++)
    {
        for (int j = 1; j<tree_array[i].length()-1; j++) {
            max_dist = max(max_dist, compute_dist(i, j, tree_array));
        }
    }

    return std::to_string(max_dist);
}
