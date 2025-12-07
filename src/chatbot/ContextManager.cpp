#include "chatbot/ContextManager.hpp"

void ContextManager::setLastTopic(const std::string &topic) { lastTopic = topic; }
std::string ContextManager::getLastTopic() const { return lastTopic.empty() ? "unknown" : lastTopic; }
