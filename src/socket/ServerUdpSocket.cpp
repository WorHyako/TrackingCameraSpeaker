#include "socket/ServerUdpSocket.hpp"

using namespace worTCS;

ServerUdpSocket::ServerUdpSocket(const PointInfo &pointInfo_) noexcept
        : BaseSocket(pointInfo_) {
}

ServerUdpSocket::~ServerUdpSocket() {
    /// Yeah, i know that using virtual function in destructor are bad practice
    /// Will fix it in future
    if (_socketInfo.state == SocketState::Connected) {
        closeSocket();
    }
}

bool ServerUdpSocket::openSocket() noexcept {
    if (_socketInfo.state != SocketState::ZeroState) {
        return false;
    }

    sockaddr_in localSockAddr{};
    localSockAddr.sin_family = AF_INET;
    localSockAddr.sin_addr.s_addr = inet_addr(_socketInfo.pointInfo.localIp.c_str());
    localSockAddr.sin_port = htons(_socketInfo.pointInfo.localPort);

    auto isModuleStartup = WSAStartup(MAKEWORD(2, 2), &_socketInfo.wsaData) == 0;

    _socketInfo.socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    auto isSocketCreated = _socketInfo.socketHandle != SOCKET_ERROR;

    auto isSocketBind =
            bind(_socketInfo.socketHandle, (const sockaddr *) &localSockAddr, sizeof(sockaddr_in)) != SOCKET_ERROR;

    /// All action must return true-result
    auto result = isModuleStartup && isSocketCreated && isSocketBind;
    _socketInfo.state = result
                        ? SocketState::Connected
                        : SocketState::SocketError;
    return result;
}

bool ServerUdpSocket::closeSocket() noexcept {
    if (_socketInfo.state != SocketState::Connected) {
        return false;
    }
    auto isSocketClosed = closesocket(_socketInfo.socketHandle) != SOCKET_ERROR;
    auto isModuleCleanup = WSACleanup() != SOCKET_ERROR;
    /// All action must return true-result
    auto result = isSocketClosed && isModuleCleanup;
    _socketInfo.state = result
                        ? SocketState::ZeroState
                        : SocketState::SocketError;
    return result;
}

void ServerUdpSocket::receivePacket() noexcept {
    /// Maybe use it(bytesReceived) in future
    int bytesReceived = -1;
    while (_socketInfo.state == SocketState::Connected) {
        {
            std::lock_guard<std::mutex> lock(_receivingMutex);
            bytesReceived = recv(_socketInfo.socketHandle, reinterpret_cast<char *>(_socketInfo.packet.data()),
                 static_cast<int>(_socketInfo.packet.size()), 0);
            _dataReceived.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / _socketInfo.socketFps));
    }
}
