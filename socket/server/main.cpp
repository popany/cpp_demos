#include <iostream>
#include "iterative_server.h"
#include <exception>

void Run(int port)
{
    try {
        Socket::Server::StartIterativeServer(port);
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    try {
        int port = 9999;
        if (argc > 1) {
            port = std::stoi(argv[1]);
        }
        Run(port);
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
