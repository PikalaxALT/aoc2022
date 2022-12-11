//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY4_H
#define AOC2022_DAY4_H

#include "Solution.h"

namespace aoc2022 {

    class Day4 : public Solution {
    protected:
        virtual bool overlap(int a1, int a2, int b1, int b2) = 0;
    public:
        template <class S> explicit Day4(const S& fname) : Solution(fname) {}
        int operator()() override {
            int count = 0;
            while (readline()) {
                // parse
                std::size_t hyp1, comma, hyp2;
                int a1, a2, b1, b2;
                hyp1 = line.find_first_of('-');
                comma = line.find_first_of(',', hyp1 + 1);
                hyp2 = line.find_first_of('-', comma + 1);
                a1 = std::stoi(line.substr(0, hyp1));
                a2 = std::stoi(line.substr(hyp1 + 1, comma - hyp1 - 1));
                b1 = std::stoi(line.substr(comma + 1, hyp2 - comma - 1));
                b2 = std::stoi(line.substr(hyp2 + 1));
                if (overlap(a1, a2, b1, b2)) {
                    ++count;
                }
            }
            std::cout << count << std::endl;
            return 0;
        }
    };

    class Day4Part1 : public Day4 {
    public:
        template <class S> explicit Day4Part1(const S& fname) : Day4(fname) {}
    private:
        bool overlap(int a1, int a2, int b1, int b2) override {
            return (a1 <= b1 && b2 <= a2) || (b1 <= a1 && a2 <= b2);
        }
    };

    class Day4Part2 : public Day4 {
    public:
        template <class S> explicit Day4Part2(const S& fname) : Day4(fname) {}
    private:
        bool overlap(int a1, int a2, int b1, int b2) override {
            return (a1 <= b1 && b1 <= a2) || (b1 <= a1 && a1 <= b2);
        }
    };

} // aoc2022

#endif //AOC2022_DAY4_H
