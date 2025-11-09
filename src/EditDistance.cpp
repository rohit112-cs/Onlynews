#include "EditDistance.h"
#include <vector>
#include <algorithm>

using namespace std;

int EditDistance::calculate(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for (int i=0;i<=m;++i) dp[i][0]=i;
    for (int j=0;j<=n;++j) dp[0][j]=j;
    for (int i=1;i<=m;++i) {
        for (int j=1;j<=n;++j) {
            if (s1[i-1]==s2[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[m][n];
}

double EditDistance::calculateSimilarity(const string& s1, const string& s2) {
    if (s1.empty() && s2.empty()) return 1.0;
    if (s1.empty() || s2.empty()) return 0.0;
    int d = calculate(s1,s2);
    int mx = max(s1.length(), s2.length());
    return 1.0 - (static_cast<double>(d)/mx);
}
