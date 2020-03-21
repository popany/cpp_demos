#include <iostream>
#include <string>
#include "select_client.h"

void Run(std::string serverAddr, int serverPort)
{
    try {
        Socket::Client::StartSelectClient(serverAddr, serverPort);
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::string serverAddr = "127.0.0.1";
    int serverPort = 9999;
    if (argc == 2) {
        serverPort = std::stoi(argv[1]);
    } else if (argc > 2) {
        serverAddr = argv[1];
        serverPort = std::stoi(argv[2]);
    }
    
    Run(serverAddr, serverPort);

    return 0;
}