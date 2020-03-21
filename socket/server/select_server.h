#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdexcept>
#include <vector>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iomanip>

namespace Socket
{
    namespace Server
    {
        // https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rzab6/xnonblock.htm
        void StartSelectServer(int port)
        {
            const int listenBackLog = 50;
            const size_t bufferSize = 1 << 16;

            sockaddr_in servaddr;
            memset(&servaddr, 0, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            servaddr.sin_port = htons(port); 

            int listenFd = socket(AF_INET, SOCK_STREAM, 0);
            if (listenFd == -1) {
                throw std::runtime_error("[StartIterativeServer] socket() failed");
            }

            int on = 1;
            if (ioctl(listen_sd, FIONBIO, (char *)&on) < 0) {
                throw std::runtime_error("[StartIterativeServer] ioctl() failed");
            }

            if (bind(listenFd, (sockaddr*) &servaddr, sizeof(servaddr)) != 0) {
                throw std::runtime_error("[StartIterativeServer] bind() failed");
            }

            if (listen(listenFd, listenBackLog) != 0) {
                throw std::runtime_error("[StartIterativeServer] listen() failed");
            }

            fd_set fdSet;
            FD_ZERO(&fdSet);
            int maxFd = listenFd;
            FD_SET(listenFd, &fdSet);

            while (true) {
                int connfd = accept(listenFd, nullptr, nullptr);
                if (connfd == -1) {
                    throw std::runtime_error("[StartIterativeServer] accept() failed");
                }

                std::vector<char> buffer = std::vector<char>(bufferSize, 0);
                for (int i = 0; ; ++i) {
                    ssize_t r = read(connfd, &buffer[0], buffer.size());           
                    if (r > 0) {
                        std::stringstream stream;
                        stream << "<" << i << ">";
                        for (ssize_t j = 0; j < r; j++) {
                            stream << "[0x" << std::setfill ('0') << std::setw(2) << std::hex << (int)buffer[j] << "]";
                        }
                        std::string s = stream.str();
                        write(connfd, &s[0], s.size());
                        continue;
                    } else if (r == 0) {
                        break;
                    } else {
                        throw std::runtime_error("[StartIterativeServer] accept() failed");
                    }
                }
            }
        }
    }
}
