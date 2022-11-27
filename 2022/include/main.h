#include <functional>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#define AOC_DAY(name) \
    void day_##name(); \
    static bool day_##name##_registered = DayFactory::Register(#name, &day_##name); \
    void day_##name()

class DayFactory {
public:
    static bool Register(std::string name, std::function<void()> func);
    static std::map<std::string, std::function<void()>> Days;
};