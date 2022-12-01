#include "main.h"
std::map<std::string, std::function<void()>> DayFactory::Days;
bool DayFactory::Register(std::string name, std::function<void()> func) {
    Days[name] = std::move(func);
    return true;
}

void print_header() {
    cout << "    ___   ____  _________  ___"     << endl;
    cout << "   /   | / __ \\/ ____/__ \\|__ \\" << endl;
    cout << "  / /| |/ / / / /    __/ /__/ /"    << endl;
    cout << " / ___ / /_/ / /___ / __// __/"     << endl;
    cout << "/_/  |_\\____/\\____//____/____/"   << endl;
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
        print_header();
        cout << "Running: " << name  << endl;
        DayFactory::Days[name]();
    }

}
