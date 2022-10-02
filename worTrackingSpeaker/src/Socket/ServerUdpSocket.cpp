#include "ServerUdpSocket.hpp"

using namespace worCameraTracking;

ServerUdpSocket::ServerUdpSocket(const std::string &localIp, int16_t localPort_, int bufferLength_)
        : BaseSocket(localIp, localPort_, bufferLength_) {
}

ServerUdpSocket::~ServerUdpSocket() {
    if (_state == SocketState::Connected) {
        closeSocket();
    }
}

bool ServerUdpSocket::openSocket(const std::string &localIp_, int16_t localPort_) {
    if (_state != SocketState::ZeroState) {
        return false;
    }

    _netParameters = NetParameters(localIp_, localPort_);
    sockaddr_in localSockAddr{};
    localSockAddr.sin_family = AF_INET;
    localSockAddr.sin_addr.s_addr = inet_addr(_netParameters._localIp.c_str());
    localSockAddr.sin_port = htons(_netParameters._localPort);

    auto isModuleStartup = WSAStartup(MAKEWORD(2, 2), &_wsaData) == 0;

    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    auto isSocketCreated = _socket != SOCKET_ERROR;

    auto isSocketBind = bind(_socket, (const sockaddr *) &localSockAddr, sizeof(sockaddr_in)) != SOCKET_ERROR;

    /// All action must return true-result
    auto result = isModuleStartup && isSocketCreated && isSocketBind;
    _state = result
            ? SocketState::Connected
            : SocketState::SocketError;
    return result;
}

bool ServerUdpSocket::closeSocket() {
    if (_state != SocketState::Connected) {
        return false;
    }
    auto isSocketClosed = closesocket(_socket) != SOCKET_ERROR;
    auto isModuleCleanup = WSACleanup() != SOCKET_ERROR;
    /// All action must return true-result
    auto result = isSocketClosed && isModuleCleanup;
    _state = result
             ? SocketState::ZeroState
             : SocketState::SocketError;

    return result;
}

void ServerUdpSocket::receivePacket() {
    while (_state == SocketState::Connected) {
        {
            std::lock_guard<std::mutex> lock(_receivingMutex);
            recv(_socket, reinterpret_cast<char *>(_buffer.data()), _bufferLength, 0);
            _dataReceived.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / SOCKET_FPS));
    }
}
