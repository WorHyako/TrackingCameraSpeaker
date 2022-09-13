#include "BaseSocket.hpp"

#include <iphlpapi.h>
#include <icmpapi.h>

//#pragma comment(lib, "iphlpapi.lib") // for Visual Studio

using namespace worLib;

NetParameters::NetParameters() {
    _localIp = "";
    _localPort = -1;
    _destinationIp = "";
    _destinationPort = -1;
}

NetParameters::NetParameters(const std::string &localIp_, int16_t localPort_,
                             const std::string &destinationIp_, int16_t destinationPort_) {
    _localIp = localIp_;
    _localPort = localPort_;
    _destinationIp = destinationIp_;
    _destinationPort = destinationPort_;
}

BaseSocket::BaseSocket(int bufferLength_) {
    _activity = false;
    _bufferLength = bufferLength_;
    _buffer = new char[_bufferLength];
    _socket = SOCKET_ERROR;
}

BaseSocket::BaseSocket(const std::string &localIp_, int16_t localPort_,
                       const std::string &destinationIp_, int16_t destinationPort_, int bufferLength_)
        : BaseSocket(bufferLength_) {
    _netParameters._localIp = localIp_;
    _netParameters._localPort = localPort_;
    _netParameters._destinationIp = destinationIp_;
    _netParameters._destinationPort = destinationPort_;
}

BaseSocket::BaseSocket(const std::string &localIp_, int16_t localPort_, int bufferLength_)
        : BaseSocket(bufferLength_) {
    _netParameters._localIp = localIp_;
    _netParameters._localPort = localPort_;
}

BaseSocket::~BaseSocket() {
    delete _buffer;
}

bool BaseSocket::checkEndPoint(const std::string &destinationIp_) {
    HANDLE hIcmpFile;
    unsigned long ipAddr = INADDR_NONE;
    DWORD dwRetVal = 0;
    char pingData[32] = "Packet to ping";
    LPVOID replyBuffer = nullptr;
    DWORD replySize = 0;

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
        struct in_addr replyAddr;
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
        std::cout << "\t  Roundtrip time = " << pEchoReply->RoundTripTime << " milliseconds\n";
    } else {
        std::cout << "\tCall to IcmpSendEcho failed.\n";
        std::cout << "\tIcmpSendEcho returned error: " << GetLastError() << std::endl;
        return false;
    }
    return true;
}

std::array<int, 29> BaseSocket::getDataInIntArray() {
    std::array<int, BUFFER_LENGTH> result{};
    char *ptrBuffer = _buffer;
    for (int16_t i = 0; i < _bufferLength; i++, ptrBuffer++) {
        result[i] = static_cast<int>(static_cast<unsigned char>(*ptrBuffer));
    }
    return result;
}

std::vector<byte> BaseSocket::getDataInStlVector() {
    std::vector<byte> resultArray(_bufferLength, '0');
    char *ptr_buffer = _buffer;
    for (int16_t i = 0; i < _bufferLength; i++, ptr_buffer++) {
        resultArray.push_back(*ptr_buffer);
    }
    return resultArray;
}

char *BaseSocket::getDataInCharPtr() const {
    return _buffer;
}

NetParameters BaseSocket::getNetParameters() const {
    return _netParameters;
}
