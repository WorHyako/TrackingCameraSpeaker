#ifndef TRACKINGCAMERASPEAKER_BASESOCKET_HPP
#define TRACKINGCAMERASPEAKER_BASESOCKET_HPP

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <winsock2.h>

//#pragma comment(lib, "wsock32.lib") // for Visual Studio

namespace worLib {

    const int SOCKET_FPS = 100;
    constexpr int BUFFER_LENGTH = 29;

    struct NetParameters {
        NetParameters();

        NetParameters(const std::string &localIp_, int16_t localPort_,
                      const std::string &destinationIp_ = "", int16_t destinationPort_ = -1);

        std::string _localIp;
        std::string _destinationIp;
        int16_t _localPort;
        int16_t _destinationPort;
    };

    class BaseSocket {
    public:
        BaseSocket(const std::string &localIp_, int16_t localPort_, int bufferLength_ = BUFFER_LENGTH);

        BaseSocket(const std::string &localIp_, int16_t localPort_,
                   const std::string &destinationIp_, int16_t destinationPort_, int bufferLength_ = BUFFER_LENGTH);

        explicit BaseSocket(int bufferLength_ = BUFFER_LENGTH);

        virtual ~BaseSocket();

        bool _activity;

    protected:
        WSADATA _wsaData;
        SOCKET _socket;
        NetParameters _netParameters;

        char *_buffer;
        int _bufferLength;

        virtual bool openSocket(const std::string &local_ip, int16_t local_port) = 0;

        virtual bool closeSocket() = 0;

    public:
        NetParameters getNetParameters() const;

        static bool checkEndPoint(const std::string &destinationIp_);

        char *getDataInCharPtr() const;

        std::array<int, BUFFER_LENGTH> getDataInIntArray();

        std::vector<byte> getDataInStlVector();
    };
}
#endif
