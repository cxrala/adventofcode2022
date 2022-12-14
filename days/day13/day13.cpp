//
// Created by Amelia Ng on 13/12/2022.
// With kind help from wab.
//

#include <vector>
#include <variant>
#include <iostream>
#include <algorithm>
#include <utility>

namespace {
    class Packet {
        std::variant<int, std::vector<Packet>> contents;
    public:

        friend std::istream &operator>>(std::istream &istream, Packet &packet) {
            istream >> std::ws;
            if (istream.peek() == '[') {
                packet.contents = std::vector<Packet>{};
                istream.ignore();
                while (istream.peek() != ']') {
                    Packet child;
                    istream >> child;
                    std::get<std::vector<Packet>>(packet.contents).push_back(std::move(child));
                    if (istream.peek() == ',') {
                        istream.ignore();
                    }
                }
                istream.ignore();
            } else {
                int num;
                istream >> num;
                packet.contents = num;
            }
            return istream;
        }

        bool operator<(Packet const &other) const {
            if (std::holds_alternative<int>(contents) && std::holds_alternative<int>(other.contents)) {
                return contents < other.contents;
            }
            if (std::holds_alternative<int>(contents)) {
                return std::vector<Packet>{*this} < std::get<std::vector<Packet>>(other.contents);
            } else if (std::holds_alternative<int>(other.contents)) {
                return std::get<std::vector<Packet>>(this->contents) < std::vector<Packet>{other};
            }
            return this->contents < other.contents;
        }
    };

}

namespace aoc::day13 {
    unsigned int solution1() {
        int index = 0;
        unsigned int solution = 0;
        while (!(std::cin >> std::ws).eof()) {
            ++index;
            Packet packet1;
            Packet packet2;
            std::cin >> packet1;
            std::cin >> packet2;
            if (packet1 < packet2) {
                solution += index;
            }
        }
        return solution;
    }

    unsigned int solution2() {
        std::vector<Packet> packets{};
        while (!(std::cin >> std::ws).eof()) {
            Packet packet1;
            std::cin >> packet1;
            packets.push_back(packet1);
        }

        Packet six = packets[packets.size() - 2];
        Packet two = packets[packets.size() - 1];

        std::sort(packets.begin(), packets.end());

        unsigned int index1 = std::lower_bound(packets.begin(), packets.end(), six) - packets.begin() + 1;
        unsigned int index2 = std::lower_bound(packets.begin(), packets.end(), two) - packets.begin() + 1;
        return index2 * index1;
    }
}