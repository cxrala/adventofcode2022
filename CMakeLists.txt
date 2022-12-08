cmake_minimum_required(VERSION 3.21)
project(adventofcode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_LIBCPP_DEBUG=1")

add_executable(adventofcode main.cpp advent.h days/day1/day1.cpp days/day2/day2.cpp days/day3/day3.cpp debug.cpp days/day4/day4.cpp days/utils/string/stringutils.h days/day5/day5.cpp days/day6/day6.cpp days/utils/map/maputils.h days/day7/day7.cpp days/utils/string/stringutils.cpp)
