#ifndef TRACKINGCAMERASPEAKER_SERVERDEPENDENCIES_HPP
#define TRACKINGCAMERASPEAKER_SERVERDEPENDENCIES_HPP

#include <string>

namespace worTCS {

    /**
     * Store net data in comfort way
     */
    struct PointInfo {
        PointInfo() noexcept;

        PointInfo(const std::string &localIp_, int16_t localPort_,
                  const std::string &destinationIp_ = "", int16_t destinationPort_ = -1) noexcept;

        std::string localIp;
        std::string destinationIp;
        int16_t localPort;
        int16_t destinationPort;
    };

    /**
     * Server's socket state
     */
    enum class SocketState {
        /// socket ready to connect
        ZeroState,
        /// socket connected and active
        Connected,
        /// socket or WinAPI error occurred
        SocketError
    };
}

#endif
