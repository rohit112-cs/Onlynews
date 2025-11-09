#ifndef TEXT_NORMALIZER_H
#define TEXT_NORMALIZER_H

#include <string>
#include <vector>
#include <unordered_set>

class TextNormalizer {
private:
    std::unordered_set<std::string> stopWords;
public:
    TextNormalizer();
    std::string toLowerCase(const std::string& text);
    std::string removeExtraSpaces(const std::string& text);
    std::vector<std::string> tokenize(const std::string& text);
    std::vector<std::string> removeStopWords(const std::vector<std::string>& words);
    std::string normalizeText(const std::string& text);
};

#endif
