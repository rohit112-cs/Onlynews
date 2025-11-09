#include "httplib.h"
#include "../include/DatasetManager.h"
#include "../include/NewsDetector.h"
#include <string>
#include <iostream>

using namespace httplib;
using namespace std;

int main() {
    DatasetManager dataset;
    NewsDetector detector;
    // initialize with samples
    vector<string> trusted = {"Scientists discover new renewable energy source"};
    vector<string> fake = {"Alien invasion confirmed by government sources"};
    dataset.addTrustedHeadlines(trusted);
    dataset.addFakeHeadlines(fake);
    detector.initialize(dataset);

    Server svr;

    svr.Post("/analyze", [&](const Request& req, Response& res) {
        auto body = req.body;
        if (body.empty()) { res.status = 400; res.set_content("headline missing", "text/plain"); return; }
        string result = detector.classifyHeadline(body);
        res.set_content(result, "text/plain");
    });

    svr.Post("/load_csv", [&](const Request& req, Response& res) {
        auto filename = req.body;
        if (filename.empty()) { res.status = 400; res.set_content("filename missing", "text/plain"); return; }
        if (dataset.loadFromCSV(filename)) {
            detector.initialize(dataset);
            res.set_content("loaded", "text/plain");
        } else {
            res.status = 500; res.set_content("failed to load", "text/plain");
        }
    });

    svr.Get("/stats", [&](const Request& req, Response& res) {
        // simple text response (could convert to JSON if desired)
        std::ostringstream oss;
        const auto& data = dataset.getDataset();
        oss << "total:" << data.size();
        res.set_content(oss.str(), "text/plain");
    });

    cout << "API server running at http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    return 0;
}
