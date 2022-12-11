//
// Created by Amelia Ng on 10/12/2022.
//
#include "../../advent.h"
#include "../utils/string/stringutils.h"
#include <iostream>
#include <vector>
#include <iterator>

namespace aoc::day10 {
    namespace {
        void addx(int &reg, int &cycles, int num) {
            reg += num;
            cycles += 2;
        }

        void noop(int &cycles) {
            ++cycles;
        }
    }

    unsigned int solution1() {
        std::string line;
        std::vector important_cycles = {20, 60, 100, 140, 180, 220};
        auto it = important_cycles.begin();
        int reg{1}, cycles{}, sum{};
        while (std::getline(std::cin, line) && it != important_cycles.end()) {
            std::vector delimited = stringutils::split(line, {' '});
            if (delimited[0] == "addx") {
                if (cycles + 2 >= *it) {
                    sum += reg * *it++;
                }
                addx(reg, cycles, std::stoi(delimited[1]));
                continue;
            }
            noop(cycles);
            if (cycles == *it) {
                sum += reg * *it++;
            }
        }
        return sum;
    }

    std::string solution2() {
        std::string res{};
        std::string line;
        int reg{1}, cycles{};
        while (std::getline(std::cin, line)) {
            std::vector delimited = stringutils::split(line, {' '});
            if (delimited[0] == "addx") {
                for (int k = 0; k < 2; ++k) {
                    if ((cycles + k) % 40 == 0 && cycles != 0) {
                        res += "\n";
                    }
                    if (reg - 1 <= (cycles + k) % 40 && (cycles + k) % 40 <= reg + 1) {
                        res += "#";
                    } else {
                        res += ".";
                    }
                }
                addx(reg, cycles, std::stoi(delimited[1]));
                continue;
            }
            if ((cycles) % 40 == 0) {
                res += "\n";
            }
            if (reg - 1 <= cycles % 40 && cycles % 40 <= reg + 1) {
                res += "#";
            } else {
                res += ".";
            }
            noop(cycles);
        }
        return res;
    }
}