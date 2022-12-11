#include <iostream>
#include <string>
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"
#include "Day8.h"
#include "Day9.h"
#include "Day10.h"
#include "Day11.h"

int main(int argc, char ** argv) {
    static const std::string usage = "usage: aoc2022 [DAY] [PART] [FILENAME]";

    if (argc < 4) {
        std::cerr << usage << std::endl;
        return 1;
    }
    int day = std::stoi(argv[1]);
    int part = std::stoi(argv[2]);
    std::string filename(argv[3]);
    if (day < 1 || day > 25) {
        std::cerr << "day out of range (1-25)" << std::endl;
        return 1;
    }
    if (part != 1 && part != 2) {
        std::cerr << "part out of range (1-2)" << std::endl;
        return 1;
    }
    switch (day) {
    default:
    case 1:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day1Part1(filename)();
        case 2:
            return aoc2022::Day1Part2(filename)();
        }
    case 2:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day2Part1(filename)();
        case 2:
            return aoc2022::Day2Part2(filename)();
        }
    case 3:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day3Part1(filename)();
        case 2:
            return aoc2022::Day3Part2(filename)();
        }
    case 4:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day4Part1(filename)();
        case 2:
            return aoc2022::Day4Part2(filename)();
        }
    case 5:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day5Part1(filename)();
        case 2:
            return aoc2022::Day5Part2(filename)();
        }
    case 6:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day6Part1(filename)();
        case 2:
            return aoc2022::Day6Part2(filename)();
        }
    case 7:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day7Part1(filename)();
        case 2:
            return aoc2022::Day7Part2(filename)();
        }
    case 8:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day8Part1(filename)();
        case 2:
            return aoc2022::Day8Part2(filename)();
        }
    case 9:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day9Part1(filename)();
        case 2:
            return aoc2022::Day9Part2(filename)();
        }
    case 10:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day10Part1(filename)();
        case 2:
            return aoc2022::Day10Part2(filename)();
        }
    case 11:
        switch (part) {
        default:
        case 1:
            return aoc2022::Day11Part1(filename)();
        case 2:
            return aoc2022::Day11Part2(filename)();
        }
    }
}
