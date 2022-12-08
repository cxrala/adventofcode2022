//
// Created by Amelia Ng on 04/12/2022.
//

#ifndef ADVENTOFCODE_STRINGUTILS_H
#define ADVENTOFCODE_STRINGUTILS_H

#include <vector>
#include <string>

namespace stringutils {
    std::vector<std::string> split(std::string const &str, std::vector<char> const &delimiters);
    bool is_numeric(std::string const &str);
}

#endif //ADVENTOFCODE_STRINGUTILS_H
