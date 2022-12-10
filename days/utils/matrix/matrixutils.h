//
// Created by Amelia Ng on 08/12/2022.
//

#ifndef ADVENTOFCODE_MATRIXUTILS_H
#define ADVENTOFCODE_MATRIXUTILS_H
#include <vector>
#include <array>
#include <utility>

namespace matrixutils {
    template<typename T, unsigned int dimensions>
    class Mdarray {
        std::vector<T> array;
        std::array<unsigned int, dimensions> sizes;

    public:
        friend class Mdarray;

        Mdarray(std::vector<T> vec, std::array<unsigned int, dimensions> sizes) : array(std::move(vec)), sizes(sizes){}
        Mdarray() = default;

        T &operator[](std::array<unsigned int, dimensions> indexes) {
            int index{};
            int temp_size = array.size();

            for (int i = indexes.size(); i > 0; --i) {
                temp_size /= sizes[indexes.size() - i];
                index += temp_size * indexes[indexes.size() - i];
            }

            return array[index];
        }

        T const &operator[](std::array<unsigned int, dimensions> indexes) const {
            return const_cast<Mdarray &>(*this)[indexes];
        }

        Mdarray &operator+=(Mdarray const &other){
            for (int i = 0; i < array.size(); ++i) {
                array[i] += other.array[i];
            }
            return *this;
        }

        Mdarray operator+(Mdarray const &other) const {
            Mdarray res{*this};
            res += other;
            return res;
        }

        bool operator==(Mdarray const &other) const {
            return array == other.array;
        }

        bool operator!=(Mdarray const &other) const = default;
    };
}

#endif //ADVENTOFCODE_MATRIXUTILS_H