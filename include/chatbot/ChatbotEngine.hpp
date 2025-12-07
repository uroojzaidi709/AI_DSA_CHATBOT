#pragma once
#include <string>
#include "MessageParser.hpp"
#include "ResponseFormatter.hpp"
#include "ContextManager.hpp"
#include "FuzzyMatcher.hpp"

class ChatbotEngine {
    MessageParser parser;
    ResponseFormatter formatter;
    ContextManager context;
public:
    ChatbotEngine();

    // main API - pass raw user input get a reply
    std::string respond(const std::string &userInput);
};
