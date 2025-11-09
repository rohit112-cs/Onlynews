#ifndef NEWS_DETECTOR_H
#define NEWS_DETECTOR_H

#include <string>
#include "Trie.h"
#include "DatasetManager.h"

class NewsDetector {
private:
    Trie trustedTrie;
    Trie fakeTrie;
    double similarityThreshold;
    double patternThreshold;
public:
    NewsDetector();
    void initialize(DatasetManager& datasetManager);
    std::string classifyHeadline(const std::string& headline);
    void analyzeHeadline(const std::string& headline);
    void setThresholds(double similarity, double pattern);
};

#endif
