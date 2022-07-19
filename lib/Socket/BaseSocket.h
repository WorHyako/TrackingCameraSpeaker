#ifndef TRACKINGCAMERASPEAKER_BASESOCKET_H
#define TRACKINGCAMERASPEAKER_BASESOCKET_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <winsock2.h>

//#pragma comment(lib, "wsock32.lib") // for Visual Studio

namespace worLib {

    const int SOCKET_FPS = 100;
    const int BUFFER_LENGTH = 29;

    struct NetParameters {
        NetParameters();

        NetParameters(const std::string &local_ip, const int16_t &local_port,
                      const std::string &destination_ip, const int16_t &destination_port);

        NetParameters(const std::string &local_ip, const int16_t &local_port);

        std::string local_ip_;
        std::string destination_ip_;
        int16_t local_port_;
        int16_t destination_port_;
    };

    class BaseSocket {
    public:
        explicit BaseSocket(const std::string &local_ip, const int16_t &local_port, int buffer_length = BUFFER_LENGTH);

        explicit BaseSocket(const std::string &local_ip, const int16_t &local_port, const std::string &destination_ip,
                            const int16_t &destination_port, int buffer_length = BUFFER_LENGTH);

        explicit BaseSocket(int buffer_length = BUFFER_LENGTH);

        virtual ~BaseSocket();

        bool activity_;

    protected:
        WSADATA wsadata_ = WSADATA();
        SOCKET socket_ = SOCKET_ERROR;
        NetParameters net_parameters_;

        char *buffer_;
        int buffer_length_;

        virtual bool openSocket(const std::string& local_ip, int16_t local_port) = 0;

        virtual bool closeSocket() = 0;

    public:
        NetParameters getNetParameters() const;

        static bool checkEndPoint(const std::string &destination_ip);

        char *getDataInCharPtr() const;

        std::array<int, BUFFER_LENGTH> getDataInIntArray();

        std::vector<byte> getDataInStlVector();
    };
}
#endif
