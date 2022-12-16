//
// Created by scott on 25-Dec-22.
//

#ifndef AOC2022_DAY25_H
#define AOC2022_DAY25_H

#include "Solution.h"

namespace aoc2022 {

    class Day25 : public Solution {
    public:
        template <class S> explicit Day25(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    };
    
    using Day25Part1 = Day25;
    using Day25Part2 = Day25;

} // aoc2022

#endif //AOC2022_DAY25_H
