//
// Created by scott on 12-Dec-22.
//

#ifndef AOC2022_DAY12_H
#define AOC2022_DAY12_H

#include <vector>
#include <unordered_map>
#include <climits>
#include "Solution.h"

namespace aoc2022 {
    
    struct MapPoint {
        int m_height;
        int m_dist;
    };
    
    class Day12 : public Solution {
    public:
        using perm_f = unsigned char;
        static const perm_f up = 1;
        static const perm_f down = 2;
        static const perm_f left = 4;
        static const perm_f right = 8;

    protected:
        std::vector<std::vector<MapPoint>> mountain;
        CoordI2 S = {-1, -1}, E = {-1, -1};
        static const std::map<char, CoordI2> directions;
        std::size_t width, height;

        void read_mountain() {
            while (readline()) {
                if (S.x == -1 && (S.x = static_cast<int>(line.find('S'))) != -1) {
                    S.y = static_cast<int>(mountain.size());
                }
                if (E.x == -1 && (E.x = static_cast<int>(line.find('E'))) != -1) {
                    E.y = static_cast<int>(mountain.size());
                }
                std::vector<MapPoint>& row = mountain.emplace_back(line.length());
                for (std::size_t i = 0; i < line.length(); ++i) {
                    row[i].m_height = line[i] == 'S' ? 0 : line[i] == 'E' ? 26 : line[i] - 'a';
                }
            }
            width = mountain[0].size();
            height = mountain.size();
        }

        int calc_path(const CoordI2& start) {
            std::vector<CoordI2> seen = {start}, now = {};
            int dist;
            bool found = false;
            for (dist = 1;; ++dist) {
                for (const CoordI2& pt : seen) {
                    MapPoint& here = mountain[pt.y][pt.x];
                    for (const std::pair<const char, CoordI2>& pair : directions) {
                        CoordI2 tgt = pt + pair.second;
                        if (tgt.x < 0 || tgt.x >= width || tgt.y < 0 || tgt.y >= height) {
                            continue;
                        }
                        MapPoint& there = mountain[tgt.y][tgt.x];
//                        std::cerr << dist << ": " << pt << "(" << here.m_height << ") " << pair.first << " " << tgt << "(" << there.m_height << ")" << std::endl;
                        if (tgt != start && there.m_dist == 0 && there.m_height - here.m_height <= 1) {
                            if (there.m_height == 26) {
                                found = true;
                                break;
                            }
                            there.m_dist = dist;
                            now.push_back(tgt);
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (found) {
                    break;
                }
                if (now.empty()) {
                    dist = INT_MAX;
                    break;
                }
                seen = now;
                now.clear();
            }
            return dist;
        }
        
        void reset() {
            for (std::vector<MapPoint>& row : mountain) {
                for (MapPoint& pt : row) {
                    pt.m_dist = 0;
                }
            }
        }

    public:
        template <class S> explicit Day12(const S& fname) : Solution(fname) {}
    };

    class Day12Part1 : public Day12 {
    public:
        template <class S> explicit Day12Part1(const S& fname) : Day12(fname) {}
        int operator()() override {
            read_mountain();
            std::cout << calc_path(S) << std::endl;
            return 0;
        }
    };

    class Day12Part2 : public Day12 {
    public:
        template <class S> explicit Day12Part2(const S& fname) : Day12(fname) {}
        int operator()() override {
            read_mountain();
            int best = INT_MAX;
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (mountain[i][j].m_height == 0) {
                        int curr = calc_path({j, i});
                        reset();
                        if (curr < best) {
                            best = curr;
                        }
                    }
                }
            }
            std::cout << best << std::endl;
            return 0;
        }
    };

    const std::map<char, CoordI2> Day12::directions {
        {'^', {0, -1}},
        {'>', {1, 0}},
        {'v', {0, 1}},
        {'<', {-1, 0}},
    };

} // aoc2022

#endif //AOC2022_DAY12_H
