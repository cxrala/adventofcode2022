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
        // todo: extract into utils
        template <typename T>
        void incr_or_initialise(T in, std::unordered_map<T, int> &map) {
            if (map.contains(in)) {
                ++map[in];
            } else {
                map.insert({in, 1});
            }
        }

        template <typename T>
        void decr_or_erase(T out, std::unordered_map<T, int> &map) {
            if (--map[out] == 0) {
                map.erase(out);
            }
        }

        template <int T>
        unsigned int first_occurrence(std::string const &buffer) {
            std::unordered_map<char, int> window;

            for (int i = 0; i < buffer.size(); ++i) {
                if (i < T - 1) incr_or_initialise<char>(buffer[i], window);
                else {
                    incr_or_initialise<char>(buffer[i], window);
                    if (window.size() == T) return i + 1;
                    decr_or_erase<char>(buffer[i - (T - 1)], window);
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