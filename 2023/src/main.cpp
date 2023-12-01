#include "main.h"
#include <chrono>
std::map<std::string, std::function<std::string(RUN_MODE)>> DayFactory::Days;
bool DayFactory::Register(std::string name, std::function<std::string(RUN_MODE)> func) {
    Days[name] = std::move(func);
    return true;
}

void print_header() {
    cout << "    ___   ____  _________  _____"     << endl;
    cout << "   /   | / __ \\/ ____/__ \\|__  /" << endl;
    cout << "  / /| |/ / / / /    __/ / /_ <"    << endl;
    cout << " / ___ / /_/ / /___ / __/___/ /"     << endl;
    cout << "/_/  |_\\____/\\____//____/____/"   << endl;
}

#include "include.h"
int main(int argc, char *argv[]) {

    print_header();

    if (argc != 2) {
        cout << "Please provide day and part in the format: Day##_#" << endl;
        cout << "Use -l to list all days" << endl;
        cout << "Use -a to run all days" << endl;
        cout << "e.g: aoc23 Day01_1 < Day01/input.txt" << endl;
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
            std::string output = it->second(RUN_MODE::ALL);
            cout << output << " ";
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::milli>(stop - start);
            std::string ok = expected_input[it->first].compare(output)==0 ? "\033[1m\033[32mOK\033[0m" : "\033[1m\033[31mFAILED\033[0m" ;
            cout << "Time: " << duration.count() << " ms "<< ok << endl;
        }
        return 0;
    }
    if (DayFactory::Days.find(name) == DayFactory::Days.end()) {
        cout << "Day with name: " << name << " not found" << endl;
        exit(1);
    } else {
        cout << "Running: " << name  << endl;
        auto start = std::chrono::high_resolution_clock::now();
        cout << DayFactory::Days[name](RUN_MODE::RUN) << endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(stop - start);
        cout << "Time: " << duration.count() << " ms"<<endl;
    }

}
