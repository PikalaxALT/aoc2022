#ifndef AOC2022_AOC2022_H
#define AOC2022_AOC2022_H

#include <functional>
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
#include "Day12.h"
#include "Day13.h"
#include "Day14.h"
#include "Day15.h"
#include "Day16.h"
#include "Day17.h"
#include "Day18.h"
#include "Day19.h"
#include "Day20.h"
#include "Day21.h"
#include "Day22.h"
#include "Day23.h"
#include "Day24.h"
#include "Day25.h"

namespace aoc2022 {
    template<typename Day, typename S>
    int dayfun(const S &fname) {
        return Day(fname)();
    };

    template<typename S>
    int run_solution(const int &day, const int &part, const S &filename) {
        static const std::function<int(const S&)> functions[25][2]{
            {dayfun<Day1Part1, S>, dayfun<Day1Part2, S>},
            {dayfun<Day2Part1, S>, dayfun<Day2Part2, S>},
            {dayfun<Day3Part1, S>, dayfun<Day3Part2, S>},
            {dayfun<Day4Part1, S>, dayfun<Day4Part2, S>},
            {dayfun<Day5Part1, S>, dayfun<Day5Part2, S>},
            {dayfun<Day6Part1, S>, dayfun<Day6Part2, S>},
            {dayfun<Day7Part1, S>, dayfun<Day7Part2, S>},
            {dayfun<Day8Part1, S>, dayfun<Day8Part2, S>},
            {dayfun<Day9Part1, S>, dayfun<Day9Part2, S>},
            {dayfun<Day10Part1, S>, dayfun<Day10Part2, S>},
            {dayfun<Day11Part1, S>, dayfun<Day11Part2, S>},
            {dayfun<Day12Part1, S>, dayfun<Day12Part2, S>},
            {dayfun<Day13Part1, S>, dayfun<Day13Part2, S>},
            {dayfun<Day14Part1, S>, dayfun<Day14Part2, S>},
            {dayfun<Day15Part1, S>, dayfun<Day15Part2, S>},
            {dayfun<Day16Part1, S>, dayfun<Day16Part2, S>},
            {dayfun<Day17Part1, S>, dayfun<Day17Part2, S>},
            {dayfun<Day18Part1, S>, dayfun<Day18Part2, S>},
            {dayfun<Day19Part1, S>, dayfun<Day19Part2, S>},
            {dayfun<Day20Part1, S>, dayfun<Day20Part2, S>},
            {dayfun<Day21Part1, S>, dayfun<Day21Part2, S>},
            {dayfun<Day22Part1, S>, dayfun<Day22Part2, S>},
            {dayfun<Day23Part1, S>, dayfun<Day23Part2, S>},
            {dayfun<Day24Part1, S>, dayfun<Day24Part2, S>},
            {dayfun<Day25Part1, S>, dayfun<Day25Part2, S>},
        };
        if (day <= 0 || day > 25 || part <= 0 || part > 2) {
            std::cerr << "Not supported" << std::endl;
            return 1;
        }
        return functions[day - 1][part - 1](filename);
    }
}

#endif //AOC2022_AOC2022_H
