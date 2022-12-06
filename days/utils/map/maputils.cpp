//
// Created by Amelia Ng on 06/12/2022.
//

#include "maputils.h"

namespace maputils {
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

}