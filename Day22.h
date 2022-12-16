//
// Created by scott on 22-Dec-22.
//

#ifndef AOC2022_DAY22_H
#define AOC2022_DAY22_H

#include "Solution.h"

namespace aoc2022 {

    class Day22 : public Solution {
    public:
        template <class S> explicit Day22(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day22Part1 = Day22;
    using Day22Part2 = Day22;

} // aoc2022

#endif //AOC2022_DAY22_H
