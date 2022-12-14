//
// Created by scott on 14-Dec-22.
//

#ifndef AOC2022_DAY14_H
#define AOC2022_DAY14_H

#include "Solution.h"
#include "Coord2.h"

namespace aoc2022 {

    template <bool solidFloor>
    class Day14 : public Solution {
    protected:
        std::unordered_set<CoordI2> seen;
        int floor = 0;
        static CoordI2 parse_path(std::string const& spec) {
            std::size_t pos = spec.find(',');
            return {
                std::stoi(spec.substr(0, pos)),
                std::stoi(spec.substr(pos + 1))
            };
        }
    public:
        template <class S> explicit Day14(const S& fname) : Solution(fname) {}
        int operator()() override {
            while (readline()) {
                std::size_t pos = line.find(" -> ");
                CoordI2 start = parse_path(line.substr(0, pos));
                seen.insert(start);
                floor = std::max(floor, start.y);
                while (pos != std::string::npos) {
                    pos += 4;
                    std::size_t nextpos = line.find(" -> ", pos);
                    CoordI2 curr = parse_path(line.substr(pos, nextpos == std::string::npos ? nextpos : nextpos - pos));
                    CoordI2 diff = curr - start;
                    if (diff.x == 0) {
                        diff.y /= std::abs(diff.y);
                    } else {
                        diff.x /= std::abs(diff.x);
                    }
                    for (CoordI2 pt = start; pt != curr;) {
                        pt += diff;
                        seen.insert(pt);
                    }
                    floor = std::max(floor, curr.y);
                    start = curr;
                    pos = nextpos;
                }
            }
            floor += 2;
            constexpr CoordI2 source = {500, 0}, down = {0, 1}, downleft = {-1, 1}, downright = {1, 1};
            CoordI2 sand;
            int grains = 0;
            do {
                ++grains;
                sand = source;
                while (sand.y != floor) {
                    if (solidFloor && sand.y + 1 == floor) {
                        seen.insert(sand);
                        break;
                    }
                    if (seen.find(sand + down) == seen.end()) {
                        sand += down;
                    } else if (seen.find(sand + downleft) == seen.end()) {
                        sand += downleft;
                    } else if (seen.find(sand + downright) == seen.end()) {
                        sand += downright;
                    } else {
                        seen.insert(sand);
                        break;
                    }
                }
            } while (solidFloor ? seen.find(source) == seen.end() : sand.y != floor);
            std::cout << grains - !solidFloor << std::endl;
            return 0;
        }
    };
    
    using Day14Part1 = Day14<false>;
    using Day14Part2 = Day14<true>;

} // aoc2022

#endif //AOC2022_DAY14_H
