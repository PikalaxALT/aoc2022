//
// Created by scott on 19-Dec-22.
//

#ifndef AOC2022_DAY19_H
#define AOC2022_DAY19_H

#include "Solution.h"

namespace aoc2022 {

    class Day19 : public Solution {
    public:
        template <class S> explicit Day19(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day19Part1 = Day19;
    using Day19Part2 = Day19;

} // aoc2022

#endif //AOC2022_DAY19_H
