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
        long long mindist;
        Sensor() = default;
        Sensor(Coord2<long long> const& pos, Coord2<long long> const& beacon) : pos(pos), beacon(beacon) {
            mindist = pos.l1dist(beacon);
        }
        Sensor(const long long& sx, const long long& sy, const long long& bx, const long long& by) : Sensor({sx, sy}, {bx, by}) {}
    };

    class Day15 : public Solution {
    protected:
        std::vector<Sensor> sensors;
        long long x0 = INT64_MAX, x1 = INT64_MIN, y0 = INT64_MAX, y1 = INT64_MIN;
        void read_sensors() {
            while (readline()) {
                std::size_t pos1 = line.find('=');
                std::size_t pos2 = line.find(',', pos1 + 1);
                long long sx = std::stoll(line.substr(pos1 + 1, pos2 - pos1 - 1));
                pos1 = line.find('=', pos2 + 1);
                pos2 = line.find(':', pos1 + 1);
                long long sy = std::stoll(line.substr(pos1 + 1, pos2 - pos1 - 1));
                pos1 = line.find('=', pos2 + 1);
                pos2 = line.find(',', pos1 + 1);
                long long bx = std::stoll(line.substr(pos1 + 1, pos2 - pos1 - 1));
                pos1 = line.find('=', pos2 + 1);
                long long by = std::stoll(line.substr(pos1 + 1));
                Sensor const& sensor = sensors.emplace_back(sx, sy, bx, by);
                x0 = std::min(sx - sensor.mindist, x0);
                x1 = std::max(sx + sensor.mindist, x1);
            }
        }
        [[nodiscard]] bool maybeBeacon(const Coord2<long long>& testpos, bool allowDetected = true) const {
            for (const Sensor& sensor : sensors) {
                if (allowDetected && testpos == sensor.beacon) {
                    return true;
                }
                long long dist = sensor.pos.l1dist(testpos);
                if (dist <= sensor.mindist) {
                    return false;
                }
            }
            return true;
        }
    public:
        template <class S> explicit Day15(const S& fname) : Solution(fname) {}
    };

    class Day15Part1 : public Day15 {
    public:
        template <class S> explicit Day15Part1(const S& fname) : Day15(fname) {}

        int operator()() override {
            read_sensors();
            int excludedPos = 0;
            Coord2<long long> testpos {x0, 2000000};
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

            for (long long dist = 1;; ++dist) {
                for (const Sensor& sensor : sensors) {
                    testpos = {sensor.pos.x - sensor.mindist - dist, sensor.pos.y};
                    while (testpos.x != sensor.pos.x) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (maybeBeacon(testpos, false)) {
                                return testpos;
                            }
                        }
                        ++testpos.x;
                        ++testpos.y;
                    }
                    while (testpos.y != sensor.pos.y) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (maybeBeacon(testpos, false)) {
                                return testpos;
                            }
                        }
                        ++testpos.x;
                        --testpos.y;
                    }
                    while (testpos.x != sensor.pos.x) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (maybeBeacon(testpos, false)) {
                                return testpos;
                            }
                        }
                        --testpos.x;
                        --testpos.y;
                    }
                    while (testpos.y != sensor.pos.y) {
                        if (testpos.x >= 0 && testpos.x <= 4000000 && testpos.y >= 0 && testpos.y <= 4000000) {
                            if (maybeBeacon(testpos, false)) {
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
