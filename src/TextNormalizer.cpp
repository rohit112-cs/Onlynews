#include "TextNormalizer.h"
#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

TextNormalizer::TextNormalizer() {
    stopWords = {"the","a","an","and","or","but","in","on","at","to","for","of","with","by"};
}

string TextNormalizer::toLowerCase(const string& text) {
    string result = text;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c){ return tolower(c); });
    return result;
}

string TextNormalizer::removeExtraSpaces(const string& text) {
    string result;
    bool lastWasSpace = true;
    for (char c : text) {
        if (isspace((unsigned char)c)) {
            if (!lastWasSpace) {
                result += ' ';
                lastWasSpace = true;
            }
        } else {
            result += c;
            lastWasSpace = false;
        }
    }
    if (!result.empty() && isspace((unsigned char)result.back())) result.pop_back();
    return result;
}

vector<string> TextNormalizer::tokenize(const string& text) {
    vector<string> tokens;
    stringstream ss(text);
    string token;
    while (ss >> token) tokens.push_back(token);
    return tokens;
}

vector<string> TextNormalizer::removeStopWords(const vector<string>& words) {
    vector<string> filtered;
    for (const auto& w : words) if (stopWords.find(w) == stopWords.end()) filtered.push_back(w);
    return filtered;
}

string TextNormalizer::normalizeText(const string& text) {
    string normalized = toLowerCase(text);
    normalized = removeExtraSpaces(normalized);
    auto tokens = tokenize(normalized);
    auto filtered = removeStopWords(tokens);
    string out;
    for (size_t i=0;i<filtered.size();++i) {
        if (i) out += " ";
        out += filtered[i];
    }
    return out;
}
