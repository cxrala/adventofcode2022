//
// Created by Amelia Ng on 05/12/2022.
//

#include "../../advent.h"
#include <deque>
#include <iostream>
#include <string>
#include "../utils/string/stringutils.h"
#include <iterator>

namespace aoc::day5 {
    namespace {
        template <typename T>
        struct Stack {
            std::deque<T> boxes{};

            void move(int quantity, Stack &to) {
                for (int i = 0; i < quantity; ++i) {
                    T box = this->boxes.back();
                    this->boxes.pop_back();
                    to.boxes.push_back(box);
                }
            }

            void move9001(int quantity, Stack &to) {
                to.boxes.insert(to.boxes.end(), this->boxes.end() - quantity, this->boxes.end());
                this->boxes.erase(this->boxes.end() - quantity, this->boxes.end());
            }

            void push_front(T &item) {
                boxes.push_front(item);
            }

        };

        std::string solve(void (Stack<char>::*mover)(int, Stack<char> &)) {
            std::string line;
            std::string message;
            bool moveInstr = false;
            std::vector<Stack<char>> stacks;

            while (std::getline(std::cin, line)) {
                if (!moveInstr) {
                    if (line == "-") {
                        moveInstr = true;
                        continue;
                    }
                    Stack<char> Stack;
                    for (char i : line) {
                        Stack.push_front(i);
                    }
                    stacks.push_back(Stack);
                } else {
                    std::vector<std::string> delimited = stringutils::split(line, {' '});
                    (stacks[std::stoi(delimited[3]) - 1].*mover)(std::stoi(delimited[1]), stacks[std::stoi(delimited[5]) - 1]);
                }
            }

            for(Stack<char> Stack : stacks) {
                message += Stack.boxes.back();
            }

            return message;
        }
    }

    std::string solution1() {
        return solve(&Stack<char>::move);
    }

    std::string solution2() {
        return solve(&Stack<char>::move9001);
    }

}