//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY10_H
#define AOC2022_DAY10_H

#include <iostream>
#include "Solution.h"

namespace aoc2022 {

    class Day10 : public Solution {
    protected:
        int x = 1, c = 1;
        virtual void update_pixel(int& dx, int& cc) = 0;
        virtual void output_result() = 0;
    public:
        template <class S> explicit Day10(const S& fname) : Solution(fname) {}
        int operator()() override {
            while (readline()) {
                std::string cmd = line.substr(0, 4);
                int cc = 0, dx = 0;
                if (cmd == "noop") {
                    cc = 1;
                } else if (cmd == "addx") {
                    dx = std::stoi(line.substr(5));
                    cc = 2;
                }
                update_pixel(dx, cc);
                c += cc;
                x += dx;
            }
            output_result();
            return 0;
        }
    };

    class Day10Part1 : public Day10 {
        int s = 0;
    public:
        template <class S> explicit Day10Part1(const S& fname) : Day10(fname) {}
    protected:
        void update_pixel(int& dx, int& cc) override {
            int f = c % 40;
            if (f > 20 - cc && f <= 20) {
                s += x * (20 + (c / 40) * 40);
            }
        }
        void output_result() override {
            std::cout << s << std::endl;
        }
    };

    class Day10Part2 : public Day10 {
        int sx = 1, sy = 1;
    public:
        template <class S> explicit Day10Part2(const S& fname) : Day10(fname) {}
    protected:
        void update_pixel(int& dx, int& cc) override {
            for (int i = 0; i < cc; ++i) {
                if (x <= sx && sx < x + 3) {
                    std::cout << '#';
                } else {
                    std::cout << '.';
                }
                ++sx;
                if (sx > 40) {
                    sx = 1;
                    ++sy;
                    std::cout << std::endl;
                }
            }
        }
        void output_result() override {}
    };

} // aoc2022

#endif //AOC2022_DAY10_H
