#ifndef TRACKINGCAMERASPEAKER_SERVERDEPENDENCIES_H
#define TRACKINGCAMERASPEAKER_SERVERDEPENDENCIES_H

#include <string>

namespace worCameraTracking {

    /**
     * Store net data in comfort way
     */
    struct NetParameters {
        NetParameters();

        NetParameters(const std::string &localIp_, int16_t localPort_,
                      const std::string &destinationIp_ = "", int16_t destinationPort_ = -1);

        std::string _localIp;
        std::string _destinationIp;
        int16_t _localPort;
        int16_t _destinationPort;
    };

    /**
     * Server's socket state
     */
    enum class SocketState {
        /// Socket ready to connect
        ZeroState,
        /// Socket connected and active
        Connected,
        /// Socket or WinAPI error occurred
        SocketError
    };
}

#endif
