//
// Created by scott on 17-Dec-22.
//

#ifndef AOC2022_DAY17_H
#define AOC2022_DAY17_H

#include "Solution.h"

namespace aoc2022 {

    class Day17 : public Solution {
    public:
        template <class S> explicit Day17(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day17Part1 = Day17;
    using Day17Part2 = Day17;

} // aoc2022

#endif //AOC2022_DAY17_H
