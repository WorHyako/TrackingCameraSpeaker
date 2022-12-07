#include "socket/BaseSocket.hpp"

#include <iphlpapi.h>
#include <icmpapi.h>

using namespace worTCS;

BaseSocket::BaseSocket(const PointInfo &pointInfo_) noexcept {
    _socketInfo.pointInfo = pointInfo_;
}

bool BaseSocket::checkEndPoint(const std::string &destinationIp_) noexcept {
    HANDLE hIcmpFile;
    unsigned long ipAddr = INADDR_NONE;
    DWORD dwRetVal;
    char pingData[32] = "Packet to ping";
    LPVOID replyBuffer;
    DWORD replySize;

    ipAddr = inet_addr(destinationIp_.c_str());
    if (ipAddr == INADDR_NONE) {
        printf("\nUsage : %s IP address", destinationIp_.c_str());
        return false;
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        printf("\n\tUnable to open handle.");
        printf("\nIcmpCreateFile returned error: %u", static_cast<unsigned>(GetLastError()));
        return false;
    }

    replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(pingData);
    replyBuffer = (void *) malloc(replySize);
    if (replyBuffer == nullptr) {
        printf("\tUnable to allocate memory.\n");
        return false;
    }

    dwRetVal = IcmpSendEcho(hIcmpFile, ipAddr, pingData, sizeof(pingData), nullptr, replyBuffer, replySize, 1000);
    if (dwRetVal) {
        auto pEchoReply = (PICMP_ECHO_REPLY) replyBuffer;
        struct in_addr replyAddr{};
        replyAddr.S_un.S_addr = pEchoReply->Address;
        printf("\nSent icmp message to %s", destinationIp_.c_str());
        if (dwRetVal > 1) {
            printf("\n\tReceived %u icmp message responses", static_cast<unsigned>(dwRetVal));
            printf("\n\tInformation from the first response.");
        }
        printf("\n\t\tReceived from %s", inet_ntoa(replyAddr));
        printf("\n\t\tStatus = %u", static_cast<unsigned>(pEchoReply->Status));
        printf("\n\t\tRoundTrip time = %u milliseconds", static_cast<unsigned>(pEchoReply->RoundTripTime));
    } else {
        printf("\n\tCall to IcmpSendEcho failed.");
        printf("\n\tIcmpSendEcho returned error: %u", static_cast<unsigned>(GetLastError()));
        return false;
    }
    return true;
}

#pragma region Accessors

const std::vector<std::byte> &BaseSocket::getPacket() const noexcept {
    return _socketInfo.packet;
}

const PointInfo& BaseSocket::getPointInfo() const noexcept {
    return _socketInfo.pointInfo;
}

SocketState BaseSocket::getSocketState() const noexcept {
    return _socketInfo.state;
}

int BaseSocket::getSocketFps() const noexcept {
    return _socketInfo.socketFps;
}

#pragma endregion Accessors

#pragma region Mutators

void BaseSocket::setPacketLength(int length_) noexcept {
    if (length_ < 1) {
        length_ = 1;
    }
    _socketInfo.packet.resize(length_);
}

void BaseSocket::setSocketFps(int fps_) noexcept {
    if (fps_ < 1) {
        fps_ = 1;
    }
    _socketInfo.socketFps = fps_;
}

void BaseSocket::setPointInfo(const PointInfo &pointInfo_) noexcept {
    _socketInfo.pointInfo = pointInfo_;
}

#pragma endregion Mutators
