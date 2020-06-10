#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <iostream>

struct Session
{
    boost::asio::ip::tcp::socket sock;
    boost::asio::ip::tcp::endpoint endPoint;
    boost::system::error_code errorCode;
    uint64_t id;

    Session(boost::asio::io_service& ios,
        std::string ip,
        uint16_t port,
        uint64_t sessionId) :
        sock(ios),
        endPoint(boost::asio::ip::address::from_string(ip), port),
        id(sessionId)
    {}
};

typedef std::function<void(std::shared_ptr<Session>, const boost::system::error_code&)> ConnectCallBack;

class AsyncTcpClient
{
    std::map<uint32_t, std::shared_ptr<Session>> sessions;
    boost::asio::io_service ios;
    uint64_t nextSessionId;
    std::mutex sessionsGuard;
    std::condition_variable sessionsCanAdd;
    uint32_t maxSessionCount;
    std::unique_ptr<boost::asio::io_service::work> work;
    std::unique_ptr<std::thread> thread;

    std::shared_ptr<Session> CreateSession(std::string ip, uint16_t port)
    {
        uint64_t sessionId = nextSessionId++;
        std::shared_ptr<Session> session = std::make_shared<Session>(ios, ip, port, sessionId);
        session->sock.open(session->endPoint.protocol());

        std::unique_lock<std::mutex> lock(sessionsGuard);
        while (sessions.size() >= maxSessionCount) {
            sessionsCanAdd.wait(lock);
        }

        sessions[sessionId] = session;
        return session;
    }

public:
    AsyncTcpClient(uint32_t maxSessionCount) :
        nextSessionId(0), maxSessionCount(maxSessionCount)
    {
        work.reset(new boost::asio::io_service::work(ios));
        thread.reset(new std::thread([this] () {
            ios.run();
        }));
    }

    void Connect(std::string ip, uint16_t port, ConnectCallBack connectCallBack)
    {
        std::shared_ptr<Session> session = CreateSession(ip, port);
        session->sock.async_connect(session->endPoint, std::bind(connectCallBack, session, std::placeholders::_1));
    }

    void CloseSession(std::shared_ptr<Session> session)
    {
        session->sock.close();
        std::unique_lock<std::mutex> lock(sessionsGuard);
        sessions.erase(sessions.find(session->id));
        sessionsCanAdd.notify_one();
    }

    void Close()
    {
        work.reset(nullptr);
        thread->join();
    }
};

class TcpPortScanner
{
    std::vector<uint16_t> portsToScan;
    std::vector<uint16_t> portsScanned;
    uint32_t maxSessionCount;
    std::mutex portsScannedGuard;

    void ResetPortsToScan(uint32_t portFrom, uint32_t portTo)
    {
        portsToScan.clear();
        for (uint32_t i = portFrom; i <= portTo; ++i) {
            portsToScan.push_back((uint16_t)i);
        }
    }

public:
    TcpPortScanner(uint32_t maxSessionCount) : maxSessionCount(maxSessionCount)
    {}

    void Scan(std::string ip, uint16_t portFrom, uint16_t portTo, bool isDebug)
    {
        ResetPortsToScan(portFrom, portTo);
        std::shared_ptr<AsyncTcpClient> tcpClient = std::make_shared<AsyncTcpClient>(maxSessionCount);

        for (auto port : portsToScan) {
            tcpClient->Connect(ip, port,
                [&] (std::shared_ptr<Session> session, const boost::system::error_code& errorCode) {
                    if (errorCode == boost::system::errc::success) {
                        std::unique_lock<std::mutex> lock(portsScannedGuard);
                        portsScanned.push_back(session->endPoint.port());
                    }
                    if (isDebug) {
						std::cout << "port: " << session->endPoint.port() << "\n";
                    }
                    tcpClient->CloseSession(session);
                }
            );
        }
        tcpClient->Close();
    }

    void PrintPortsScanned()
    {
        for (auto port : portsScanned) {
            std::cout << port << "\n";
        }
        std::cout << std::endl;
    }
};

std::map<std::string, std::string> GetParams(int argc, char* argv[])
{
    const std::string defaultSessionCount = "100";
    const std::string defaultIp = "127.0.0.1";
    const std::string defaultFromPort = "0";
    const std::string defaultToPort = "65535";
    const std::string defaultIsDebug = "false";

    std::map<std::string, std::string> params;
    params["sessionCount"] = defaultSessionCount;
    params["ip"] = defaultIp;
    params["fromPort"] = defaultFromPort;
    params["toPort"] = defaultToPort;
    params["isDebug"] = "false";

    for (int i = 1; i < argc;) {
        if (std::string(argv[i]) == "-f") {
            params["fromPort"] = argv[i + 1];
            i += 2;
            continue;
        }
        else if (std::string(argv[i]) == "-t") {
            params["toPort"] = argv[i + 1];
            i += 2;
            continue;
        }
        else if (std::string(argv[i]) == "-c") {
            params["sessionCount"] = argv[i + 1];
            i += 2;
            continue;
        }
        else if (std::string(argv[i]) == "-d") {
            params["isDebug"] = "true";
            i++;
        }
        else {
            params["ip"] = argv[i];
            i++;
        }
    }

    std::cout << "ip: " << params["ip"] << "\n";
    std::cout << "fromPort: " << params["fromPort"] << "\n";
    std::cout << "toPort: " << params["toPort"] << "\n";
    std::cout << "sessionCount: " << params["sessionCount"] << std::endl;
    std::cout << "isDebug: " << params["isDebug"] << std::endl;

    return params;
}

int main(int argc, char* argv[])
{
    try {
        std::map<std::string, std::string> params = GetParams(argc, argv);
        uint32_t sessionCount = std::stoul(params["sessionCount"]);
        std::string ip = params["ip"];
        uint32_t fromPort = std::stoul(params["fromPort"]);
        uint32_t toPort = std::stoul(params["toPort"]);
        bool isDebug = params["isDebug"] == "true";

        TcpPortScanner portScanner(sessionCount);

        portScanner.Scan(ip, fromPort, toPort, isDebug);

        portScanner.PrintPortsScanned();
    } catch (const std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    return 0;
}
