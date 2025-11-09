OnlyNews - No Python version

This package is a C++ only version of the OnlyNews project.
It does NOT include any Python fetcher or scripts.

Contents:
- include/: project headers
- src/: project C++ source files
- api/: api server (OnlyNewsAPI.cpp) and httplib.h (mini header-only server)
- CMakeLists.txt

How to build:
mkdir -p build
cd build
cmake ..
cmake --build .

Run API:
# set ONLYNEWS_API_KEY in environment before running for endpoints requiring key
export ONLYNEWS_API_KEY="your_key_here"
./onlynews_api

Notes:
- External news fetching is expected to be done by external systems that POST to /forward_article.
- No Python tools included per request.

