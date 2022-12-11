//
// Created by scott on 11-Dec-22.
//

#ifndef AOC2022_DAY7_H
#define AOC2022_DAY7_H

#include <map>
#include <iostream>
#include "Solution.h"

namespace aoc2022 {

    constexpr std::size_t disk_size = 70000000, needed_size = 30000000;

    struct FSNode {
        std::string name;
        bool is_dir = false;
        FSNode* parent = nullptr;
        std::size_t size = 0;
        std::map<std::string, FSNode> children = {};

        [[nodiscard]] std::size_t total_size_at_most(const std::size_t &limit) const {
            std::size_t result = 0;
            if (is_dir) {
                if (size <= limit) {
                    result += size;
                }
                for (auto &p : children) {
                    result += p.second.total_size_at_most(limit);
                }
            }
            return result;
        }

        [[nodiscard]] std::size_t smallest_child_at_least(const std::size_t &limit) const {
            std::size_t result = size;
            if (is_dir) {
                for (auto &p : children) {
                    std::size_t second = p.second.smallest_child_at_least(limit);
                    if (second >= limit && second < result) {
                        result = second;
                    }
                }
            }
            return result;
        }
    };

    enum Command {
        CMD_NASHI,
        CMD_CD,
        CMD_LS,
    };

    class Day7 : public Solution {
    protected:
        FSNode root;
        virtual std::size_t calc_size() = 0;
    public:
        template <class S> explicit Day7(const S& fname) : Solution(fname), root({"", true}) {}
        int operator()() override {
            Command last_cmd {Command::CMD_NASHI};
            FSNode* cwd = &root;
            while (readline()) {
                if (line[0] == '$') {
                    std::string cmdname = line.substr(2, 2);
                    if (cmdname == "cd") {
                        // Parse cd command
                        last_cmd = Command::CMD_CD;
                        std::string target = line.substr(5);
                        if (target[0] == '/') {
                            cwd = &root;
                        } else {
                            std::size_t last_slash;
                            while (true) {
                                last_slash = target.find('/');
                                std::string dirname = target.substr(0, last_slash);
                                if (dirname == "..") {
                                    cwd = cwd->parent;
                                } else if (dirname.empty()) {
                                    cwd = &root;
                                } else {
                                    cwd = &cwd->children.at(dirname);
                                }
                                if (last_slash == std::string::npos) {
                                    break;
                                }
                                target = target.substr(last_slash + 1);
                            }
                        }
                    } else if (cmdname == "ls") {
                        // Parse ls command
                        last_cmd = Command::CMD_LS;
                    } else {
                        // Handle unknown command
                        std::cerr << cmdname << ": no such file or directory\n";
                        std::exit(127);
                    }
                } else {
                    switch (last_cmd) {
                    case Command::CMD_NASHI:
                    case Command::CMD_CD:
                        break;
                    case Command::CMD_LS:
                        std::size_t spacepos = line.find(' ');
                        std::string size_arg = line.substr(0, spacepos);
                        std::string name_arg = line.substr(spacepos + 1);
                        if (size_arg == "dir") {
                            cwd->children[name_arg] = FSNode{name_arg, true, cwd};
                        } else {
                            std::size_t size = std::stoull(size_arg);
                            cwd->children[name_arg] = FSNode{name_arg, false, cwd, size};
                            FSNode* node = cwd;
                            while (node) {
                                node->size += size;
                                node = node->parent;
                            }
                        }
                        break;
                    }
                }
            }
            std::cout << calc_size() << std::endl;
            return 0;
        }
    };
    
    class Day7Part1 : public Day7 {
    public:
        template <class S> explicit Day7Part1(const S& fname) : Day7(fname) {}
    private:
        std::size_t calc_size() override {
            return root.total_size_at_most(100000);
        }
    };

    class Day7Part2 : public Day7 {
    public:
        template <class S> explicit Day7Part2(const S& fname) : Day7(fname) {}
    private:
        std::size_t calc_size() override {
            std::size_t to_free = root.size - disk_size + needed_size;
            return root.smallest_child_at_least(to_free);
        }
    };

} // aoc2022

#endif //AOC2022_DAY7_H
