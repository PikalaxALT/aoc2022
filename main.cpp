#include <iostream>
#include <string>
#include "aoc2022.h"

int main(int argc, char ** argv) {
    static const std::string usage = "usage: aoc2022 [DAY] [PART] [FILENAME]";

    if (argc < 4) {
        std::cerr << usage << std::endl;
        return 1;
    }
    int day, part;
    try {
        day = std::stoi(argv[1]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "malformatted day (should be an int between 1 and 25 inclusive)\n" << usage << std::endl;
        return 1;
    }
    try {
        part = std::stoi(argv[2]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "malformatted part (accepted values are 1 or 2)\n" << usage << std::endl;
        return 1;
    }
    std::string filename(argv[3]);
    if (day < 1 || day > 25) {
        std::cerr << "day out of range (1-25)" << std::endl;
        return 1;
    }
    if (part != 1 && part != 2) {
        std::cerr << "part out of range (1-2)" << std::endl;
        return 1;
    }
    try {
        return aoc2022::run_solution(day, part, filename);
    } catch (io_failure const& e) {
        std::cerr << filename << ": no such file or directory" << std::endl;
        return 1;
    }
}
