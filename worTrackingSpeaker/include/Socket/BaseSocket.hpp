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

    extern int SOCKET_FPS;

    extern int BUFFER_LENGTH;

    class BaseSocket {
    public:
        std::condition_variable _dataReceived;
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
