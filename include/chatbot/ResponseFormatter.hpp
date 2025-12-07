#pragma once
#include <string>

class ResponseFormatter {
public:
    std::string definition(const std::string &topic) const;
    std::string example(const std::string &topic) const;
    std::string notUnderstood() const;
    std::string confirmBuild(const std::string &topic, const std::string &detail) const;
};
