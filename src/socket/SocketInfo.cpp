#include "socket/SocketInfo.hpp"

using namespace worTCS;

SocketInfo::SocketInfo()
        : wsaData(WSAData()) {
    state = SocketState::ZeroState;
    packet.resize(default_buffer_length);
    socketHandle = SOCKET_ERROR;
    socketFps = 100;
}
