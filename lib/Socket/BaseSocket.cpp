#include "BaseSocket.h"

#include <iphlpapi.h>
#include <icmpapi.h>

//#pragma comment(lib, "iphlpapi.lib") // for Visual Studio

namespace worLib {

    NetParameters::NetParameters() {
        local_ip_ = "";
        local_port_ = -1;
        destination_ip_ = "";
        destination_port_ = -1;
    }

    NetParameters::NetParameters(const std::string &local_ip, const int16_t &local_port) {
        local_ip_ = local_ip;
        local_port_ = local_port;
        destination_ip_ = "";
        destination_port_ = -1;
    }

    NetParameters::NetParameters(const std::string &local_ip, const int16_t &local_port,
                                 const std::string &destination_ip, const int16_t &destination_port) {
        local_ip_ = local_ip;
        local_port_ = local_port;
        destination_ip_ = destination_ip;
        destination_port_ = destination_port;
    }

    BaseSocket::BaseSocket(int buffer_length) {
        activity_ = false;
        buffer_length_ = buffer_length;
        buffer_ = new char[buffer_length_];
    }

    BaseSocket::BaseSocket(const std::string &local_ip, const int16_t &local_port, const std::string &destination_ip,
                           const int16_t &destination_port, int buffer_length) {
        net_parameters_.local_ip_ = local_ip;
        net_parameters_.local_port_ = local_port;
        net_parameters_.destination_ip_ = destination_ip;
        net_parameters_.destination_port_ = destination_port;
        buffer_length_ = buffer_length;
        buffer_ = new char[buffer_length_];
        activity_ = false;
    }

    BaseSocket::BaseSocket(const std::string &local_ip, const int16_t &local_port, int buffer_length) {
        net_parameters_.local_ip_ = local_ip;
        net_parameters_.local_port_ = local_port;
        buffer_length_ = buffer_length;
        buffer_ = new char[buffer_length_];
        activity_ = false;
    }

    BaseSocket::~BaseSocket() {
        delete buffer_;
    }

    bool BaseSocket::checkEndPoint(const std::string &destination_ip) {
        HANDLE h_icmp_file;
        unsigned long ipaddr = INADDR_NONE;
        DWORD dw_ret_val = 0;
        char send_data[32] = "Packet to ping";
        LPVOID reply_buffer = nullptr;
        DWORD reply_size = 0;

        ipaddr = inet_addr(destination_ip.c_str());
        if (ipaddr == INADDR_NONE) {
            std::cout << "usage: " << destination_ip.c_str() << " IP address\n";
            return false;
        }

        h_icmp_file = IcmpCreateFile();
        if (h_icmp_file == INVALID_HANDLE_VALUE) {
            std::cout << "\tUnable to open handle.\n";
            std::cout << "IcmpCreatefile returned error: " << GetLastError() << std::endl;
            return false;
        }

        reply_size = sizeof(ICMP_ECHO_REPLY) + sizeof(send_data);
        reply_buffer = (VOID *) malloc(reply_size);
        if (reply_buffer == nullptr) {
            std::cout << "\tUnable to allocate memory\n";
            return false;
        }

        dw_ret_val = IcmpSendEcho(h_icmp_file, ipaddr, send_data, sizeof(send_data), nullptr, reply_buffer, reply_size,
                                  1000);
        if (dw_ret_val) {
            auto pEchoReply = (PICMP_ECHO_REPLY) reply_buffer;
            struct in_addr reply_addr;
            reply_addr.S_un.S_addr = pEchoReply->Address;
            std::cout << "\tSent icmp message to " << destination_ip.c_str() << std::endl;
            if (dw_ret_val > 1) {
                std::cout << "\tReceived " << dw_ret_val << " icmp message responses\n";
                std::cout << "\tInformation from the first response:\n";
            } else {
                std::cout << "\tReceived " << dw_ret_val << " icmp message response\n";
                std::cout << "\tInformation from this response:\n";
            }
            std::cout << "\t  Received from " << inet_ntoa(reply_addr) << std::endl;
            std::cout << "\t  Status = " << pEchoReply->Status << std::endl;
            std::cout << "\t  Roundtrip time = " << pEchoReply->RoundTripTime << " milliseconds\n";
        } else {
            std::cout << "\tCall to IcmpSendEcho failed.\n";
            std::cout << "\tIcmpSendEcho returned error: " << GetLastError() << std::endl;
            return false;
        }
        return true;
    }

    std::array<int, 29> BaseSocket::getDataInIntArray() {
        std::array<int, 29> result{};
        char *ptr_buffer = buffer_;
        for (int16_t i = 0; i < buffer_length_; i++, ptr_buffer++)
            result[i] = static_cast<int>(static_cast<unsigned  char>(*ptr_buffer));

        return result;
    }

    std::vector<byte> BaseSocket::getDataInStlVector() {
        std::vector<byte> result_array;
        char *ptr_buffer = buffer_;
        for (int16_t i = 0; i < buffer_length_; i++, ptr_buffer++)
            result_array.push_back(*ptr_buffer);

        return result_array;
    }

    char *BaseSocket::getDataInCharPtr() const {
        return buffer_;
    }

    NetParameters BaseSocket::getNetParameters() const {
        return net_parameters_;
    }
}