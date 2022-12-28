#include <functional>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <numeric>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <cmath>

using namespace std;

enum RUN_MODE {
    RUN,
    ALL,
    TEST
};


#define AOC_DAY(name) \
    std::string day_##name(RUN_MODE run_mode); \
    static bool day_##name##_registered = DayFactory::Register(#name, &day_##name); \
    std::string day_##name(RUN_MODE run_mode)

class DayFactory {
public:
    static bool Register(std::string name, std::function<std::string(RUN_MODE)> func);
    static std::map<std::string, std::function<std::string(RUN_MODE)>> Days;
};