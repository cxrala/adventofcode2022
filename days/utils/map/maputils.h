//
// Created by Amelia Ng on 06/12/2022.
//

#ifndef ADVENTOFCODE_MAPUTILS_H
#define ADVENTOFCODE_MAPUTILS_H
#include <unordered_map>

namespace maputils {
    template <typename T>
    void incr_or_initialise(T in, std::unordered_map<T, int> &map);

    template <typename T>
    void decr_or_erase(T out, std::unordered_map<T, int> &map);
}

#endif //ADVENTOFCODE_MAPUTILS_H
