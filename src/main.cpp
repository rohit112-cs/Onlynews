#include <iostream>
#include "DatasetManager.h"
#include "NewsDetector.h"

using namespace std;

void displayMenu() {
    cout << "\n=== Only News - Fake News Detection System ===\n";
    cout << "1. Analyze a headline\n2. Load dataset from CSV\n3. Add sample headlines\n4. Display dataset statistics\n5. Configure thresholds\n6. Exit\nChoose an option: ";
}

void addSampleHeadlines(DatasetManager& dataset) {
    vector<string> trusted = {
        "Scientists discover new renewable energy source",
        "Global literacy rates continue to rise",
        "New vaccine shows promising results in clinical trials"
    };
    vector<string> fake = {
        "Alien invasion confirmed by government sources",
        "Celebrity death hoax spreads on social media",
        "Miracle cure discovered in remote village"
    };
    dataset.addTrustedHeadlines(trusted);
    dataset.addFakeHeadlines(fake);
    cout << "Added " << trusted.size() << " trusted and " << fake.size() << " fake sample headlines.\n";
}

int main() {
    cout << "Only News - Fake News Detection\n";
    DatasetManager dataset;
    NewsDetector detector;
    addSampleHeadlines(dataset);
    detector.initialize(dataset);
    const string NEWS_API_KEY = "b1f4007aa8d917e8fbefe53ecfdfe54b";

    int choice;
    string input;
    do {
        displayMenu();
        if (!(cin >> choice)) break;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter headline to analyze: ";
                getline(cin,input);
                if (!input.empty()) detector.analyzeHeadline(input);
                break;
            case 2:
                cout << "Enter CSV filename: ";
                getline(cin,input);
                if (!input.empty()) { if (dataset.loadFromCSV(input)) detector.initialize(dataset); }
                break;
            case 3:
                addSampleHeadlines(dataset);
                detector.initialize(dataset);
                break;
            case 4:
                dataset.displayStats(); break;
            case 5: {
                double s,p; cout << "Enter similarity (0-1): "; cin >> s; cout << "Enter pattern (0-1): "; cin >> p;
                detector.setThresholds(s,p); cin.ignore();
                cout << "Thresholds updated\n"; break;
            }
            case 6:
                cout << "Exiting\n"; break;
            default:
                cout << "Invalid option\n";
        }
    } while (choice != 6);
    return 0;
}
