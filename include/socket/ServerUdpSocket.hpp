#ifndef TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP
#define TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP

#include "socket/BaseSocket.hpp"

namespace worTCS {

    /**
     * Class providing UDP socket management
     */
    class ServerUdpSocket final
            : public BaseSocket {
    public:
        explicit ServerUdpSocket(const PointInfo& pointInfo_ = PointInfo()) noexcept;

        ~ServerUdpSocket() final;

        /**
         * Start WinAPI module, connect and bind socket
         * Change @b'state' to Connected if successful
         * @param localIp_ local ip to listen
         * @param localPort_ local port to listen
         * @return Success open socket
         */
        [[nodiscard]] bool openSocket() noexcept final;

        /**
         * Close socket and clean up WinAPI module
         * Change @b'state' to ZeroState if successful
         * @return Success close socket
         */
        [[nodiscard]] bool closeSocket() noexcept final;

        /**
         * Get data from port to @b'packet' and notify all @b'_dataReceived' condition_variable
         * Recommended to run in other thread/task
         */
        void receivePacket() noexcept;
    };
}
#endif
