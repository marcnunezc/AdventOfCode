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

using namespace std;

#define AOC_DAY(name) \
    std::string day_##name(); \
    static bool day_##name##_registered = DayFactory::Register(#name, &day_##name); \
    std::string day_##name()

class DayFactory {
public:
    static bool Register(std::string name, std::function<std::string()> func);
    static std::map<std::string, std::function<std::string()>> Days;
};