#ifndef TRACKINGCAMERASPEAKER_PARTIALBUFFER_H
#define TRACKINGCAMERASPEAKER_PARTIALBUFFER_H

#include <array>
#include <string>

namespace worLib {

    const int PARTIAL_BUFFER_PACKET_LENGTH = 29;

    class PartialBuffer {
    public:
        PartialBuffer();

        std::array<unsigned char, 29> buffer_;
        int delta_byte_;
        bool packet_valid_;
        bool packet_complete_;

        bool tryToAppendNewData(const std::array<unsigned char, PARTIAL_BUFFER_PACKET_LENGTH> &new_data);

        bool checkChecksum(const std::array<unsigned char, PARTIAL_BUFFER_PACKET_LENGTH> &byte_array) const;
    };
}

#endif
