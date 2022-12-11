//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY8_H
#define AOC2022_DAY8_H

#include <iostream>
#include <vector>
#include "Solution.h"

namespace aoc2022 {

    class Day8 : public Solution {
    protected:
        std::vector<std::vector<int>> trees {};
        virtual int measure() = 0;
    public:
        template <class S> explicit Day8(const S& fname) : Solution(fname) {}
        int operator()() override {
            while (readline()) {
                std::vector<int>& row = trees.emplace_back();
                for (const char &c : line) {
                    if (c >= '0' && c <= '9'){
                        row.push_back(c - '0');
                    }
                }
            }
            std::cout << measure() << std::endl;
            return 0;
        }
    };

    class Day8Part1 : public Day8 {
    public:
        template <class S> explicit Day8Part1(const S& fname) : Day8(fname) {}
    private:
        int measure() override {
            int visible = 2 * (trees.size() + trees.front().size()) - 4;
            std::vector<std::vector<bool>> visibleB(trees.size(), std::vector<bool>(trees.front().size()));
            for (int i = 1; i < trees.size() - 1; ++i) {
                std::vector<int>& row = trees[i];
                int highestLeft = row.front(), highestRight = row.back();
                for (int j = 1, k = trees.front().size() - 2; j < trees.front().size() - 1; ++j, --k) {
                    if (row[j] > highestLeft) {
                        visibleB[i][j] = true;
                        highestLeft = row[j];
                    }
                    if (row[k] > highestRight) {
                        visibleB[i][k] = true;
                        highestRight = row[k];
                    }
                }
            }
            for (int i = 1; i < trees.front().size() - 1; ++i) {
                int highestTop = trees.front()[i], highestBottom = trees.back()[i];
                for (int j = 1, k = trees.size() - 2; j < trees.size() - 1; ++j, --k) {
                    if (trees[j][i] > highestTop) {
                        visibleB[j][i] = true;
                        highestTop = trees[j][i];
                    }
                    if (trees[k][i] > highestBottom) {
                        visibleB[k][i] = true;
                        highestBottom = trees[k][i];
                    }
                }
            }
            for (int i = 1; i < trees.size() - 1; ++i) {
                for (int j = 1; j < trees.front().size() - 1; ++j) {
                    if (visibleB[i][j]) {
                        ++visible;
                    }
                }
            }
            return visible;
        }
    };

    class Day8Part2 : public Day8 {
    public:
        template <class S> explicit Day8Part2(const S& fname) : Day8(fname) {}
    private:
        int measure() override {
            int bestSight = 0, distLeft, distUp, distRight, distDown;
            for (int i = 1; i < trees.size() - 1; ++i) {
                for (int j = 1; j < trees.front().size() - 1; ++j) {
                    const int &curTree = trees[i][j];
                    for (distLeft = 1; j > distLeft; ++distLeft) {
                        if (trees[i][j - distLeft] >= curTree) {
                            break;
                        }
                    }
                    for (distRight = 1; j + distRight < trees.front().size() - 1; ++distRight) {
                        if (trees[i][j + distRight] >= curTree) {
                            break;
                        }
                    }
                    for (distUp = 1; i > distUp; ++distUp) {
                        if (trees[i - distUp][j] >= curTree) {
                            break;
                        }
                    }
                    for (distDown = 1; i + distDown < trees.size() - 1; ++distDown) {
                        if (trees[i + distDown][j] >= curTree) {
                            break;
                        }
                    }
                    int curSight = distLeft * distRight * distUp * distDown;
                    if (curSight > bestSight) {
                        bestSight = curSight;
                    }
                }
            }
            return bestSight;
        }
    };

} // aoc2022

#endif //AOC2022_DAY8_H
