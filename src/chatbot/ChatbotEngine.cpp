#include "chatbot/ChatbotEngine.hpp"
#include "chatbot/MessageParser.hpp"
#include "chatbot/ResponseFormatter.hpp"
#include "chatbot/ContextManager.hpp"
#include "chatbot/FuzzyMatcher.hpp"
#include <sstream>

// optional: include DSA headers if you want to construct/use them at runtime
#include "../include/dsa/BST.hpp"   // adjust path if necessary

ChatbotEngine::ChatbotEngine() {
    // nothing for now
}

static std::string joinInts(const std::vector<int>& v) {
    std::ostringstream o;
    for(size_t i=0;i<v.size();++i) {
        if(i) o << ", ";
        o << v[i];
    }
    return o.str();
}

std::string ChatbotEngine::respond(const std::string &userInput) {
    std::string normalized = FuzzyMatcher::normalize(userInput);
    std::string topic = parser.detectTopic(normalized);
    std::string intent = parser.detectIntent(normalized);

    // if no topic found but there is context, try to use last topic
    if(topic == "unknown") {
        std::string last = context.getLastTopic();
        if(last != "unknown") topic = last;
    } else {
        // remember topic
        context.setLastTopic(topic);
    }

    if(intent == "definition") {
        return formatter.definition(topic);
    }

    if(intent == "example") {
        return formatter.example(topic);
    }

    if(intent == "build") {
        // handle "make a BST from 1,5,3"
        std::vector<int> nums = parser.parseNumbers(userInput);
        if(nums.empty()) return "I couldn't find numbers to build from. Example: 'Make a BST from 1,5,3'";
        // Optional: use actual BST class to insert numbers and show inorder
        try {
            BST bst;
            for(int n : nums) bst.insert(n);
            auto inorder = bst.getInorder();
            std::string detail = "nodes -> " + joinInts(nums) + ". Inorder: " + joinInts(inorder);
            return formatter.confirmBuild("BST", detail);
        } catch(...) {
            // If BST class signature mismatches, fallback message
            return formatter.confirmBuild(topic, "nodes -> " + joinInts(nums));
        }
    }

    if(intent == "operate") {
        // simple operate handling: e.g., "search 5 in 1,2,5"
        std::vector<int> nums = parser.parseNumbers(userInput);
        if(!nums.empty()) {
            // assume first is target if phrase contains 'search' or similar
            if(userInput.find("search") != std::string::npos || userInput.find("find") != std::string::npos) {
                int target = nums[0];
                // if more numbers, treat rest as array
                if(nums.size() >= 2) {
                    std::vector<int> arr(nums.begin()+1, nums.end());
                    // perform linear search
                    for(size_t i=0;i<arr.size();++i) if(arr[i]==target) {
                        std::ostringstream os;
                        os << "Found " << target << " at index " << i << " (0-based).";
                        return os.str();
                    }
                    return "Not found.";
                } else return "Please provide the array to search in: e.g. 'search 5 in 2 5 7'";
            }
        }
    }

    // If topic understood but intent unknown, offer suggestions
    if(topic != "unknown") {
        return "I understand the topic '" + topic + "' but not the exact request. Try: 'What is " + topic + "?', 'Show example of " + topic + "', or 'Make a " + topic + " from 1,5,3'.";
    }

    return formatter.notUnderstood();
}
