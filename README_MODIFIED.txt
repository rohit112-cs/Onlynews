OnlyNews - Modified Package

What I changed:
- Added cross-platform api/httplib.h (mini server with header parsing).
- Replaced api/OnlyNewsAPI.cpp to:
  - Return JSON responses.
  - Require ONLYNEWS_API_KEY via x-api-key header.
  - Provide /analyze, /load_csv, /stats, and /forward_article endpoints.
- Added fetch_and_forward.py script to fetch from NewsAPI.org and forward headlines to /forward_article.
- Updated CMakeLists.txt to build onlynews and onlynews_api (links ws2_32 on Windows).

How to run (CLI only):
- Build as before (see CMakeLists).
- To run CLI: ./onlynews

How to run API:
- Set environment variable ONLYNEWS_API_KEY (recommended) and optionally NEWS_API_KEY for fetch script.
  Example (Linux/macOS):
    export ONLYNEWS_API_KEY="your_key_here"
    export NEWS_API_KEY="your_newsapi_key"
    export ONLYNEWS_URL="http://localhost:8080/forward_article"

- Build and run API:
    mkdir -p build
    cd build
    cmake ..
    cmake --build .
    # Run API executable (or use onlynews_api)
    ./onlynews_api

- Use fetcher (Python) to fetch and forward headlines (requires requests):
    pip install requests
    python3 fetch_and_forward.py

API Endpoints:
- POST /analyze           (header x-api-key) body = raw headline -> JSON {"headline":"...","result":"Trusted"}
- POST /forward_article   (header x-api-key) body = raw headline -> JSON
- POST /load_csv          (header x-api-key) body = path to CSV to load dataset
- GET  /stats             (header x-api-key) -> JSON {"total": N}

Security:
- Do NOT commit your keys. Use environment variables.
- If you exposed the API key earlier, rotate it.

If you want, I can:
- Add proper HTTPS client fetching in C++ (requires OpenSSL and more changes), or
- Convert fetcher to run as a background service, or
- Zip and provide this modified project for download.

