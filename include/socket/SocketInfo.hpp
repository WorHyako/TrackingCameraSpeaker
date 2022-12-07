#ifndef TRACKINGCAMERASPEAKER_SOCKETINFO_HPP
#define TRACKINGCAMERASPEAKER_SOCKETINFO_HPP

#include "socket/ServerDependencies.hpp"

#include <cstddef>
#include <vector>
#include <winsock2.h>

namespace worTCS {

    struct SocketInfo {
        SocketInfo();

        static constexpr int default_buffer_length = 256;

        SocketState state;

        WSADATA wsaData;

        SOCKET socketHandle;

        PointInfo pointInfo;

        /// Server tick rate
        int socketFps;

        std::vector<std::byte> packet;
    };
}
#endif
