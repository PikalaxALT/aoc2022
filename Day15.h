//
// Created by scott on 15-Dec-22.
//

#ifndef AOC2022_DAY15_H
#define AOC2022_DAY15_H

#include <numeric>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include "Solution.h"
#include "Coord2.h"

namespace aoc2022 {
    
    struct Sensor {
        Coord2<long long> pos;
        Coord2<long long> beacon;
        int mindist;
        Sensor() = default;
        Sensor(Coord2<long long> const& pos, Coord2<long long> const& beacon) : pos(pos), beacon(beacon) {
            mindist = pos.l1dist(beacon);
        }
        Sensor(const int& sx, const int& sy, const int& bx, const int& by) : Sensor({sx, sy}, {bx, by}) {}
    };

    class Day15 : public Solution {
        std::mt19937 rng;
    protected:
        std::vector<Sensor> sensors;
        int x0 = INT_MAX, x1 = INT_MIN, y0 = INT_MAX, y1 = INT_MIN;
        template <typename T> const T& choose(std::vector<T> const& v) {
            return v[std::uniform_int_distribution<std::size_t>{0, v.size() - 1}(rng)];
        }
        Coord2<long long> randomPos(const int& xm, const int& xM, const int& ym, const int& yM) {
            std::uniform_int_distribution xroll{xm, xM}, yroll{ym, yM};
            return {
                xroll(rng),
                yroll(rng)
            };
        }
        void read_sensors() {
            while (readline()) {
                std::size_t pos1 = line.find('=');
                std::size_t pos2 = line.find(',', pos1 + 1);
                int sx = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                pos1 = line.find('=', pos2 + 1);
                pos2 = line.find(':', pos1 + 1);
                int sy = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                pos1 = line.find('=', pos2 + 1);
                pos2 = line.find(',', pos1 + 1);
                int bx = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                pos1 = line.find('=', pos2 + 1);
                int by = std::stoi(line.substr(pos1 + 1));
                sensors.emplace_back(sx, sy, bx, by);
            }
        }
        int findNearestSensor(const Coord2<long long>& testpos, Sensor& dest) const {
            int m = INT_MAX;
            for (const Sensor& sensor : sensors) {
                int dist = sensor.pos.l1dist(testpos);
                if (dist <= sensor.mindist && dist < m) {
                    m = dist;
                    dest = sensor;
                } 
            }
            return m;
        }
        [[nodiscard]] bool maybeBeacon(const Coord2<long long>& testpos, bool allowDetected = true) const {
            Sensor sensor {};
            int dist = findNearestSensor(testpos, sensor);
            return dist != INT_MAX || (allowDetected && testpos == sensor.beacon);
        }
    public:
        template <class S> explicit Day15(const S& fname) : Solution(fname), rng(std::random_device{}()) {}
    };

    class Day15Part1 : public Day15 {
    public:
        template <class S> explicit Day15Part1(const S& fname) : Day15(fname) {}

        int operator()() override {
            read_sensors();
            constexpr int ytest = 2000000;
            int excludedPos = 0;
            Coord2<long long> testpos {x0, ytest};
            for (long long& x = testpos.x; x != x1; ++x) {
                if (!maybeBeacon(testpos)) {
                    ++excludedPos;
                }
            }
            std::cout << excludedPos << std::endl;
            return 0;
        }
    };

    class Day15Part2 : public Day15 {
        [[nodiscard]] Coord2<long long> findUncoveredPos() const {
            // For each sensor, walk the perimeter of its range until an uncovered point is found.
            Coord2<long long> testpos {};

            for (int dist = 1;; ++dist) {
                for (const Sensor& sensor : sensors) {
                    Sensor buf {};
                    testpos = {sensor.pos.x - sensor.mindist - dist, sensor.pos.y};
                    while (testpos.x != sensor.pos.x) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (findNearestSensor(testpos, buf) == INT_MAX) {
                                return testpos;
                            }
                        }
                        ++testpos.x;
                        ++testpos.y;
                    }
                    while (testpos.y != sensor.pos.y) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (findNearestSensor(testpos, buf) == INT_MAX) {
                                return testpos;
                            }
                        }
                        ++testpos.x;
                        --testpos.y;
                    }
                    while (testpos.x != sensor.pos.x) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (findNearestSensor(testpos, buf) == INT_MAX) {
                                return testpos;
                            }
                        }
                        --testpos.x;
                        --testpos.y;
                    }
                    while (testpos.y != sensor.pos.y) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (findNearestSensor(testpos, buf) == INT_MAX) {
                                return testpos;
                            }
                        }
                        --testpos.x;
                        ++testpos.y;
                    }
                }
            }
        }
    public:
        template <class S> explicit Day15Part2(const S& fname) : Day15(fname) {}

        int operator()() override {
            read_sensors();
            Coord2<long long> testpos = findUncoveredPos();
            std::cout << testpos.x * 4000000 + testpos.y << std::endl;
            return 0;
        }
    };

} // aoc2022

#endif //AOC2022_DAY15_H
