//
// Created by scott on 17-Dec-22.
//

#ifndef AOC2022_DAY17_H
#define AOC2022_DAY17_H

#include <string>
#include <vector>
#include <array>
#include "Coord2.h"
#include "Solution.h"

namespace aoc2022 {

    template <typename T, typename S = T>
    struct Rock : public std::vector<Coord2<T>> {
        Rock operator+(const Coord2<S>& rhs) const {
            Rock ret = *this;
            for (Coord2<S>& point : ret) {
                point += rhs;
            }
            return ret;
        }
    };
    
    struct RockState {
        long long i;
        long long height;
        long long yoff;
        long long jeti;
        std::array<int, 7> roof_rel;
        friend std::ostream& operator<<(std::ostream& strm, const RockState& self) {
            strm << self.i << "\t" << self.height << "\t" << self.yoff << "\t" << self.jeti;
            for (const int& y : self.roof_rel) {
                strm << "\t" << y;
            }
            return strm;
        }
        bool operator==(const RockState& rhs) const {
            return (i % 5) == (rhs.i % 5) && 
            jeti == rhs.jeti && 
            height - yoff == rhs.height - rhs.yoff && 
            roof_rel == rhs.roof_rel;
        }
    };
    
    template <long long nrocks>
    class Day17 : public Solution {
    protected:
        std::vector<std::array<bool, 7>> grid;
        static const std::array<Rock<long long>, 5> rocks;
        bool tryMove(Rock<long long> & rock, Coord2<long long> const& direction, const long long &yoff) const {
            Rock newpos = rock + direction;
            for (Coord2<long long> const& point : newpos) {
                if (point.x < 0 || point.x >= 7 || point.y <= yoff || point.y - yoff < grid.size() && grid[point.y - yoff][point.x]) {
                    return false;
                }
            }
            rock = newpos;
            return true;
        }
    public:
        template <class S> explicit Day17(const S& fname) : Solution(fname) {}
        int operator()() override {
            readline();
            RockState state {};
            std::vector<RockState> history;
            long long &top = state.height, &jeti = state.jeti, &yoff = state.yoff;
            std::array<long long, 7> roof {};
            for (long long &i = state.i; i < nrocks; ++i) {
                Rock rock = rocks[i % 5] + Coord2<long long>{2, top + 4};
                grid.resize(rock[0].y + 1 - yoff);
                while (true) {
                    tryMove(rock, {line[jeti++] - '=', 0}, yoff);
                    if (jeti >= line.length()) {
                        jeti = 0;
                    }
                    if (!tryMove(rock, {0, -1}, yoff)) {
                        break;
                    }
                }
                for (const Coord2<long long>& point : rock) {
                    grid[point.y - yoff][point.x] = true;
                    roof[point.x] = std::max(roof[point.x], point.y);
                }
                auto minmax = std::minmax_element(roof.cbegin(), roof.cend());
                top = *minmax.second;
                long long new_yoff = *minmax.first - 1;
                if (new_yoff > yoff) {
                    std::copy(grid.begin() + (new_yoff - yoff), grid.end(), grid.begin());
                    for (auto it = grid.end() - (new_yoff - yoff); it != grid.end(); ++it) {
                        it->fill(false);
                    }
                    yoff = new_yoff;
                }
                for (int j = 0; j < 7; ++j) {
                    state.roof_rel[j] = static_cast<int>(roof[j] - yoff);
                }
                //std::cerr << state << std::endl;
                auto sit = std::find(history.cbegin(), history.cend(), state);
                if (sit != history.cend()) {
                    long long period = i - sit->i;
                    long long dy = top - sit->height;
                    long long remaining = nrocks - (i + 1);
                    top += history[sit->i + (remaining % period)].height - sit->height + dy * (remaining / period);
                    break;
                }
                history.push_back(state);
            }
            std::cout << top << std::endl;
            return 0;
        }
    };
    
    using Day17Part1 = Day17<2022>;
    using Day17Part2 = Day17<1000000000000>;
    
    template <long long nrocks>
    const std::array<Rock<long long>, 5> Day17<nrocks>::rocks  {{
        {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
        {{{1, 2}, {0, 1}, {1, 1}, {2, 1}, {1, 0}}},
        {{{2, 2}, {2, 1}, {0, 0}, {1, 0}, {2, 0}}},
        {{{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
        {{{0, 1}, {1, 1}, {0, 0}, {1, 0}}}
    }};

} // aoc2022

#endif //AOC2022_DAY17_H
