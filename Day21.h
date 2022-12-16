//
// Created by scott on 21-Dec-22.
//

#ifndef AOC2022_DAY21_H
#define AOC2022_DAY21_H

#include "Solution.h"

namespace aoc2022 {

    class Day21 : public Solution {
    public:
        template <class S> explicit Day21(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day21Part1 = Day21;
    using Day21Part2 = Day21;

} // aoc2022

#endif //AOC2022_DAY21_H
