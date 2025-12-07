#include "chatbot/FuzzyMatcher.hpp"
#include <cctype>
#include <vector>

std::string FuzzyMatcher::normalize(const std::string &s) {
    std::string out;
    for(char c : s) {
        if (std::isalnum((unsigned char)c) || std::isspace((unsigned char)c))
            out.push_back(std::tolower((unsigned char)c));
    }
    return out;
}

int FuzzyMatcher::levenshtein(const std::string &a, const std::string &b) {
    const size_t n = a.size(), m = b.size();
    if(n == 0) return (int)m;
    if(m == 0) return (int)n;
    std::vector<int> prev(m+1), cur(m+1);
    for(size_t j = 0; j <= m; ++j) prev[j] = (int)j;
    for(size_t i = 1; i <= n; ++i) {
        cur[0] = (int)i;
        for(size_t j = 1; j <= m; ++j) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;
            cur[j] = std::min({ prev[j] + 1, cur[j-1] + 1, prev[j-1] + cost });
        }
        prev.swap(cur);
    }
    return prev[m];
}

bool FuzzyMatcher::isClose(const std::string &a, const std::string &b, int maxDist) {
    std::string na = normalize(a);
    std::string nb = normalize(b);
    int d = levenshtein(na, nb);
    return d <= maxDist;
}
