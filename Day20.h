//
// Created by scott on 20-Dec-22.
//

#ifndef AOC2022_DAY20_H
#define AOC2022_DAY20_H

#include "Solution.h"

namespace aoc2022 {

    class Day20 : public Solution {
    public:
        template <class S> explicit Day20(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day20Part1 = Day20;
    using Day20Part2 = Day20;

} // aoc2022

#endif //AOC2022_DAY20_H
