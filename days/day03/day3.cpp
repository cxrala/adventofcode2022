//
// Created by Amelia Ng on 03/12/2022.
//
#include "../../advent.h"
#include <cctype>
#include <unordered_set>
#include <iostream>
#include <array>

namespace aoc::day3 {
    namespace {
        int priority(char item) {
            if (std::islower(item)) return item - 'a' + 1;
            return item - 'A' + 27;
        }

        int solve(std::array<std::string, 1> const &r) {
            std::string rucksack = r[0];
            std::unordered_set<char> seen;

            for (int i = 0; i < rucksack.size() / 2; ++i) {
                seen.insert(rucksack[i]);
            }
            //Narrowing conversion from 'unsigned long' to signed type 'int' is implementation-defined warning, how to cast correctly? or do I just make i unsigned long?
            for (int i = rucksack.size() / 2; i < rucksack.size(); ++i) {
                if (seen.contains(rucksack[i])) return priority(rucksack[i]);
            }
            return 0;
        }

        int solve2(std::array<std::string, 3> const &rucksack) {
            std::unordered_set<char> seen, seen2;

            for (char item : rucksack[0]) {
                seen.insert(item);
            }
            for (char item : rucksack[1]) {
                if (seen.contains(item)) {
                    seen2.insert(item);
                }
            }
            for (char item : rucksack[2]) {
                if (seen2.contains(item)) {
                    return priority(item);
                }
            }
        }

        template<int T>
        unsigned int nya(int (&f)(std::array<std::string, T> const &)) {
            std::array<std::string, T> rucksack;
            unsigned int cumsum = 0;

            while (std::getline(std::cin, rucksack[0])) {
                for (int i = 1; i < T; ++i) {
                    std::getline(std::cin, rucksack[i]);
                }
                cumsum += f(rucksack);
            }
            return cumsum;
        }
    }


    unsigned int solution1() {
        return nya<1>(solve);
    }

    unsigned int solution2() {
        return nya<3>(solve2);
    }
}
