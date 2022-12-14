//
// Created by Amelia Ng on 06/12/2022.
//
#include "../../advent.h"
#include <utility>
#include <vector>
#include <optional>
#include <unordered_map>
#include <string>
#include <iostream>
#include "../utils/string/stringutils.h"
#include <iterator>
#include <functional>
#include <unordered_set>
#include <limits>

namespace aoc::day7 {
    namespace {
        struct Node;
    }
}

template <> struct std::hash<aoc::day7::Node> {
    std::size_t operator()(aoc::day7::Node const &node) const {
        return std::hash<aoc::day7::Node const *>{}(&node);
    }
};

namespace aoc::day7 {
    namespace {
        struct Node {
            Node *parent;
            std::string name;
            std::unordered_map<std::string, Node> children;
            std::optional<unsigned int> size;

            explicit Node(std::string str) : name(std::move(str)), parent(nullptr) {};

            Node(Node *parent, std::string str) : parent(parent), name(std::move(str)) {};

            Node(Node *parent, unsigned int size, std::string str) : parent(parent), size(size),
                                                                     name(std::move(str)) {};

            void addChild(Node &child) {
                if (!children.contains(child.name)) {
                    children.insert({child.name, child});
                }
            }

            bool operator==(Node const &node) const {
                return node.name == name && node.parent == parent;
            }
        };

        class Filesystem {
            Node root;
            unsigned int over{};

            unsigned int sizes_dfs(Node &node, std::unordered_set<Node> &visited) {
                if (node.children.empty()) {
                    return node.size.value();
                }
                visited.insert(node);

                unsigned int total = 0;

                for (auto it = node.children.begin(); it != node.children.end(); ++it) {
                    Node &child = it->second;
                    if (!visited.contains(child)) {
                        total += sizes_dfs(child, visited);
                    } else {
                        total += *child.size;
                    }
                }

                node.size = total;
                if (total <= 100000) over += total;
                return total;
            }

            void fill_sizes() {
                std::unordered_set<Node> visited{};
                sizes_dfs(root, visited);
            }

            Node &construct_filesystem_cin() {
                std::string line;
                Node *currDir = &root;

                while (std::getline(std::cin, line)) {
                    std::vector<std::string> split_line = stringutils::split(line, {' '});
                    if (split_line[0] == "$") {
                        if (split_line[1] == "cd") {
                            if (split_line[2] == "..") {
                                currDir = currDir->parent;
                            } else if (split_line[2] == "/") {
                                currDir = &root;
                            } else {
                                if (!currDir->children.contains(split_line[2])) {
                                    Node child{currDir, split_line[2]};
                                    currDir->addChild(child);
                                } else {
                                    currDir = &currDir->children.find(split_line[2])->second;
                                }
                            }
                        } else if (split_line[1] == "ls") {
                            continue;
                        }
                    } else if (stringutils::is_numeric(split_line[0])) {
                        Node child(currDir, std::stoul(split_line[0]), split_line[1]);
                        currDir->addChild(child);
                    } else if (split_line[0] == "dir") {
                        Node child{currDir, split_line[1]};
                        currDir->addChild(child);
                    }
                }

                fill_sizes();
                return root;
            }

        public:
            Filesystem() : root(Node{"/"}) {
                construct_filesystem_cin();
            };

            Node const &get_root() const {
                return root;

            }

            unsigned int get_total() const {
                return over;
            }
        };

        unsigned int recurse(Node const &node, std::unordered_set<Node> &visited, unsigned int lower_bound, unsigned int res) {
            if (node.children.empty()) {
                return node.size.value();
            }
            visited.insert(node);

            for (auto it = node.children.begin(); it != node.children.end(); ++it) {
                Node const &child = it->second;
                if (!visited.contains(child) && child.size >= lower_bound) {
                    res = std::min(res, recurse(child, visited, lower_bound, res));
                }
            }

            res = std::min(res, node.size.value());
            return res;
        }

        unsigned int find_smallest(Filesystem const &fs, unsigned int lb) {
            std::unordered_set<Node> visited{};
            return recurse(fs.get_root(), visited, lb, std::numeric_limits<int>::max());
        }
    }

    unsigned int solution1() {
        Filesystem fs{};
        return fs.get_total();
    }

    unsigned int solution2() {
        Filesystem fs{};
        Node const &root = fs.get_root();
        unsigned int remaining = 70000000 - fs.get_root().size.value();
        unsigned int upper = 30000000 - remaining;

        return find_smallest(fs, upper);
    }
}