bool is_visible(size_t i, size_t j, std::vector<std::string> tree_array) {
    int value = tree_array[i][j];

    bool blocked = false;
    size_t start=0;
    for (size_t m : std::ranges::iota_view{start, i} | std::views::reverse) {
        if (tree_array[m][j]>=value) {
            blocked = true;
            break;
        }
    }
    if (!blocked) return true;

    //right
    blocked = false;
    for (size_t m : std::ranges::iota_view{i+1, tree_array.size()}) {
        if (tree_array[m][j]>=value) {
            blocked = true;
            break;
        }
    }
    if (!blocked) return true;

    //up
    blocked = false;
    for (size_t m : std::ranges::iota_view{start, j} | std::views::reverse) {
        if (tree_array[i][m]>=value) {
            blocked = true;
            break;
        }
    }
    if (!blocked) return true;

    //down
    blocked = false;
    for (size_t m : std::ranges::iota_view{j+1, tree_array.size()}) {
        if (tree_array[i][m]>=value) {
            blocked = true;
            break;
        }
    }
    if (!blocked) return true;

    return false;
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
    for (int i=1; i<tree_array.size()-1; i++)
    {
        for (int j = 1; j<tree_array[i].length()-1; j++) {
            if (is_visible(i,j, tree_array))
                count++;
        }
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
