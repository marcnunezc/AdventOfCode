#include "main.h"
std::map<std::string, std::function<void()>> DayFactory::Days;
bool DayFactory::Register(std::string name, std::function<void()> func) {
    Days[name] = std::move(func);
    return true;
}

#include "include.h"
int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Please provide day and part in the format: Day##_#" << endl;
        cout << "e.g: aoc22 Day01_1 < Day01/input.txt" << endl;
        exit(1);
    }

    std::string name(argv[1]);
    if (DayFactory::Days.find(name) == DayFactory::Days.end()) {
        cout << "Day with name: " << name << " not found" << endl;
        exit(1);
    } else {
        cout << "Running: " << name  << endl;
        DayFactory::Days[name]();
    }

}
