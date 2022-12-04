//
// Created by Amelia Ng on 01/12/2022.
//

#include "../../advent.h"
#include <iostream>
#include <string>
#include <queue>
#include <utility>

namespace aoc::day1 {

    template<int T>
    unsigned int lol() {
        std::vector<unsigned int> vec;
        vec.reserve(T + 1);
        std::priority_queue pq{std::greater{}, std::move(vec)};

        std::string calories;
        unsigned int cumsum = 0;

        while (std::getline(std::cin, calories)) {
            if (calories.empty()) {
                pq.push(cumsum);
                if (pq.size() == T + 1) {
                    pq.pop();
                }
                cumsum = 0;
            } else {
                cumsum += std::stoul(calories);
            }
        }
        pq.push(cumsum);
        pq.pop();

        cumsum = 0;
        while (!pq.empty()) {
            cumsum += pq.top();
            pq.pop();
        }

        return cumsum;
    }

    unsigned int solution1() {
        return lol<1>();
    }

    unsigned int solution2() {
        return lol<3>();
    }
}