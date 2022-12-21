template<typename T, size_t N>
struct hash<array<T, N> >
{
    typedef array<T, N> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const
    {
        hash<T> hasher;
        result_type h = 0;
        for (result_type i = 0; i < 3; ++i)
        {
            h = h * 31 + hasher(a[i]);
        }
        return h;
    }
};

AOC_DAY(Day18_1) {
    std::unordered_set<std::array<int, 3>> cubes;
    int x, y, z;
    char c;
    while (cin >> x >> c >> y >> c >>z) {
        cubes.insert({x,y,z});
    }

    int n = 0;
    for (auto it = cubes.begin(); it != cubes.end(); it++) {
        for (int i = 0; i<3; i++) {
            auto coords = *it;
            coords[i]++;
            if (cubes.find(coords) == cubes.end())
                n++;
            coords[i] -= 2;
            if (cubes.find(coords) == cubes.end())
                n++;
        }
    }

    return std::to_string(n);
}

std::vector<std::array<int,3>> get_air_neighbours(std::array<int,3> coords, std::unordered_set<std::array<int, 3>>& visited, std::unordered_set<std::array<int, 3>>& cubes) {
    std::vector<std::array<int,3>> neigh_vector;
    neigh_vector.reserve(3*2);
    for (int i = 0; i<3; i++) {
        coords[i]++;
        neigh_vector.push_back(coords);
        coords[i] -= 2;
        neigh_vector.push_back(coords);
        coords[i]++;
    }
    return neigh_vector;
};


bool search_outside(std::array<int,3> coords, const std::array<int, 3>& maxes, const std::array<int, 3>& mins, std::unordered_set<std::array<int, 3>>& visited, std::unordered_set<std::array<int, 3>>& cubes) {

    for (int i = 0; i<3; i++) {
        if (coords[i] == maxes[i]+1 || coords[i] == mins[i]-1)
            return true;
    }
    for (int i = 0; i<3; i++) {
        coords[i]++;
        if (visited.find(coords) == visited.end() && cubes.find(coords) == cubes.end()) {
            visited.insert(coords);
            if (search_outside(coords, maxes, mins, visited, cubes))
                return true;
        }
        coords[i] -= 2;
        if (visited.find(coords) == visited.end() && cubes.find(coords) == cubes.end()) {
            visited.insert(coords);
            if (search_outside(coords, maxes, mins, visited, cubes))
                return true;
        }
        coords[i]++;
    }
    return false;
}


AOC_DAY(Day18_2) {

    std::unordered_set<std::array<int, 3>> cubes;
    int x, y, z;
    char c;
    int max_x, max_y, max_z;
    int min_x, min_y, min_z;


    while (cin >> x >> c >> y >> c >>z) {
        cubes.insert({x,y,z});
        max_x = max(x, max_x);
        max_y = max(y, max_y);
        max_z = max(z, max_z);
        min_x = min(x, min_x);
        min_y = min(y, min_y);
        min_z = min(z, min_z);
    }
    std::array<int, 3> mins({min_x, min_y, min_z});
    std::array<int, 3> maxes({max_x, max_y, max_z});
    std::unordered_set<std::array<int, 3>> air;

    int n = 0;
    for (auto it = cubes.begin(); it != cubes.end(); it++) {
        for (int i = 0; i<3; i++) {
            std::unordered_set<std::array<int, 3>> visited;
            auto coords = *it;
            coords[i]++;
            if (cubes.find(coords) == cubes.end()) {
                n++;
                if (!search_outside(coords, maxes, mins, visited, cubes))
                    n--;
            }
            coords[i] -= 2;
            visited.clear();
            if (cubes.find(coords) == cubes.end()) {
                n++;
                if (!search_outside(coords, maxes, mins, visited, cubes))
                    n--;
            }
        }
    }

    return std::to_string(n);
}
