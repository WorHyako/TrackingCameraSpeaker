#include "ServerUdpSocket.hpp"

using namespace worLib;

ServerUdpSocket::ServerUdpSocket(const std::string &localIp, int16_t localPort_, int bufferLength_)
        : BaseSocket(localIp, localPort_, bufferLength_) {
}

ServerUdpSocket::ServerUdpSocket(const std::string &localIp_, int16_t localPort_,
                                 const std::string &destinationIp_, int16_t destinationPort_,
                                 int bufferLength_)
        : BaseSocket(localIp_, localPort_, destinationIp_, destinationPort_, bufferLength_) {
}

ServerUdpSocket::~ServerUdpSocket() {
    if (_activity) {
        _activity = false;
        closeSocket();
    }
}

bool ServerUdpSocket::openSocket(const std::string &localIp_, int16_t localPort_) {
    _netParameters._localIp = localIp_;
    _netParameters._localPort = localPort_;
    sockaddr_in localSockAddr;
    localSockAddr.sin_family = AF_INET;
    localSockAddr.sin_addr.s_addr = inet_addr(_netParameters._localIp.c_str());
    localSockAddr.sin_port = htons(_netParameters._localPort);

    if (WSAStartup(MAKEWORD(2, 2), &_wsaData)) {
        return false;
    }
    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_socket == SOCKET_ERROR) {
        return false;
    }
    if (bind(_socket, (const sockaddr *) &localSockAddr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        return false;
    }
    _activity = true;
    return true;
}

bool ServerUdpSocket::closeSocket() {
    if (_activity) {
        _activity = false;
        if (closesocket(_socket) == SOCKET_ERROR) {
            return false;
        }
        if (WSACleanup() == SOCKET_ERROR) {
            return false;
        }
    }
    return true;
}

void ServerUdpSocket::startReceivingData() {
    while (_activity) {
        recv(_socket, _buffer, _bufferLength, 0);
        Sleep(1000 / SOCKET_FPS);
    }
}
