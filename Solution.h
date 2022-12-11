//
// Created by scott on 10-Dec-22.
//

#ifndef AOC2022_SOLUTION_H
#define AOC2022_SOLUTION_H

#include <fstream>
#include <string>

class io_failure : public std::runtime_error {
public:
    explicit io_failure(const std::string& what_arg) : std::runtime_error(what_arg) {}
    explicit io_failure(const char* what_arg) : std::runtime_error(what_arg) {}
};

namespace aoc2022 {

    class Solution {
        std::ifstream infile;
    protected:
        std::string line;
        std::istream& readline() {
            return std::getline(infile, line);
        }
    public:
        template <class S> explicit Solution(const S& filename) : infile(filename) {
            if (!infile.good()) {
                throw io_failure("Solution::Solution");
            }
        }
        virtual int operator()() = 0;
    };

} // aoc2022

#endif //AOC2022_SOLUTION_H
