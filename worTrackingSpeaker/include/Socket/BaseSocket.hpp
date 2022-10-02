#ifndef TRACKINGCAMERASPEAKER_BASESOCKET_HPP
#define TRACKINGCAMERASPEAKER_BASESOCKET_HPP

#include "ServerDependencies.hpp"

#include <array>
#include <vector>
#include <mutex>
#include <condition_variable>

#include <winsock2.h>

//#pragma comment(lib, "wsock32.lib") // for Visual Studio

namespace worCameraTracking {
    /// Server tick rate
    extern int SOCKET_FPS;

    /// Server's receiving buffer
    extern int BUFFER_LENGTH;

    /**
     * Base abstract class to socket management
     * Provide mutex @b'_receivingMutex' and condition_variable @b'_dataReceived', base WinAPI fields to create
     * UDP or TCP full management classes
     */
    class BaseSocket {
    public:
        /// Condition variable in charge of @b'_buffer'. Notify then data received
        std::condition_variable _dataReceived;
        /// Mutex in charge of @b'_buffer'. Locked while the data is receiving
        std::mutex _receivingMutex;

    protected:
        SocketState _state;
        WSADATA _wsaData;
        SOCKET _socket;
        NetParameters _netParameters;

        std::vector<byte> _buffer;
        int _bufferLength;

    public:
        BaseSocket(const std::string &localIp_, int16_t localPort_, int bufferLength_ = BUFFER_LENGTH);

        BaseSocket(const std::string &localIp_, int16_t localPort_,
                   const std::string &destinationIp_, int16_t destinationPort_, int bufferLength_ = BUFFER_LENGTH);

        virtual ~BaseSocket() = default;

        explicit BaseSocket(int bufferLength_ = BUFFER_LENGTH);

        virtual bool openSocket(const std::string &local_ip, int16_t local_port) = 0;

        virtual bool closeSocket() = 0;

        /**
         * Check connection to destination IP
         * @param destinationIp_ destination IP to ping
         * @return successful connection
         */
        static bool checkEndPoint(const std::string &destinationIp_);

    public:
#pragma region Accessors

        NetParameters getNetParameters() const;

        const std::vector<byte> &getBuffer() const;

        SocketState getSocketState() const;

#pragma endregion Accessors

#pragma region Mutators

#pragma endregion Mutators
    };
}
#endif
