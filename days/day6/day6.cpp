//
// Created by Amelia Ng on 06/12/2022.
//

#include "../../advent.h"
#include <iostream>
#include <string>
#include <unordered_map>

namespace aoc::day6 {
    namespace {
        // todo: make templated
        void incr_or_initialise(char in, std::unordered_map<char, int> &map) {
            if (map.contains(in)) {
                ++map[in];
            } else {
                map.insert({in, 1});
            }
        }

        void decr_or_erase(char out, std::unordered_map<char, int> &map) {
            --map[out];
            if (map[out] == 0) {
                map.erase(out);
            }
        }

        template <int T>
        unsigned int first_occurrence(std::string const &buffer) {
            std::unordered_map<char, int> window;

            for (int i = 0; i < buffer.size(); ++i) {
                if (i < T - 1) incr_or_initialise(buffer[i], window);
                else {
                    incr_or_initialise(buffer[i], window);
                    if (window.size() == T) return i + 1;
                    decr_or_erase(buffer[i - (T - 1)], window);
                }
            }
        }
    }

    unsigned int solution1() {
        std::string buffer;
        std::getline(std::cin, buffer);
        return first_occurrence<4>(buffer);
    }

    unsigned int solution2() {
        std::string buffer;
        std::getline(std::cin, buffer);
        return first_occurrence<14>(buffer);
    }
}