#ifndef TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP
#define TRACKINGCAMERASPEAKER_SERVERUDPSOCKET_HPP

#include "BaseSocket.hpp"

namespace worCameraTracking {

    /**
     * Class providing UDP socket management
     */
    class ServerUdpSocket
            : public BaseSocket {
    public:
        ServerUdpSocket(const std::string &localIp, int16_t localPort_, int bufferLength_ = BUFFER_LENGTH);

        ServerUdpSocket() = default;

        ~ServerUdpSocket() override;

        /**
         * Start WinAPI module, connect and bind socket
         * Change @b'_state' to Connected if successful
         * @param localIp_ local ip to listen
         * @param localPort_ local port to listen
         * @return Success open socket
         */
        bool openSocket(const std::string &localIp_, int16_t localPort_) override;

        /**
         * Close socket and clean up WinAPI module
         * Change @b'_state' to ZeroState if successful
         * @return Success close socket
         */
        bool closeSocket() override;

        /**
         * Get data from port to @b'_buffer' and notify all @b'_dataReceived' condition_variable
         * Recommended to run in other thread/task
         */
        void receivePacket();

    public:
#pragma region Accessors

#pragma endregion Accessors

#pragma region Mutators

#pragma endregion Mutators
    };
}
#endif
