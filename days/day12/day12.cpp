//
// Created by Amelia Ng on 12/12/2022.
//

#include "../../advent.h"
#include "../utils/matrix/matrixutils.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <array>
#include "../utils/pair/pairutils.h"

namespace aoc::day12 {
    namespace {
        template<bool fromS>
        struct Terrain {
            matrixutils::Mdarray<char, 2> grid;
            std::vector<std::pair<int, int>> starts;
            unsigned int rows;
            unsigned int cols;

            Terrain() {
                std::string line;
                std::vector<char> input;
                unsigned int r{};
                while (std::getline(std::cin, line)) {
                    ++r;
                    unsigned int j = 0;
                    for (char chr: line) {
                        if (((chr == 'S' || chr == 'a') && !fromS) || (chr == 'S' && fromS)) {
                            starts.emplace_back(r - 1, j);
                        }
                        input.push_back(chr);
                        ++j;

                    }
                }
                cols = input.size() / r;
                rows = r;
                grid = {input, {rows, cols}};
            }

            bool within_bounds(pairutils::AddablePair<int> &point) const {
                return point.pair.first >= 0 && point.pair.second >= 0 && point.pair.first < rows &&
                       point.pair.second < cols;
            }

            static bool is_steppable(char curr, char next) {
                if (curr == 'S') curr = 'a';
                if (curr == 'E') curr = 'z';
                if (next == 'S') next = 'a';
                if (next == 'E') next = 'z';
                return next == curr + 1 || next <= curr;
            }

//            bool has_visited(matrixutils::Mdarray<bool, 2> &visited, unsigned int i, unsigned int j) {
//                std::array<unsigned int, 2> indices{i, j};
//                return visited[indices];
//            }

            char char_at(pairutils::AddablePair<int> point) {
                return grid[{static_cast<unsigned int>(point.pair.first), static_cast<unsigned int>(point.pair.second)}];
            }

            //todo: figure out how to get rid of the static casts (because there are so many of them and they make my code unreadable)

            unsigned int solve1(std::pair<int, int> initial_start) {
//                matrixutils::Mdarray<bool, 2> visited{std::vector<bool>(rows * cols), {rows, cols}};
                std::vector<std::vector<bool>> visited(rows);
                for (auto & i : visited) {
                    i = std::vector<bool>(cols);
                }

                std::queue<std::pair<pairutils::AddablePair<int>, int>> queue{};
                queue.push({initial_start, 0});
                while (!queue.empty()) {
                    auto node_point = queue.front();
                    queue.pop();
                    if (char_at(node_point.first) == 'E') {
                        return node_point.second;
                    }
                    std::vector<pairutils::AddablePair<int>> directions{{0,  1},
                                                                        {1,  0},
                                                                        {0,  -1},
                                                                        {-1, 0}};
                    for (auto &direction: directions) {
                        auto neighbour_point = node_point.first + direction;
                        if (within_bounds(neighbour_point)) {
                            if (is_steppable(char_at(node_point.first), char_at(neighbour_point))
                            && !visited[neighbour_point.pair.first][neighbour_point.pair.second]) {
                                queue.push({neighbour_point, node_point.second + 1});
                                visited[neighbour_point.pair.first][neighbour_point.pair.second] = true;
//                                todo: figure out how on earth to do this
//                                visited[{static_cast<unsigned int>(neighbour_point.pair.first), static_cast<unsigned int>(neighbour_point.pair.second)}] = true;
                            }
                        }
                    }
                }
                return INT_MAX;
            };

            unsigned int solve2() {
                unsigned int min = UINT_MAX;
                for (auto point: starts) {
                    min = std::min(solve1(point), min);
                }
                return min;
            }
        };
    }

    unsigned int solution1() {
        Terrain<true> terrain{};
        return terrain.solve1(terrain.starts.front());
    }

    unsigned int solution2() {
        Terrain<false> terrain{};
        return terrain.solve2();
    }
}
