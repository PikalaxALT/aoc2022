//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY11_H
#define AOC2022_DAY11_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Solution.h"

namespace aoc2022 {

    struct Monkey {
        std::vector<unsigned long long> items;
        bool is_mult; // false -> add
        bool is_self; // false -> one operand
        unsigned long long operand;
        unsigned long long divisor;
        int iftrue;
        int iffalse;
        unsigned long long activity;
        bool operator>(const Monkey& rhs) const {
            return activity > rhs.activity;
        }
    };

    template <int nrounds, int worrymod>
    class Day11 : public Solution {
        int globalDivisor = 1;
    public:
        template <class S> explicit Day11(const S& fname) : Solution(fname) {}
        int operator()() override {

            std::vector<Monkey> monkeys;
            while (readline()) {
                // assume monkeys are indexed in order
                Monkey& monkey = monkeys.emplace_back();
                readline();
                std::size_t pos = line.find_first_of("0123456789");
                while (pos != std::string::npos) {
                    std::size_t nextpos = line.find(',', pos);

                    if (nextpos == std::string::npos) {
                        monkey.items.push_back(std::stoull(line.substr(pos)));
                        break;
                    }
                    monkey.items.push_back(std::stoull(line.substr(pos, nextpos - pos)));
                    pos = line.find_first_of("0123456789", nextpos);
                }
                readline();
                monkey.is_mult = line[line.find_first_of("+*")] == '*';
                std::size_t oppos = line.find_first_of("0123456789");
                if (oppos == std::string::npos) {
                    monkey.is_self = true;
                } else {
                    monkey.operand = std::stoull(line.substr(oppos));
                }
                readline();
                globalDivisor *= monkey.divisor = std::stoull(line.substr(line.find_first_of("0123456789")));
                readline();
                monkey.iftrue = std::stoi(line.substr(line.find_first_of("0123456789")));
                readline();
                monkey.iffalse = std::stoi(line.substr(line.find_first_of("0123456789")));
                readline(); // consume blank line
            }
            for (int i = 0; i < nrounds; ++i) {
                int midx = 0;
                for (Monkey& monkey : monkeys) {
                    monkey.activity += monkey.items.size();
                    for (unsigned long long item : monkey.items) {
                        unsigned long long old = item;
                        unsigned long long operand = monkey.is_self ? item : monkey.operand;
                        if (monkey.is_mult) {
                            item *= operand;
                        } else {
                            item += operand;
                        }
                        if (worrymod > 1) {
                            item /= worrymod;
                        }
                        int& monkeyidx = (item % monkey.divisor == 0) ? monkey.iftrue : monkey.iffalse;
                        monkeys[monkeyidx].items.push_back(item % globalDivisor);
                    }
                    monkey.items.clear();
                    ++midx;
                }
            }
            std::sort(monkeys.begin(), monkeys.end(), std::greater<Monkey>{});
            std::cout << monkeys[0].activity * monkeys[1].activity << std::endl;
            return 0;
        }
    };

    using Day11Part1 = Day11<20, 3>;
    using Day11Part2 = Day11<10000, 1>;

} // aoc2022

#endif //AOC2022_DAY11_H
