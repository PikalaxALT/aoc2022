//
// Created by scott on 10-Dec-22.
//

#ifndef AOC2022_SOLUTION_H
#define AOC2022_SOLUTION_H

#include <fstream>
#include <string>

namespace aoc2022 {

    class Solution {
        std::ifstream infile;
    protected:
        std::string line;
        std::istream& readline() {
            return std::getline(infile, line);
        }
    public:
        template <class S> explicit Solution(const S& filename) : infile(filename) {}
        virtual int operator()() = 0;
    };

} // aoc2022

#endif //AOC2022_SOLUTION_H
