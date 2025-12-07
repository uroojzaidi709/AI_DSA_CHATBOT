#pragma once
#include <string>
#include <algorithm>

class FuzzyMatcher {
public:
    // Normalize: lowercase and remove punctuation
    static std::string normalize(const std::string &s);

    // Return Levenshtein distance
    static int levenshtein(const std::string &a, const std::string &b);

    // Returns whether words are "close"
    static bool isClose(const std::string &a, const std::string &b, int maxDist = 2);
};
