#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string.h>

namespace Socket
{
    namespace Client
    {
        void StartSelectClient(std::string serverAddr, int serverPort)
        {
            const size_t recvBufSize = 1 << 16;
            const size_t sendBufSize = 1 << 16;
            int sockFd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockFd == -1) {
                throw std::runtime_error("[StartSelectClient] socket() failed");
            }

            sockaddr_in servaddr;
            memset(&servaddr, 0, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(serverPort); 
            if (inet_pton(AF_INET, &serverAddr[0], &servaddr.sin_addr) <= 0) {
                throw std::runtime_error("[StartSelectClient] inet_pton() failed");
            }

            if (connect(sockFd, (sockaddr*) &servaddr, sizeof(servaddr)) != 0) {
                throw std::runtime_error("[StartSelectClient] connect() failed");
            }

            fd_set rset;
            FD_ZERO(&rset);

            std::vector<char> recvBuf(recvBufSize, 0);
            std::vector<char> sendBuf(sendBufSize, 0);
            while (true) {
                FD_SET(fileno(stdin), &rset);
                FD_SET(sockFd, &rset);
                int maxFd = std::max(sockFd, fileno(stdin));
                if (select(maxFd + 1,  &rset,  NULL,  NULL,  NULL) <= 0) {
                    throw std::runtime_error("[StartSelectClient] select() failed");
                }

                if (FD_ISSET(sockFd,  &rset)) {
                    ssize_t r = read(sockFd, &recvBuf[0], recvBuf.size());           
                    if (r > 0) {
                        std::cout << "Read: " << "\"" << std::string(&recvBuf[0], r) << "\"" << std::endl;
                    } else if (r == 0) {
                        std::cout << "[StartSelectClient] connection closed" << std::endl;
                    } else {
                        throw std::runtime_error("[StartSelectClient] sockFd read error");
                    }
                }

                if (FD_ISSET(fileno(stdin), &rset)) {
                    const char* s = fgets(&sendBuf[0], sendBuf.size(), stdin);
                    if (s == nullptr) {
                        std::cout << "[StartSelectClient] endof file" << std::endl;
                    }
                    std::string line(s);
                    while (line.back() != '\n') {
                        s = fgets(&sendBuf[0], sendBuf.size(), stdin);
                        if (s == nullptr) {
                            break;
                        }
                        line.append(s);
                    }
                    if (line.back() == '\n') {
                        line.pop_back();
                    }
                    
                    std::cout << "send: " << line.size() << "byte" << std::endl;
                    write(sockFd, &line[0], line.size());
                }
            }
        }
    }
}
