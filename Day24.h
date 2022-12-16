//
// Created by scott on 24-Dec-22.
//

#ifndef AOC2022_DAY24_H
#define AOC2022_DAY24_H

#include "Solution.h"

namespace aoc2022 {

    class Day24 : public Solution {
    public:
        template <class S> explicit Day24(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day24Part1 = Day24;
    using Day24Part2 = Day24;

} // aoc2022

#endif //AOC2022_DAY24_H
