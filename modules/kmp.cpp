#include <iostream>
#include <vector>
using namespace std;

vector<int> buildLPS(const string &pattern) {
    int n = pattern.size();
    vector<int> lps(n);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = lps[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        lps[i] = j;
    }
    return lps;
}

bool kmpSearch(const string &text, const string &pattern) {
    if (pattern.empty()) return false;
    vector<int> lps = buildLPS(pattern);
    int j = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        while (j > 0 && text[i] != pattern[j])
            j = lps[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == (int)pattern.size())
            return true;
    }
    return false;
}