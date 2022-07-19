#include "ServerUdpSocket.h"

namespace worLib {

    ServerUdpSocket::ServerUdpSocket(const std::string &local_ip, const int16_t &local_port, int buffer_length)
            : BaseSocket(local_ip, local_port, buffer_length) {
    }

    ServerUdpSocket::ServerUdpSocket(const std::string &local_ip, const int16_t &local_port,
                                     const std::string &destination_ip, const int16_t &destination_port,
                                     int buffer_length)
            : BaseSocket(local_ip, local_port, destination_ip, destination_port, buffer_length) {
    }

    ServerUdpSocket::~ServerUdpSocket() {
        if (activity_) {
            activity_ = false;
            closeSocket();
        }
    }

    bool ServerUdpSocket::openSocket(const std::string &local_ip, int16_t local_port) {
        net_parameters_.local_ip_ = local_ip;
        net_parameters_.local_port_ = local_port;
        sockaddr_in local_sockaddr;
        local_sockaddr.sin_family = AF_INET;
        local_sockaddr.sin_addr.s_addr = inet_addr(net_parameters_.local_ip_.c_str());
        local_sockaddr.sin_port = htons(net_parameters_.local_port_);

        if (WSAStartup(MAKEWORD(2, 2), &wsadata_))
            return false;

        socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (socket_ == SOCKET_ERROR)
            return false;

        if (bind(socket_, (const sockaddr *) &local_sockaddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
            return false;

        activity_ = true;
        return true;
    }

    bool ServerUdpSocket::closeSocket() {
        if (activity_) {
            activity_ = false;
            if (closesocket(socket_) == SOCKET_ERROR)
                return false;

            if (WSACleanup() == SOCKET_ERROR)
                return false;
        }
        return true;
    }

    void ServerUdpSocket::startReceivingData() {
        while (activity_) {
            recv(socket_, buffer_, buffer_length_, 0);
            Sleep(1000 / SOCKET_FPS);
        }
    }
}