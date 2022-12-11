//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY6_H
#define AOC2022_DAY6_H

#include <set>
#include "Solution.h"

namespace aoc2022 {

    template <int markerLen>
    class Day6 : public Solution {
    public:
        template <class S> explicit Day6(const S& fname) : Solution(fname) {}
        int operator()() override {
            readline();
            for (int i = markerLen; i <= line.length(); ++i) {
                std::set<char> s (line.begin() + i - markerLen, line.begin() + i);
                if (s.size() == markerLen) {
                    std::cout << i << std::endl;
                    break;
                }
            }
            return 0;
        }
    };

    using Day6Part1 = Day6<4>;
    using Day6Part2 = Day6<14>;

} // aoc2022

#endif //AOC2022_DAY6_H
