//
// Created by Amelia Ng on 02/12/2022.
//

#include "../../advent.h"
#include <string>
#include <iostream>

namespace aoc::day2 {

    unsigned int score(const std::string &str) {
        int first = str.at(0) - 'A';
        int second = str.at(2) - 'X';
        if (first == second) return 3 + (second + 1);
        if (first == ((second + 2) % 3)) return 6 + (second + 1);
        return second + 1;
    }

    unsigned int score2(const std::string &str) {
        int first = str.at(0) - 'A';
        int second = str.at(2) - 'X';
        switch (second) {
            case 0:
                return (first + 2) % 3 + 1;
            case 1:
                return 4 + first;
            default:
                return 7 + (first + 1) % 3;
        }
    }

    unsigned int solution1() {
        std::string round;
        unsigned int total = 0;
        while (std::getline(std::cin, round)) {
            total += score(round);
        }
        return total;
    }

    unsigned int solution2() {
        std::string round;
        unsigned int total = 0;
        while (std::getline(std::cin, round)) {
            total += score2(round);
        }
        return total;
    }
}