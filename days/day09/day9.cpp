//
// Created by Amelia Ng on 11/12/2022.
//

#include "../../advent.h"
#include <utility>
#include <unordered_set>
#include <iostream>
#include <string>
#include "../utils/string/stringutils.h"
#include <algorithm>
#include "../utils/pair/pairutils.h"
#include <array>
#include <vector>

namespace aoc::day9 {
    namespace {
        using namespace pairutils;

        int sign(int num) {
            if (num < 0) return -1;
            else if (num > 0) return 1;
            else return 0;
        }

        template<int T>
        struct Snake {
            std::array<AddablePair<int>, T> snake;

            std::pair<int, int> &tail() {
                return snake[T - 1].pair;
            }

            std::vector<std::pair<int, int>> move_head(AddablePair<int> direction, int steps) {
                std::vector<std::pair<int, int>> visited{};
                visited.push_back(tail());
                for (int i = 0; i < steps; ++i) {
                    snake[0] += direction;
                    for (int j = 0; j < T - 1; ++j) {
                        std::pair<int, int> diff = (snake[j] - snake[j + 1]).pair;
                        if (std::abs(diff.first) > 1 || std::abs(diff.second) > 1) {
                            snake[j + 1] += {sign(diff.first), sign(diff.second)};
                            visited.push_back(tail());
                        }
                    }
                }
                return visited;
            }
        };

        template <int T>
        unsigned int solve() {
            Snake<T> snek{};
            std::unordered_set<std::pair<int, int>, pairhash> visited;
            visited.insert(snek.tail());
            std::string line;

            while (std::getline(std::cin, line)) {
                std::vector delimited = stringutils::split(line, {' '});
                AddablePair<int> direction{};

                if (delimited[0] == "D") {
                    direction = {0, -1};
                } else if (delimited[0] == "U") {
                    direction = {0, 1};
                } else if (delimited[0] == "L") {
                    direction = {-1, 0};
                } else {
                    direction = {1, 0};
                }
                std::vector visited_vec = snek.move_head(direction, std::stoi(delimited[1]));
                visited.insert(visited_vec.begin(), visited_vec.end());
            }

            return visited.size();
        }
    }

    unsigned int solution1() {
        return solve<2>();
    }

    unsigned int solution2() {
        return solve<10>();
    }
}