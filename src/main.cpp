#include <iostream>
#include "chatbot/ChatbotEngine.hpp"

int main() {
    ChatbotEngine bot;
    std::string input;

    std::cout << "DSA Chatbot (improved). Type 'exit' to quit.\n\n";
    while(true) {
        std::cout << "User: ";
        std::getline(std::cin, input);
        if(input == "exit" || input == "quit") break;
        std::string reply = bot.respond(input);
        std::cout << "Bot: " << reply << "\n\n";
    }
    std::cout << "Goodbye!\n";
    return 0;
}
