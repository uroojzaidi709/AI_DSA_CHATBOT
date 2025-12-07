#include "chatbot/MessageParser.hpp"
#include "chatbot/FuzzyMatcher.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

static std::string simpleLower(const std::string &s) {
    std::string out;
    for(char c : s) {
        if(std::isalnum((unsigned char)c) || std::isspace((unsigned char)c) || c==',' ) out.push_back(std::tolower((unsigned char)c));
    }
    return out;
}

std::vector<std::string> MessageParser::tokens(const std::string &input) const {
    std::string s = simpleLower(input);
    std::istringstream ss(s);
    std::vector<std::string> t;
    std::string w;
    while(ss >> w) t.push_back(w);
    return t;
}

std::string MessageParser::detectTopic(const std::string &input) const {
    std::vector<std::string> common = {"stack","queue","heap","bst","tree","graph","sorting","searching","knapsack","dp","trie","kmp","rabinkarp","hashmap","linkedlist","linked","list","binary","binarysearch"};
    std::vector<std::string> toks = tokens(input);
    for(const auto &tok : toks) {
        for(const auto &c : common) {
            if(FuzzyMatcher::isClose(tok, c, 1) || tok.find(c) != std::string::npos) {
                // treat "binary" or "binarysearch" as bst if combined with "search" or "tree"
                if(c=="binary" || c=="binarysearch") return "bst";
                if(c=="linked" || c=="list" || c=="linkedlist") return "linkedlist";
                if(c=="tree") return "bst";
                return c;
            }
        }
    }
    return "unknown";
}

std::string MessageParser::detectIntent(const std::string &input) const {
    std::vector<std::string> defWords = {"what","define","definition","explain","meaning","describe"};
    std::vector<std::string> exWords  = {"example","sample","code","implementation","demo","show","how to","show me"};
    std::vector<std::string> buildWords = {"make","build","create","construct","insert","from","take"};
    std::vector<std::string> opWords = {"search","find","traverse","traversal","push","pop","enqueue","dequeue","delete","remove","sort","run","execute","compute"};

    std::string s = simpleLower(input);

    for(const auto &w : defWords) if(s.find(w) != std::string::npos) return "definition";
    for(const auto &w : exWords)  if(s.find(w) != std::string::npos) return "example";
    for(const auto &w : buildWords) if(s.find(w) != std::string::npos && s.find("from") != std::string::npos) return "build";
    for(const auto &w : opWords) if(s.find(w) != std::string::npos) return "operate";

    return "unknown";
}

std::vector<int> MessageParser::parseNumbers(const std::string &input) const {
    std::vector<int> out;
    std::string s = input;
    // keep digits, spaces, commas, minus
    std::string filtered;
    for(char c : s) {
        if(std::isdigit((unsigned char)c) || c=='-' || c==',' || std::isspace((unsigned char)c)) filtered.push_back(c);
        else filtered.push_back(' ');
    }
    std::istringstream ss(filtered);
    std::string token;
    while(std::getline(ss, token, ',')) {
        std::istringstream s2(token);
        int num;
        while(s2 >> num) out.push_back(num);
    }
    return out;
}
