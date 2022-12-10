//
// Created by Amelia Ng on 06/12/2022.
//

#ifndef ADVENTOFCODE_MAPUTILS_H
#define ADVENTOFCODE_MAPUTILS_H
#include <unordered_map>

namespace maputils {
    template <typename T>
    void decr_or_erase(T out, std::unordered_map<T, int> &map) {
        /*if (--map[out] == 0) {
            map.erase(out);
        }*/
        const auto iter = map.find(out);
        if (--iter->second == 0) {
            map.erase(iter);
        }
    }
}

#endif //ADVENTOFCODE_MAPUTILS_H
