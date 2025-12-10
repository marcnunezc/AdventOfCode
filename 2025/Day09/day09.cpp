struct Tile {
    long x,y;
};


size_t compute_area(Tile& a, Tile& b) {
    auto dx = std::abs(a.x - b.x)+1;
    auto dy = std::abs(a.y - b.y)+1;

    return dx*dy ;
}


AOC_DAY(Day09_1) {

    std::size_t sum = 0;
    std::string line;

    std::vector<Tile> tiles_vector;
    while (getline(cin, line)) {
        Tile tile;
        sscanf(line.c_str(),"%ld,%ld", &tile.x, &tile.y);
        tiles_vector.push_back(tile);
    }
    std::map<std::pair<size_t, size_t>, size_t> area_map;

    for (int i = 0; i<tiles_vector.size(); i++) {
        for (int j = i+1; j<tiles_vector.size(); j++) {
            area_map[{i,j}] = compute_area(tiles_vector[i], tiles_vector[j]);
        }
    }

    auto it = std::max_element(area_map.begin(),area_map.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );
    auto max_area = it->second;

    return std::to_string(max_area);
}

bool check_if_dot_is_inside(long x, long y, long max_x, long max_y, long min_x, long min_y, std::set<std::pair<size_t,size_t>>& edges, std::vector<Tile>& tiles_vector)
{
    bool rayLeft  = false;
    bool rayRight = false;
    bool rayUp    = false;
    bool rayDown  = false;

    for (auto& edge : edges) {
        Tile a = tiles_vector[edge.first];
        Tile b = tiles_vector[edge.second];

        // vertical
        if (a.x == b.x) {
            long y1 = std::min(a.y, b.y);
            long y2 = std::max(a.y, b.y);

            if (y >= y1 && y <= y2) {
                if (a.x >= min_x && a.x <= x)
                    rayLeft = true;

                if (a.x >= x && a.x <= max_x)
                    rayRight = true;
            }
        }

        // horizontal
        else if (a.y == b.y) {
            long x1 = std::min(a.x, b.x);
            long x2 = std::max(a.x, b.x);

            if (x >= x1 && x <= x2) {
                if (a.y >= min_y && a.y <= y)
                    rayUp = true;

                if (a.y >= y && a.y <= max_y)
                    rayDown = true;
            }
        }

        if (rayLeft && rayRight && rayUp && rayDown)
            return true;
    }

    return rayLeft && rayRight && rayUp && rayDown;
}


bool check_if_all_dots_are_inside(Tile& a, Tile& b, const long max_x, const long max_y, const long min_x, const long min_y, std::set<std::pair<size_t,size_t>>& edges, std::vector<Tile>& tiles_vector) {

    //check first all 4 corners of the rectangle:
    if (!check_if_dot_is_inside(std::min(a.x, b.x), std::min(a.y, b.y), max_x, max_y, min_x, min_y, edges, tiles_vector))
        return false;
    if (!check_if_dot_is_inside(std::min(a.x, b.x), std::max(a.y, b.y), max_x, max_y, min_x, min_y, edges, tiles_vector))
        return false;
    if (!check_if_dot_is_inside(std::max(a.x, b.x), std::min(a.y, b.y), max_x, max_y, min_x, min_y, edges, tiles_vector))
        return false;
    if (!check_if_dot_is_inside(std::max(a.x, b.x), std::max(a.y, b.y), max_x, max_y, min_x, min_y, edges, tiles_vector))
        return false;

    for (int x = std::min(a.x, b.x); x <= std::max(a.x, b.x); x++) {
        if (!check_if_dot_is_inside(x, a.y, max_x, max_y, min_x, min_y, edges,tiles_vector))
            return false;
        if (!check_if_dot_is_inside(x, b.y, max_x, max_y, min_x, min_y, edges,tiles_vector))
            return false;
    }
    for (int y = std::min(a.y, b.y); y <= std::max(a.y, b.y); y++) {
        if (!check_if_dot_is_inside(a.x, y, max_x, max_y, min_x, min_y, edges, tiles_vector))
            return false;
        if (!check_if_dot_is_inside(b.x, y, max_x, max_y, min_x, min_y, edges, tiles_vector))
            return false;
    }

    return true;
}

AOC_DAY(Day09_2) {
    std::size_t sum = 0;
    std::string line;

    std::vector<Tile> tiles_vector;
    std::set<std::pair<size_t,size_t>> edges;
    std::map<std::pair<size_t, size_t>, size_t> area_map;
    long max_x=0, max_y=0;
    long min_x=1e9, min_y=1e9;
    while (getline(cin, line)) {
        Tile tile;
        sscanf(line.c_str(),"%ld,%ld", &tile.x, &tile.y);
        tiles_vector.push_back(tile);

        max_x = std::max(max_x, tile.x);
        max_y = std::max(max_y, tile.y);
        min_x = std::min(min_x, tile.x);
        min_y = std::min(min_y, tile.y);
    }

    max_y += 1;
    max_x += 1;
    min_x -= 1;
    min_y -= 1;

    for (int i = 0; i < tiles_vector.size(); i++) {
        int i_pair = i == tiles_vector.size()-1 ? 0: i+1;
        edges.insert({i, i_pair});
    }

    for (int i = 0; i<tiles_vector.size(); i++) {
        for (int j = i+1; j<tiles_vector.size(); j++) {
            if (check_if_all_dots_are_inside(tiles_vector[i], tiles_vector[j], max_x, max_y, min_x, min_y, edges, tiles_vector))
            area_map[{i,j}] = compute_area(tiles_vector[i], tiles_vector[j]);
        }
    }

    auto it = std::max_element(area_map.begin(),area_map.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );
    auto max_area = it->second;

    return std::to_string(max_area);
}
