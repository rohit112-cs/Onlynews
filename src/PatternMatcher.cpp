#include "PatternMatcher.h"
#include <vector>

using namespace std;

static vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m,0);
    int len=0,i=1;
    while (i<m) {
        if (pattern[i]==pattern[len]) { len++; lps[i]=len; i++; }
        else { if (len!=0) len = lps[len-1]; else { lps[i]=0; i++; } }
    }
    return lps;
}

vector<int> PatternMatcher::KMPSearch(const string& text, const string& pattern) {
    vector<int> matches;
    if (pattern.empty() || text.empty()) return matches;
    auto lps = computeLPSArray(pattern);
    int i=0,j=0,n=text.length(),m=pattern.length();
    while (i<n) {
        if (pattern[j]==text[i]) { i++; j++; }
        if (j==m) { matches.push_back(i-j); j = lps[j-1]; }
        else if (i<n && pattern[j]!=text[i]) { if (j!=0) j = lps[j-1]; else i++; }
    }
    return matches;
}

vector<int> PatternMatcher::RabinKarpSearch(const string& text, const string& pattern, int prime) {
    vector<int> matches;
    if (pattern.empty() || text.empty()) return matches;
    int n=text.length(), m=pattern.length();
    int patternHash=0, textHash=0, h=1;
    for (int i=0;i<m-1;++i) h = (h*256)%prime;
    for (int i=0;i<m;++i) { patternHash = (256*patternHash + pattern[i])%prime; textHash = (256*textHash + text[i])%prime; }
    for (int i=0;i<=n-m;++i) {
        if (patternHash==textHash) {
            bool match=true;
            for (int j=0;j<m;++j) if (text[i+j]!=pattern[j]) { match=false; break; }
            if (match) matches.push_back(i);
        }
        if (i < n-m) {
            textHash = (256*(textHash - text[i]*h) + text[i+m])%prime;
            if (textHash < 0) textHash += prime;
        }
    }
    return matches;
}

bool PatternMatcher::containsPattern(const string& text, const string& pattern, double threshold) {
    if (pattern.length() < 3) return false;
    if (text.find(pattern) != string::npos) return true;
    auto kmp = KMPSearch(text, pattern);
    if (!kmp.empty()) return true;
    if (pattern.length() >= text.length() * threshold) {
        auto rk = RabinKarpSearch(text, pattern);
        return !rk.empty();
    }
    return false;
}
