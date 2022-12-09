struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

void move(int& x, int& y, char dir) {
    if (dir=='R')
        x += 1;
    else if (dir=='L')
        x -= 1;
    else if (dir=='U')
        y += 1;
    else
        y -= 1;
}

void move_tail(int& hx, int& hy, int& tx, int& ty) {
    int new_tx, new_ty;
    if (std::abs(hx - tx) == 2 && std::abs(hy - ty) == 2) {
        if (hx > tx)
            new_tx = hx-1;
        else
            new_tx = hx+1;
        if (hy > ty)
            new_ty = hy-1;
        else
            new_ty = hy+1;
    }
    else {
        if (std::abs(hx - tx) > 0) {
            if (std::abs(hy-ty) > 1)
                new_tx = hx;
            else if (hx > tx)
                new_tx = hx-1;
            else if (hx < tx)
                new_tx = hx+1;
        }

        if (std::abs(hy - ty) > 0) {
            if (std::abs(hx-tx) > 1)
                new_ty = hy;
            else if (hy > ty)
                new_ty = hy-1;
            else if (hy < ty)
                new_ty = hy+1;
        }
    }
    tx = new_tx; ty = new_ty;
}

AOC_DAY(Day09_1) {

    int hx=0, hy=0;
    int tx=0, ty=0;
    char dir;
    int step;
    std::unordered_set<std::pair<int,int>, pair_hash> positions;
    positions.insert({0,0});
    while(cin >> dir >> step) {
        for (int i : std::ranges::iota_view{0,step}) {
            move(hx, hy, dir);
            if (std::abs(hx-tx)>1 || std::abs(hy-ty)>1) {
                move_tail(hx, hy, tx, ty);
                positions.insert({tx,ty});
            }
        }
    }

    return std::to_string(positions.size());
}

AOC_DAY(Day09_2){

    std::vector<std::pair<int, int>> tails(10, {0,0});
    char dir;
    int step;
    std::unordered_set<std::pair<int,int>, pair_hash> positions;
    positions.insert({0,0});
    while(cin >> dir >> step) {
        for (int i : std::ranges::iota_view{0,step}) {
            // first motion
            move(tails[0].first, tails[0].second, dir);
            for (int j = 1; j<tails.size(); j++) {
                int& hx=tails[j-1].first;
                int& hy=tails[j-1].second;
                int& tx=tails[j].first;
                int& ty=tails[j].second;
                if (std::abs(hx-tx)>1 || std::abs(hy-ty)>1) {
                    move_tail(hx, hy, tx, ty);
                    if (j == tails.size()-1)
                        positions.insert({tails.back().first, tails.back().second});
                }
            }
        }
    }

    return std::to_string(positions.size());
}
