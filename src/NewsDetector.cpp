#include "NewsDetector.h"
#include "PatternMatcher.h"
#include "EditDistance.h"
#include "TextNormalizer.h"
#include <iostream>
#include <algorithm>

using namespace std;

NewsDetector::NewsDetector(): similarityThreshold(0.8), patternThreshold(0.6) {}

void NewsDetector::initialize(DatasetManager& datasetManager) {
    auto trustedHeadlines = datasetManager.getHeadlinesByCategory("trusted");
    for (const auto& h : trustedHeadlines) trustedTrie.insert(h,h);
    auto fakeHeadlines = datasetManager.getHeadlinesByCategory("fake");
    for (const auto& h : fakeHeadlines) fakeTrie.insert(h,h);
    cout << "Initialized with " << trustedHeadlines.size() << " trusted and "
         << fakeHeadlines.size() << " fake headlines\n";
}

string NewsDetector::classifyHeadline(const string& headline) {
    TextNormalizer normalizer;
    string normalized = normalizer.normalizeText(headline);
    if (trustedTrie.searchExact(normalized)) return "Trusted";
    if (fakeTrie.searchExact(normalized)) return "Fake";

    string prefix = normalized.substr(0, min<size_t>(3, normalized.size()));
    auto fakePatterns = fakeTrie.searchPrefix(prefix);
    for (const auto& pattern : fakePatterns) {
        if (PatternMatcher::containsPattern(normalized, pattern, patternThreshold)) return "Suspicious";
    }

    double maxSim = 0.0; string closest;
    auto trusted = trustedTrie.searchPrefix(prefix);
    for (const auto& t : trusted) {
        double s = EditDistance::calculateSimilarity(normalized, t);
        if (s>maxSim) { maxSim=s; closest=t; }
    }
    auto fakes = fakeTrie.searchPrefix(prefix);
    for (const auto& f: fakes) {
        double s = EditDistance::calculateSimilarity(normalized, f);
        if (s>maxSim) { maxSim=s; closest=f; }
    }

    if (maxSim > similarityThreshold) {
        if (trustedTrie.searchExact(closest)) return "Trusted"; else return "Fake";
    }
    return "Suspicious";
}

void NewsDetector::analyzeHeadline(const string& headline) {
    TextNormalizer normalizer;
    string normalized = normalizer.normalizeText(headline);
    string classification = classifyHeadline(headline);
    cout << "\n=== Analysis Result ===\nOriginal: " << headline << "\nNormalized: " << normalized
         << "\nClassification: " << classification << "\n";
    auto simT = trustedTrie.searchPrefix(normalized.substr(0, min<size_t>(3, normalized.size())));
    auto simF = fakeTrie.searchPrefix(normalized.substr(0, min<size_t>(3, normalized.size())));
    if (!simT.empty() || !simF.empty()) {
        cout << "\nSimilar headlines found:\n";
        for (size_t i=0;i<min(simT.size(), size_t(3));++i) cout << "  Trusted: " << simT[i] << "\n";
        for (size_t i=0;i<min(simF.size(), size_t(3));++i) cout << "  Fake:    " << simF[i] << "\n";
    }
}

void NewsDetector::setThresholds(double similarity, double pattern) {
    similarityThreshold = similarity;
    patternThreshold = pattern;
}
