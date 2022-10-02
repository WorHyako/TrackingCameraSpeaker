#ifndef TRACKINGCAMERASPEAKER_SERVERDEPENDENCIES_H
#define TRACKINGCAMERASPEAKER_SERVERDEPENDENCIES_H

#include <string>

namespace worCameraTracking {

    struct NetParameters {
        NetParameters();

        NetParameters(const std::string &localIp_, int16_t localPort_,
                      const std::string &destinationIp_ = "", int16_t destinationPort_ = -1);

        std::string _localIp;
        std::string _destinationIp;
        int16_t _localPort;
        int16_t _destinationPort;
    };

    enum class SocketState {
        ZeroState,
        Connected,
        SocketError
    };
}

#endif
