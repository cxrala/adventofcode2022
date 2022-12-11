//
// Created by Amelia Ng on 06/12/2022.
//

#include "../../advent.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "../utils/map/maputils.h"

namespace aoc::day6 {
    namespace {
        template <int T>
        unsigned int first_occurrence(std::string const &buffer) {
            std::unordered_map<char, int> window;

            for (int i = 0; i < buffer.size(); ++i) {
                if (i < T - 1) {
                    ++window[buffer[i]];
                }
                else {
                    ++window[buffer[i]];
                    if (window.size() == T) return i + 1;
                    maputils:: decr_or_erase<char>(buffer[i - (T - 1)], window);
                }
            }
        }

        template <int T>
        unsigned int solve() {
            std::string buffer;
            std::getline(std::cin, buffer);
            return first_occurrence<T>(buffer);
        }
    }

    unsigned int solution1() {
        return solve<4>();
    }

    unsigned int solution2() {
        return solve<14>();
    }
}