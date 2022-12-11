//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY5_H
#define AOC2022_DAY5_H

#include "Solution.h"

namespace aoc2022 {

    template <bool reverse>
    class Day5 : public Solution {
    public:
        template <class S> explicit Day5(const S& fname) : Solution(fname) {}
        int operator()() override {
            std::vector<std::string> lines0 {};
            while (readline() && line.length() > 1) {
                lines0.push_back(line);
            }
            std::size_t nstacks = (lines0[lines0.size() - 1].length() + 1) / 4;
            std::vector<std::string> stacks (nstacks);
            for (auto l = lines0.crbegin() + 1; l != lines0.crend(); ++l) {
                const std::string &curLine = *l;
                for (int i = 0; i < nstacks; ++i) {
                    if (curLine[i * 4] == '[') {
                        stacks[i] += curLine[i * 4 + 1];
                    }
                }
            }
            while (readline()) {
                int n = 0, from = 0, to = 0, i = 5;
                while (line[i] >= '0' && line[i] <= '9') {
                    n *= 10;
                    n += line[i] - '0';
                    ++i;
                }
                while (line[i] < '0' || line[i] > '9') {
                    ++i;
                }
                while (line[i] >= '0' && line[i] <= '9') {
                    from *= 10;
                    from += line[i] - '0';
                    ++i;
                }
                while (line[i] < '0' || line[i] > '9') {
                    ++i;
                }
                while (line[i] >= '0' && line[i] <= '9') {
                    to *= 10;
                    to += line[i] - '0';
                    ++i;
                }
                if (reverse) {
                    stacks[to - 1] += std::string(stacks[from - 1].crbegin(), stacks[from - 1].crbegin() + n);
                } else {
                    stacks[to - 1] += stacks[from - 1].substr(stacks[from - 1].size() - n);
                }
                stacks[from - 1] = stacks[from - 1].substr(0, stacks[from - 1].size() - n);
            }
            for (const std::string &stack : stacks) {
                if (!stack.empty()) {
                    std::cout << stack.back();
                }
            }
            std::cout << std::endl;
            return 0;
        }
    };

    using Day5Part1 = Day5<true>;
    using Day5Part2 = Day5<false>;

} // aoc2022

#endif //AOC2022_DAY5_H
