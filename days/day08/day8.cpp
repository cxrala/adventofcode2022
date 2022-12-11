//
// Created by Amelia Ng on 08/12/2022.
//
#include "../../advent.h"
#include <utility>
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include "../utils/matrix/matrixutils.h"

namespace aoc::day8 {
    namespace {
        class Forest {
            matrixutils::Mdarray<std::pair<char, bool>, 2> forest;
            unsigned int rows{};
            unsigned int cols;

            std::pair<char, bool> &getPair(matrixutils::Mdarray<int, 2> &point) {
                return forest[{static_cast<unsigned int>(point[{0, 0}]), static_cast<unsigned int>(point[{1, 0}])}];
            }

            unsigned int total_in_line(matrixutils::Mdarray<int, 2> const &direction,
                                       matrixutils::Mdarray<int, 2> start,
                                       matrixutils::Mdarray<int, 2> end) {
                unsigned int total{};
                auto it = std::move(start);
                std::pair<char, bool> *curr;
                char upper_bound = '0' - 1;
                end += direction;
                while (it != end) {
                    curr = &forest[{static_cast<unsigned int>(it[{0, 0}]), static_cast<unsigned int>(it[{1, 0}])}];
                    it += direction;
                    if (curr->first > upper_bound) {
                        if (!curr->second) ++total;
                        curr->second = true;
                        if (curr->first == '9') {
                            break;
                        }
                        upper_bound = curr->first;
                    }
                }
                return total;
            }

            unsigned int scenic_from(matrixutils::Mdarray<int, 2> point) {
                std::vector<matrixutils::Mdarray<int, 2>> directions{
                        {{1,  0},  {2, 1}},
                        {{0,  -1}, {2, 1}},
                        {{-1, 0},  {2, 1}},
                        {{0,  1},  {2, 1}}};

                unsigned int score = 1;
                unsigned int distance;
                for (matrixutils::Mdarray<int, 2> &direction: directions) {
                    matrixutils::Mdarray<int, 2> it = point;
                    bool blocked = false;
                    distance = 0;
                    while (!blocked) {
                        it += direction;
                        if (it[{0, 0}] < 0 || it[{0, 0}] >= rows || it[{1, 0}] < 0 || it[{1, 0}] >= cols) {
                            break;
                        } else if (getPair(it).first >= getPair(point).first) {
                            blocked = true;
                        }
                        ++distance;
                    }
                    score *= distance;

                }

                return score;
            }

        public:
            Forest() {
                std::string row;
                std::getline(std::cin, row);
                cols = row.size();
                std::vector<std::pair<char, bool>> trees{};

                do {
                    ++rows;
                    for (char c: row) {
                        trees.emplace_back(c, false);
                    }
                } while (std::getline(std::cin, row));

                forest = {trees, {rows, cols}};
            }

            unsigned int count_from_side() {
                unsigned int total{};
                for (int i = 0; i < rows; ++i) {
                    matrixutils::Mdarray<int, 2> direction1{{0, 1},
                                                            {2, 1}};
                    total += total_in_line(direction1, {{i, 0},
                                                        {2, 1}}, {{i, static_cast<int>(cols) - 1},
                                                                  {2, 1}});
                    matrixutils::Mdarray<int, 2> direction2{{0, -1},
                                                            {2, 1}};
                    total += total_in_line(direction2, {{i, static_cast<int>(cols) - 1},
                                                        {2, 1}}, {{i, 0},
                                                                  {2, 1}});
                }
                for (int i = 0; i < cols; ++i) {
                    matrixutils::Mdarray<int, 2> direction3{{1, 0},
                                                            {2, 1}};
                    total += total_in_line(direction3, {{0, i},
                                                        {2, 1}}, {{static_cast<int>(rows) - 1, i},
                                                                  {2,                          1}});
                    matrixutils::Mdarray<int, 2> direction4{{-1, 0},
                                                            {2,  1}};
                    total += total_in_line(direction4, {{static_cast<int>(rows) - 1, i},
                                                        {2,                          1}}, {{0, i},
                                                                                           {2, 1}});
                }

                return total;
            }

            unsigned int get_scenic() {
                unsigned int solution = 0;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrixutils::Mdarray<int, 2> point{{i, j},
                                                           {2, 1}};
                        solution = std::max(solution, scenic_from(point));
                    }
                }
                return solution;
            }
        };
    }

    unsigned int solution1() {
        Forest forest{};
        return forest.count_from_side();
    }

    unsigned int solution2() {
        Forest forest{};
        return forest.get_scenic();
    }
}