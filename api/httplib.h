#ifndef CPP_HTTPLIB_MINI_H
#define CPP_HTTPLIB_MINI_H

// Cross-platform socket headers & helpers
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
    using socklen_t = int;
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define CLOSE_SOCKET close
#endif

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include <sstream>
#include <cstring>
#include <vector>

namespace httplib {

struct Request {
    std::string method;
    std::string path;
    std::string body;
};

struct Response {
    int status = 200;
    std::string body;
    std::string content_type = "text/plain";
    void set_content(const std::string &b, const std::string &type) {
        body = b;
        content_type = type;
    }
};

class Server {
public:
    using Handler = std::function<void(const Request &, Response &)>;

    Server() : running(false) {}
    ~Server() { stop(); }

    void Get(const std::string &path, Handler handler) { get_handlers[path] = handler; }
    void Post(const std::string &path, Handler handler) { post_handlers[path] = handler; }

    bool listen(const std::string &host, int port) {
        if (running) return false;
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed\n";
            return false;
        }
#endif
        server_fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            std::cerr << "Socket creation failed\n";
#ifdef _WIN32
            WSACleanup();
#endif
            return false;
        }

        int opt = 1;
#ifdef _WIN32
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(static_cast<uint16_t>(port));

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            std::cer
