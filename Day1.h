//
// Created by scott on 10-Dec-22.
//

#ifndef AOC2022_DAY1_H
#define AOC2022_DAY1_H

#include <vector>
#include <algorithm>
#include <numeric>
#include "Solution.h"

namespace aoc2022 {

    template<int topn>
    class Day1 : public Solution {
        std::vector<int> calcounts = {0};
    public:
        template <class S> explicit Day1(const S& filename) : Solution(filename) {}
        int operator()() override {
            while (readline()) {
                if (line.empty()) {
                    calcounts.push_back(0);
                } else {
                    calcounts.back() += std::stoi(line);
                }
            }
            std::sort(calcounts.begin(), calcounts.end(), std::greater<int>{});
            std::cout << std::accumulate(calcounts.begin(), calcounts.begin() + topn, 0) << std::endl;
            return 0;
        }
    };

    using Day1Part1 = Day1<1>;
    using Day1Part2 = Day1<3>;

} // aoc2022

#endif //AOC2022_DAY1_H
