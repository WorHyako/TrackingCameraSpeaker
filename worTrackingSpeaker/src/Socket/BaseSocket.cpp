#include "BaseSocket.hpp"

#include <iostream>
#include <iphlpapi.h>
#include <icmpapi.h>

//#pragma comment(lib, "iphlpapi.lib") // for Visual Studio

using namespace worCameraTracking;

int worCameraTracking::SOCKET_FPS = 100;
int worCameraTracking::BUFFER_LENGTH = 29;

BaseSocket::BaseSocket(int bufferLength_) {
    _state = SocketState::ZeroState;
    _bufferLength = bufferLength_;
    _buffer.resize(_bufferLength);
    _socket = SOCKET_ERROR;
    _wsaData = WSAData();
}

BaseSocket::BaseSocket(const std::string &localIp_, int16_t localPort_,
                       const std::string &destinationIp_, int16_t destinationPort_, int bufferLength_)
        : BaseSocket(bufferLength_) {
    _netParameters = NetParameters(localIp_, localPort_, destinationIp_, destinationPort_);
}

BaseSocket::BaseSocket(const std::string &localIp_, int16_t localPort_, int bufferLength_)
        : BaseSocket(bufferLength_) {
    _netParameters = NetParameters(localIp_, localPort_);
}

bool BaseSocket::checkEndPoint(const std::string &destinationIp_) {
    HANDLE hIcmpFile;
    unsigned long ipAddr = INADDR_NONE;
    DWORD dwRetVal;
    char pingData[32] = "Packet to ping";
    LPVOID replyBuffer;
    DWORD replySize;

    ipAddr = inet_addr(destinationIp_.c_str());
    if (ipAddr == INADDR_NONE) {
        std::cout << "usage: " << destinationIp_.c_str() << " IP address\n";
        return false;
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        std::cout << "\tUnable to open handle.\n";
        std::cout << "IcmpCreatefile returned error: " << GetLastError() << std::endl;
        return false;
    }

    replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(pingData);
    replyBuffer = (void *) malloc(replySize);
    if (replyBuffer == nullptr) {
        std::cout << "\tUnable to allocate memory\n";
        return false;
    }

    dwRetVal = IcmpSendEcho(hIcmpFile, ipAddr, pingData, sizeof(pingData), nullptr, replyBuffer, replySize,
                            1000);
    if (dwRetVal) {
        auto pEchoReply = (PICMP_ECHO_REPLY) replyBuffer;
        struct in_addr replyAddr{};
        replyAddr.S_un.S_addr = pEchoReply->Address;
        std::cout << "\tSent icmp message to " << destinationIp_.c_str() << std::endl;
        if (dwRetVal > 1) {
            std::cout << "\tReceived " << dwRetVal << " icmp message responses\n";
            std::cout << "\tInformation from the first response:\n";
        } else {
            std::cout << "\tReceived " << dwRetVal << " icmp message response\n";
            std::cout << "\tInformation from this response:\n";
        }
        std::cout << "\t  Received from " << inet_ntoa(replyAddr) << std::endl;
        std::cout << "\t  Status = " << pEchoReply->Status << std::endl;
        std::cout << "\t  RoundTrip time = " << pEchoReply->RoundTripTime << " milliseconds\n";
    } else {
        std::cout << "\tCall to IcmpSendEcho failed.\n";
        std::cout << "\tIcmpSendEcho returned error: " << GetLastError() << std::endl;
        return false;
    }
    return true;
}

#pragma region Accessors

const std::vector<byte> &BaseSocket::getBuffer() const {
    return _buffer;
}

NetParameters BaseSocket::getNetParameters() const {
    return _netParameters;
}

SocketState BaseSocket::getSocketState() const {
    return _state;
}

#pragma endregion Accessors

#pragma region Mutators

#pragma endregion Mutators
