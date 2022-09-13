#ifndef TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP
#define TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP

#include "BaseSocket.hpp"

namespace worLib {

    class ServerUdpSocket
            : public BaseSocket {
    public:
        ServerUdpSocket(const std::string &localIp, int16_t localPort_, int bufferLength_ = BUFFER_LENGTH);

        ServerUdpSocket(const std::string &localIp_, int16_t localPort_,
                        const std::string &destinationIp_, int16_t destinationPort_, int bufferLength_ = BUFFER_LENGTH);

        ServerUdpSocket() = default;

        ~ServerUdpSocket() override;

        bool openSocket(const std::string &localIp_, int16_t localPort_) override;

        bool closeSocket() override;

        void startReceivingData();
    };
}
#endif
