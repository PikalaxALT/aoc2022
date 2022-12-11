//
// Created by scott on 10-Dec-22.
//

#ifndef AOC2022_DAY3_H
#define AOC2022_DAY3_H

#include <array>
#include <iterator>
#include "Solution.h"

namespace aoc2022 {

    template <std::size_t n>
    class Day3 : public Solution {
    protected:
        std::array<std::string, n> lines;
    public:
        template <class S> explicit Day3(const S& filename) : Solution(filename) {}
        virtual bool getlines() = 0;
        int operator()() override {
            int priosum = 0;
            while (getlines()) {
                for (std::string& s : lines) {
                    std::sort(s.begin(), s.end());
                }
                std::string isec = lines[0], isec2;
                for (std::size_t i = 1; i < n; ++i) {
                    std::set_intersection(isec.begin(), isec.end(), lines[i].begin(), lines[i].end(), std::back_inserter(isec2));
                    isec = isec2;
                }
                const char &c = isec.front();
                if (c >= 'a' && c <= 'z') {
                    priosum += c - 'a' + 1;
                } else {
                    priosum += c - 'A' + 27;
                }
            }
            std::cout << priosum << std::endl;
            return 0;
        }
    };

    class Day3Part1 : public Day3<2> {
    public:
        template <class S> explicit Day3Part1(const S& filename) : Day3(filename) {}
    private:
        bool getlines() override {
            if (!readline()) return false;
            std::size_t h = line.length() / 2;
            lines[0] = line.substr(0, h);
            lines[1] = line.substr(h);
            return true;
        }
    };

    class Day3Part2 : public Day3<3> {
    public:
        template <class S> explicit Day3Part2(const S& filename) : Day3(filename) {}
        private:
        bool getlines() override {
            if (!readline()) return false;
            lines[0] = line;
            readline();
            lines[1] = line;
            readline();
            lines[2] = line;
            return true;
        }
    };

} // aoc2022

#endif //AOC2022_DAY3_H
