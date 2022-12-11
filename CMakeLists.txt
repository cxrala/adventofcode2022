cmake_minimum_required(VERSION 3.21)
project(adventofcode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_LIBCPP_DEBUG=1")

add_executable(adventofcode main.cpp advent.h days/day01/day1.cpp days/day02/day2.cpp days/day03/day3.cpp debug.cpp days/day04/day4.cpp days/utils/string/stringutils.h days/day05/day5.cpp days/day06/day6.cpp days/utils/map/maputils.h days/day07/day7.cpp days/utils/string/stringutils.cpp days/day08/day8.cpp days/utils/matrix/matrixutils.h days/day10/day10.cpp days/day09/day9.cpp days/utils/pair/pairutils.h)
