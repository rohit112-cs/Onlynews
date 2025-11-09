#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#include <string>

class EditDistance {
public:
    static int calculate(const std::string& str1, const std::string& str2);
    static double calculateSimilarity(const std::string& str1, const std::string& str2);
};

#endif
