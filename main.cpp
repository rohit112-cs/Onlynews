#include <iostream>
#include "modules/trie.cpp"
#include "modules/kmp.cpp"
#include "modules/edit_distance.cpp"
using namespace std;

int main() {
    cout << "=== OnlyNews (Phase 2 Demo) ===\n";

    // Trie test
    Trie trie;
    trie.insert("india wins world cup");
    cout << "Trie search (india wins world cup): " 
         << (trie.search("india wins world cup") ? "Found" : "Not Found") << endl;

    // KMP test
    string text = "breaking news india wins world cup";
    string pattern = "india";
    cout << "KMP match result: " << (kmpSearch(text, pattern) ? "Match Found" : "No Match") << endl;

    // Edit Distance test
    string a = "india wins world cup";
    string b = "india wins word cup";
    cout << "Edit Distance: " << editDistance(a, b) << endl;

    cout << "\n(Integration + CLI will be added in next phase.)\n";
    return 0;
}