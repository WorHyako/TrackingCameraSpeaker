#ifndef TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_H
#define TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_H

#include "BaseSocket.h"

namespace worLib {

    class ServerUdpSocket
            : public BaseSocket {
    public:
        ServerUdpSocket(const std::string &local_ip, const int16_t &local_port, int buffer_length = BUFFER_LENGTH);

        ServerUdpSocket(const std::string &local_ip, const int16_t &local_port, const std::string &destination_ip,
                        const int16_t &destination_port, int buffer_length = BUFFER_LENGTH);

        ServerUdpSocket() = default;

        ~ServerUdpSocket() override;

        bool openSocket(const std::string& local_ip, int16_t local_port) override;

        bool closeSocket() final;

        void startReceivingData();
    };
}
#endif