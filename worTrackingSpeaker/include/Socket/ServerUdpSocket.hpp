#ifndef TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP
#define TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP

#include "BaseSocket.hpp"

namespace worCameraTracking {

    class ServerUdpSocket
            : public BaseSocket {
    public:
        ServerUdpSocket(const std::string &localIp, int16_t localPort_, int bufferLength_ = BUFFER_LENGTH);

        ServerUdpSocket() = default;

        virtual ~ServerUdpSocket();

        bool openSocket(const std::string &localIp_, int16_t localPort_) override;

        bool closeSocket() override;

        void receivePacket();

    public:
#pragma region Accessors

#pragma endregion Accessors

#pragma region Mutators

#pragma endregion Mutators
    };
}
#endif
