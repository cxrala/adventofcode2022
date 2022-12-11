//
// Created by Amelia Ng on 11/12/2022.
//

#ifndef ADVENTOFCODE_PAIRUTILS_H
#define ADVENTOFCODE_PAIRUTILS_H

#include <utility>
namespace pairutils {
    struct pairhash {
        template <typename T, typename U>
        std::size_t operator()(const std::pair<T, U> &x) const
        {
            return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
        }
    };

    template<typename T>
    struct AddablePair {
        std::pair<T, T> pair;
        AddablePair(T first, T second) : pair(std::pair<T, T>{first, second}) {};
        AddablePair() = default;
        AddablePair &operator+=(AddablePair const &other) {
            pair.first += other.pair.first;
            pair.second += other.pair.second;
            return *this;
        };

        AddablePair &operator+=(AddablePair const &&other) {
            return *this += other;
        };

        AddablePair operator+(AddablePair const &other) const {
            AddablePair res(*this);
            res += other;
            return res;
        }

        AddablePair &operator-=(AddablePair const &other) {
            pair.first -= other.pair.first;
            pair.second -= other.pair.second;
            return *this;
        };

        AddablePair operator-(AddablePair const &other) const {
            AddablePair res(*this);
            res -= other;
            return res;
        }

        bool operator==(AddablePair const &other) const {
            return pair.first == other.pair.first && pair.second == other.pair.second;
        }

        bool operator!=(AddablePair const &other) const = default;
    };
}

#endif //ADVENTOFCODE_PAIRUTILS_H
