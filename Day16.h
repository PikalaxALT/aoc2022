//
// Created by scott on 16-Dec-22.
//

#ifndef AOC2022_DAY16_H
#define AOC2022_DAY16_H

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include "Solution.h"

namespace aoc2022 {

    struct Valve {
        std::string name;
        int flow = 0;
        bool open = false;
        std::unordered_map<std::string, int> tunnels;

        bool operator==(const Valve &rhs) const {
            return name == rhs.name;
        }
    };
    
    struct Actor {
        std::string target = "AA";
        int distance = 0;
        bool operator<(const Actor& rhs) const {
            return distance < rhs.distance;
        }
    };
}

template<> struct std::hash<aoc2022::Valve> {
    unsigned long long operator()(const aoc2022::Valve &valve) const {
        return std::hash<std::string>{}(valve.name);
    }
};

template<> struct std::hash<std::pair<std::string, std::string>> {
    std::hash<std::string> str_hasher{};
    unsigned long long operator()(const std::pair<std::string, std::string>& pair) const {
        return (str_hasher(pair.first) << 1) | str_hasher(pair.second);
    }
};

namespace aoc2022 {

    template<int n_actors>
    class Day16 : public Solution {
    protected:
        std::unordered_map<std::string, Valve> valves;
        std::unordered_set<std::string> closed;
        
        // return type is vector because i cba to code a lazy iterator
        std::vector<std::vector<std::string>> iter_targets(int n, bool reciprocal = true) {
            // n can only be 0, 1, or 2
            std::vector<std::vector<std::string>> ret {};
            if (closed.size() >= n) {
                switch (n) {
                case 1:
                    for (const std::string &s: closed) {
                        ret.push_back({s});
                    }
                    break;
                case 2:
                    // All pairwise
                    for (auto it = closed.cbegin(); std::next(it) != closed.cend(); ++it) {
                        for (auto it2 = std::next(it); it2 != closed.cend(); ++it2) {
                            ret.push_back({*it, *it2});
                            if (reciprocal) {
                                ret.push_back({*it2, *it});
                            }
                        }
                    }
                default:
                    break;
                }
            }
            return ret;
        }
        
        int find_path(std::array<Actor, n_actors>& actors, std::array<std::string, n_actors>& path, int time, int pressure = 0, int flow = 0) {
            std::vector<int> movable; // list of movable actors
            std::array<Actor, n_actors> bak = actors; // To restore at the end
            std::array<std::string, n_actors> best_path = path;
            
            // Which actor will reach the next valve first?
            int dt = std::min_element(actors.begin(), actors.end())->distance + 1;
            if (dt > time) { // not enough time to get there
                return pressure + time * flow;
            }
            time -= dt;
            pressure += dt * flow;
            int nmoving = 0;
            for (int i = 0; i < n_actors; ++i) {
                actors[i].distance -= dt;
                if (actors[i].distance < 0) {
                    valves[actors[i].target].open = true;
                    flow += valves[actors[i].target].flow;
                    movable.push_back(i);
                    actors[i].distance = INT_MAX;
                } else {
                    ++nmoving;
                }
            }
            int best = pressure + flow * time; // Result from taking no action this turn
            if (nmoving != 0) {
                best = find_path(actors, best_path, time, pressure, flow);
            }
            for (std::vector<std::string> const &options: iter_targets(movable.size(), n_actors == 1 ||
                                                                                       bak[0].target !=
                                                                                       bak[1].target)) {
                std::array<std::string, n_actors> cur_path = path;
                for (int i = 0; i < movable.size(); ++i) {
                    actors[movable[i]].target = options[i];
                    actors[movable[i]].distance = valves[bak[movable[i]].target].tunnels[options[i]];
                    cur_path[movable[i]] += options[i];
                    closed.erase(options[i]);
                }
                int curr = find_path(actors, cur_path, time, pressure, flow);
                if (curr > best) {
                    best = curr;
                    best_path = cur_path;
                }
                closed.insert(options.cbegin(), options.cend()); // reset for next call
            }
            // Reset for next iteration
            actors = bak;
            for (Actor& actor : actors) {
                valves[actor.target].open = false;
            }
            
            // Return best path and pressure relieved
            path = best_path;
            return best;
        }
        
        void readValveLayout() {
            while (readline()) {
                std::string name = line.substr(6, 2);
                closed.insert(name);
                Valve& valve = valves[name];
                valve.name = name;
                std::size_t pos1 = line.find(';', 23);
                valve.flow = std::stoi(line.substr(23, pos1 - 23));
                pos1 = line.find("lead to valves ");
                if (pos1 == std::string::npos) {
                    pos1 = line.find("leads to valve ");
                }
                pos1 += 15;
                do {
                    valve.tunnels[line.substr(pos1, 2)] = 1;
                    pos1 += 4;
                } while (pos1 < line.length());
            }
            
            std::vector<std::string> to_remove;
            for (std::pair<const std::string, Valve>& valve : valves) {
                if (valve.second.flow <= 0) {
                    to_remove.push_back(valve.first);
                }
                for (auto it = valve.second.tunnels.begin(); std::next(it) != valve.second.tunnels.end(); ++it) {
                    for (auto it2 = std::next(it); it2 != valve.second.tunnels.end(); ++it2) {
                        if (valves[it->first].tunnels.find(it2->first) == valves[it->first].tunnels.end()) {
                            valves[it->first].tunnels[it2->first] = valves[it2->first].tunnels[it->first] =
                                it->second + it2->second;
                        } else {
                            valves[it->first].tunnels[it2->first] = valves[it2->first].tunnels[it->first] =
                                std::min(valves[it->first].tunnels[it2->first], it->second + it2->second);
                        }
                    }
                }
            }
            for (const std::string& tr : to_remove) {
                for (std::pair<const std::string, Valve>& valve : valves) {
                    valve.second.tunnels.erase(tr);
                }
                closed.erase(tr);
            }
        }
        
    public:
        template <class S> explicit Day16(const S& fname) : Solution(fname) {}
        int operator()() override {
            readValveLayout();
            std::array<Actor, n_actors> actors;
            std::array<std::string, n_actors> path;
            // Give an extra minute to burn at the beginning
            std::cout << find_path(actors, path, 35 - 4 * n_actors) << std::endl;
            return 0;
        }
    };
    
    
    using Day16Part1 = Day16<1>;
    using Day16Part2 = Day16<2>;

} // aoc2022

#endif //AOC2022_DAY16_H
