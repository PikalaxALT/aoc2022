//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY9_H
#define AOC2022_DAY9_H

#include <map>
#include <iostream>
#include <unordered_set>
#include "Solution.h"

namespace aoc2022 {

    struct CoordI2 {
        int x, y;

        bool operator==(const CoordI2 &rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        friend CoordI2 operator+(CoordI2 lhs, const CoordI2 &rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y};
        }

        friend CoordI2 operator-(CoordI2 lhs, const CoordI2 &rhs) {
            return {lhs.x - rhs.x, lhs.y - rhs.y};
        }

        CoordI2 &operator+=(const CoordI2 &rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
    };
}

template<> struct std::hash<aoc2022::CoordI2> {
    unsigned long long operator()(const aoc2022::CoordI2& obj) const {
        std::hash<int> int_hasher {};
        unsigned long long xhash = int_hasher(obj.x), yhash = int_hasher(obj.y);
        return (xhash << 1) ^ yhash;
    }
};

namespace aoc2022 {
    template <std::size_t ropelen>
    class Day9 : public Solution {
        static const std::map<char, CoordI2> directions;
        std::array<CoordI2, ropelen> rope {};
    public:
        template <class S> explicit Day9(const S& fname) : Solution(fname) {}
        int operator()() override {

            CoordI2& head = rope.front(), &tail = rope.back();
            std::unordered_set<CoordI2> visited {tail};
            while (readline()) {
                const CoordI2& cur_move = directions.at(line[0]);
                int nsteps = std::stoi(line.substr(2));
                for (int i = 0; i < nsteps; ++i) {
                    head += cur_move;
                    for (int j = 1; j < ropelen; ++j) {
                        CoordI2 next_move = rope[j - 1] - rope[j];
                        int &dx = next_move.x, &dy = next_move.y, adx = std::abs(dx), ady = std::abs(dy);
                        if (adx >= 2 || ady >= 2) {
                            if (dx != 0) {
                                dx /= adx;
                            }
                            if (dy != 0) {
                                dy /= ady;
                            }
                        } else {
                            dx = 0;
                            dy = 0;
                        }
                        rope[j] += next_move;
                    }
                    visited.insert(tail);
                }
            }
            std::cout << visited.size() << std::endl;
            return 0;
        }
    };

    template <std::size_t ropelen>
    const std::map<char, CoordI2> Day9<ropelen>::directions  {
        {'R', {1, 0}},
        {'U', {0, -1}},
        {'L', {-1, 0}},
        {'D', {0, 1}}
    };

    using Day9Part1 = Day9<2>;
    using Day9Part2 = Day9<10>;
} // aoc2022

#endif //AOC2022_DAY9_H
