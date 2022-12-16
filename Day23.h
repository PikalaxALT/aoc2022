//
// Created by scott on 23-Dec-22.
//

#ifndef AOC2022_DAY23_H
#define AOC2022_DAY23_H

#include "Solution.h"

namespace aoc2022 {

    class Day23 : public Solution {
    public:
        template <class S> explicit Day23(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day23Part1 = Day23;
    using Day23Part2 = Day23;

} // aoc2022

#endif //AOC2022_DAY23_H
