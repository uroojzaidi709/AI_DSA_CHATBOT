#pragma once
#include <string>
#include <vector>

class MessageParser {
public:
    // returns normalized tokens (lowercase, punctuation removed)
    std::vector<std::string> tokens(const std::string &input) const;

    // detect primary topic (stack, queue, heap, bst, graph, sorting, searching, knapsack, dp, trie, kmp, rabinkarp, hashmap)
    std::string detectTopic(const std::string &input) const;

    // detect intent: definition | example | build | operate | unknown
    std::string detectIntent(const std::string &input) const;

    // try parse list of integers from input (e.g., "1,5,3,6" or "1 5 3 6")
    std::vector<int> parseNumbers(const std::string &input) const;
};
