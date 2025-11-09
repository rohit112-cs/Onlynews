#include "DatasetManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

bool DatasetManager::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cerr << "Error: Could not open file " << filename << endl; return false; }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string headline, category;
        if (getline(ss, headline, ',') && getline(ss, category, ',')) {
            if (!headline.empty() && headline.front()=='"') headline = headline.substr(1, headline.length()-2);
            if (!category.empty() && category.front()=='"') category = category.substr(1, category.length()-2);
            string normalized = normalizer.normalizeText(headline);
            dataset.push_back({normalized, category});
        }
    }
    file.close();
    cout << "Loaded " << dataset.size() << " news items from " << filename << endl;
    return true;
}

void DatasetManager::addTrustedHeadlines(const vector<string>& headlines) {
    for (const auto& h : headlines) dataset.push_back({normalizer.normalizeText(h), "trusted"});
}

void DatasetManager::addFakeHeadlines(const vector<string>& headlines) {
    for (const auto& h : headlines) dataset.push_back({normalizer.normalizeText(h), "fake"});
}

const vector<NewsItem>& DatasetManager::getDataset() const { return dataset; }

vector<string> DatasetManager::getHeadlinesByCategory(const string& category) const {
    vector<string> res;
    for (const auto& it : dataset) if (it.category == category) res.push_back(it.headline);
    return res;
}

void DatasetManager::displayStats() const {
    unordered_map<string,int> count;
    for (const auto& it : dataset) count[it.category]++;
    cout << "\nDataset Statistics:\nTotal headlines: " << dataset.size() << endl;
    for (const auto& p : count) cout << p.first << ": " << p.second << " headlines\n";
}
