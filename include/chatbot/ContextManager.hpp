#pragma once
#include <string>

class ContextManager {
    std::string lastTopic;
public:
    void setLastTopic(const std::string &topic);
    std::string getLastTopic() const;
};
