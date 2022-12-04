//
// Created by Amelia Ng on 04/12/2022.
//

#include "stringutils.h"
#include <string>

namespace stringutils {
    namespace {
        template<typename T>
        bool isOneOf(T elem, const std::vector<T> &vec) {
            for (T mem : vec) {
                if (elem == mem) return true;
            }
            return false;
        }
    }
    // WHAT THE FUCK IS GOING ON
    std::vector<std::string> split(const std::string &str, const std::vector<char> &delimiters) {
        std::vector<std::string> res{};
        std::string buffer;
        for (char chr : str) {
            if (isOneOf<char>(chr, delimiters)) {
                if (!buffer.empty()) {
                    res.push_back(buffer);
                    buffer = "";
                }
            } else {
                buffer += chr;
            }
        }
        if (!buffer.empty()) {
            res.push_back(buffer);
        }
        return res;
    }
}