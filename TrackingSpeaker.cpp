#include "TrackingSpeaker.h"

namespace worLib {

    TrackingSpeaker::TrackingSpeaker() {
        speaker_activity_ = false;
        receiving_thread_ = nullptr;
        parsing_thread_ = nullptr;
    }

    TrackingSpeaker::~TrackingSpeaker() {
        stopReader();
    }

    bool TrackingSpeaker::startReader(const std::string &local_ip, int16_t local_port) {
        if (!server_.openSocket(local_ip, local_port)) {
            speaker_activity_ = false;
            return false;
        } else
            speaker_activity_ = true;

        receiving_thread_ = new std::thread(&ServerUdpSocket::startReceivingData, server_);
        parsing_thread_ = new std::thread(&TrackingSpeaker::startParse, this);
        return true;
    }

    bool TrackingSpeaker::stopReader() {
        if (speaker_activity_) {
            speaker_activity_ = false;
            receiving_thread_->detach();
            parsing_thread_->detach();
            delete receiving_thread_;
            delete parsing_thread_;
        }
        Sleep(1);
        return server_.closeSocket();
    }

    void TrackingSpeaker::startParse() {
        while (speaker_activity_) {
            std::vector<unsigned char> data_varray = server_.getDataInStlVector();
            if (data_varray.empty()) continue;

            std::array<unsigned char, FREED_PACKET_LENGTH> data_array{};
            std::copy(data_varray.begin(), data_varray.end(), data_array.begin());
            freed_packet_.parseData(data_array);

            Sleep(1);
        }
    }

    std::ostream &operator<<(std::ostream &os, const TrackingSpeaker &reader) {
        os << reader.freed_packet_;
        return os;
    }
}