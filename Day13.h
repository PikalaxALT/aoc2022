//
// Created by scott on 13-Dec-22.
//

#ifndef AOC2022_DAY13_H
#define AOC2022_DAY13_H

#include <vector>
#include "Solution.h"

namespace aoc2022 {
    
    enum PacketType {
        INT,
        LIST,
    };
    
    struct Packet {
        PacketType type;
        union {
            int number;
            std::vector<Packet>* list;
        };
        explicit Packet(const PacketType& type, const int& value) : type(type) {
            switch (type) {
            case PacketType::INT:
                number = value;
                break;
            case PacketType::LIST:
                list = new std::vector<Packet>;
                list->emplace_back(PacketType::INT, value);
                break;
            }
        }
        explicit Packet(const PacketType& type) : type(type), list(nullptr) {
            if (type == PacketType::LIST) {
                list = new std::vector<Packet>;
            }
        }
        explicit Packet(const std::string& line) {
            if (line[0] == '[') {
                type = PacketType::LIST;
                list = new std::vector<Packet>;
                for (std::size_t i = 1; i < line.length() - 1; ++i) {
                    std::size_t j;
                    if (line[i] == '[') {
                        j = i;
                        int balance = 1;
                        while (balance) {
                            switch (line[++j]) {
                            case '[':
                                ++balance;
                                break;
                            case ']':
                                --balance;
                                break;
                            }
                        }
                        list->push_back(Packet{line.substr(i, ++j - i)});
                    } else {
                        j = line.find(',', i);
                        if (j == std::string::npos) {
                            list->push_back(Packet(line.substr(i)));
                            break;
                        }
                        list->push_back(Packet{line.substr(i, j - i)});
                    }
                    i = j;
                }
            } else {
                type = PacketType::INT;
                number = std::stoi(line);
            }
        }
        
        std::strong_ordering operator<=>(const Packet& rhs) const {
            if (type == PacketType::INT && rhs.type == PacketType::INT) {
                return number <=> rhs.number;
            } else if (type == PacketType::LIST && rhs.type == PacketType::INT) {
                return *this <=> Packet(PacketType::LIST, rhs.number);
            } else if (type == PacketType::INT && rhs.type == PacketType::LIST) {
                return Packet(PacketType::LIST, number) <=> rhs;
            } else {
                const std::vector<Packet>& listl = *list, &listr = *rhs.list;
                for (std::size_t i = 0; i < listl.size(); ++i) {
                    if (i >= listr.size()) {
                        return std::strong_ordering::greater;
                    }
                    std::strong_ordering result = listl[i] <=> listr[i];
                    if (result != std::strong_ordering::equal) {
                        return result;
                    }
                }
                return listl.size() <=> listr.size();
            }
        }
        
        friend std::ostream& operator<<(std::ostream& strm, Packet const& self) {
            switch (self.type) {
            case PacketType::INT:
                strm << self.number;
                break;
            case PacketType::LIST:
                strm << "[";
                if (!self.list->empty()) {
                    for (auto it = self.list->cbegin();; strm << ",") {
                        strm << *it;
                        if (++it == self.list->cend()) {
                            break;
                        }
                    }
                }
                strm << "]";
                break;
            }
            return strm;
        }
    };

    class Day13Part1 : public Solution {
    public:
        template <class S> explicit Day13Part1(const S& fname) : Solution(fname) {}
        int operator()() override {
            int i = 1;
            int score = 0;
            while (readline()) {
                Packet lhs(line);
                readline();
                Packet rhs(line);
                readline(); // skip blank line
                if (lhs < rhs) {
                    score += i;
                }
                ++i;
            }
            std::cout << score << std::endl;
            return 0;
        }
    };

    class Day13Part2 : public Solution {
        std::vector<Packet> packets;
        Packet make_divider(int value) {
            Packet packet {PacketType::LIST};
            packet.list->emplace_back(PacketType::LIST, value);
            return packet;
        }
    public:
        template <class S> explicit Day13Part2(const S& fname) : Solution(fname) {}
        int operator()() override {
            Packet div2 = make_divider(2), div6 = make_divider(6);
            packets.emplace_back(div2);
            packets.emplace_back(div6);
            while (readline()) {
                packets.emplace_back(line);
                readline();
                packets.emplace_back(line);
                readline(); // skip blank line
            }
            std::sort(packets.begin(), packets.end());
            int result = 1, i = 1;
            for (const Packet& packet : packets) {
                if (packet <=> div2 == std::strong_ordering::equal || packet <=> div6 == std::strong_ordering::equal) {
                    result *= i;
                }
                ++i;
            }
            std::cout << result << std::endl;
            return 0;
        }
    };


} // aoc2022

#endif //AOC2022_DAY13_H
