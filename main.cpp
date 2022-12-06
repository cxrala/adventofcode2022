#include <iostream>
#include "advent.h"
#include <chrono>


int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::cout << aoc::day6::solution1() << std::endl;
//    std::cout << "Answer:\n" << aoc::day5::solution2() << std::endl;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time diff: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms\n";
}
