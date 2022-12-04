//
// Created by Amelia Ng on 04/12/2022.
//
#include "../../advent.h"
#include <string>
#include "../utils/string/stringutils.h"
#include <iostream>
#include <vector>

namespace aoc::day4 {
    namespace {

        std::vector<int> getSections(std::string const &assignments) {
            std::vector<char> delimiters{'-', ','};
            std::vector<std::string> delimited = stringutils::split(assignments, delimiters);
            std::vector<int> sections;
            std::transform(delimited.begin(), delimited.end(), std::back_inserter(sections), [](const std::string &str) { return std::stoi(str); });
            return sections;
        }

        bool solve1(std::string const & assignments) {
            std::vector<int> sections = getSections(assignments);
            if (sections[0] < sections[2]) {
                return sections[3] <= sections[1];
            } else if (sections [2] < sections[0]) {
                return sections[3] >= sections[1];
            }
            return true;
        }

        bool solve2(std::string const & assignments) {
            std::vector<int> sections = getSections(assignments);
            if (sections[0] < sections[2]) return sections[1] >= sections[2];
            else if (sections[2] < sections[0]) return sections[3] >= sections[0];
            return true;
        }

        unsigned int getSolution(bool (&solver)(std::string const & assignments)) {
            std::string assignment;
            unsigned int cumsum = 0;
            while (std::getline(std::cin, assignment)) {
                if (solver(assignment)) {
                    ++cumsum;
                }
            }
            return cumsum;
        }
    }

    unsigned int solution1(bool (&solver)(std::string const & assignments)) {
        return getSolution(solve1);
    }

    unsigned int solution2() {
        return getSolution(solve2);

    }

}