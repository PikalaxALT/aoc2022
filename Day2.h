//
// Created by scott on 10-Dec-22.
//

#ifndef AOC2022_DAY2_H
#define AOC2022_DAY2_H

#include <iostream>
#include "Solution.h"

namespace aoc2022 {

    class Day2 : public Solution {
    public:
        template <class S> explicit Day2(const S& fname) : Solution(fname) {}
        virtual int calc_score(int oppMove, int myMove) = 0;
        int operator()() override {
            int oppMove, myMove, score = 0;
            while (readline()) {
                oppMove = line[0] - 'A'; // A = rock, B = paper, C = scissors
                myMove = line[2] - 'X'; // X = rock, Y = paper, C = scissors
                score += calc_score(oppMove, myMove);
            }
            std::cout << score << std::endl;
            return 0;
        }
    };

    class Day2Part1 : public Day2 {
    public:
        template <class S> explicit Day2Part1(const S& fname) : Day2(fname) {}
    private:
        int calc_score(int oppMove, int myMove) override {
            int diff = oppMove - myMove;
            if (diff < 0) {
                diff += 3;
            }
            if (diff == 0) {
                diff = 1;
            } else if (diff == 1) {
                diff = 0;
            }
            return (myMove + 1) + 3 * diff;
        }
    };

    class Day2Part2 : public Day2 {
    public:
        template <class S> explicit Day2Part2(const S& fname) : Day2(fname) {}
    private:
        int calc_score(int oppMove, int theResult) override {
            int myMove = (oppMove + theResult - 1) % 3;
            if (myMove < 0) {
                myMove += 3;
            }
            return (myMove + 1) + 3 * theResult;
        }
    };

} // aoc2022

#endif //AOC2022_DAY2_H
