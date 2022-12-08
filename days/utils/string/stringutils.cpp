//
// Created by Amelia Ng on 07/12/2022.
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

    bool is_numeric(std::string const &str) {
        std::string::const_iterator it = str.begin();
        while (it != str.end() && std::isdigit(*it)) ++it;
        return !str.empty() && it == str.end();
    }

}
