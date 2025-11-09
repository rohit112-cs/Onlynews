#ifndef PATTERN_MATCHER_H
#define PATTERN_MATCHER_H

#include <vector>
#include <string>

class PatternMatcher {
public:
    static std::vector<int> KMPSearch(const std::string& text, const std::string& pattern);
    static std::vector<int> RabinKarpSearch(const std::string& text, const std::string& pattern, int prime = 101);
    static bool containsPattern(const std::string& text, const std::string& pattern, double threshold = 0.8);
};

#endif
