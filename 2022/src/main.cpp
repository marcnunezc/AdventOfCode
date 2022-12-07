#include "main.h"
#include <chrono>
std::map<std::string, std::function<std::string()>> DayFactory::Days;
bool DayFactory::Register(std::string name, std::function<std::string()> func) {
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

    print_header();

    if (argc != 2) {
        cout << "Please provide day and part in the format: Day##_#" << endl;
        cout << "e.g: aoc22 Day01_1 < Day01/input.txt" << endl;
        cout << "Use -l to list all days" << endl;
        cout << "Use -a to run all days" << endl;
        exit(1);
    }

    std::string name(argv[1]);
    if (!strcmp(argv[1], "-l")) {
        for (auto it = DayFactory::Days.begin(); it != DayFactory::Days.end(); it++) {
            cout << it->first << endl;
        }
        return 0;
    }
    if (!strcmp(argv[1], "-a")) {
        for (auto it = DayFactory::Days.begin(); it != DayFactory::Days.end(); it++) {
            cout << "Running " << it->first << " ";
            std::string basename = it->first.substr(0, 5);
            std::string input_file(basename+"/input.txt");
            std::ifstream in(input_file);
            std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
            auto start = std::chrono::high_resolution_clock::now();
            cout << it->second() << " ";
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::milli>(stop - start);
            cout << "Time: " << duration.count() << " ms"<<endl;
        }
        return 0;
    }
    if (DayFactory::Days.find(name) == DayFactory::Days.end()) {
        cout << "Day with name: " << name << " not found" << endl;
        exit(1);
    } else {
        cout << "Running: " << name  << endl;
        auto start = std::chrono::high_resolution_clock::now();
        cout << DayFactory::Days[name]() << endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(stop - start);
        cout << "Time: " << duration.count() << " ms"<<endl;
    }

}
