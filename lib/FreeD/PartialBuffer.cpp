#include "PartialBuffer.h"

namespace worLib {

    PartialBuffer::PartialBuffer() {
        delta_byte_ = 0;

        buffer_.fill('0');
        packet_valid_ = false;
        packet_complete_ = true;
    }

    bool PartialBuffer::tryToAppendNewData(const std::array<unsigned char, PARTIAL_BUFFER_PACKET_LENGTH> &new_data) {
        if (*new_data.begin() == 0xD1) {
            std::copy(new_data.begin(), new_data.end(), buffer_.begin());
            packet_complete_ = true;

            if (checkChecksum(buffer_)) {
                packet_valid_ = true;
                return true;
            } else {
                packet_valid_ = false;
                return false;
            }
        }

        if (!packet_complete_ && delta_byte_) {
            for (int16_t i = 0; i < delta_byte_; i++)
                buffer_[i + (buffer_.size() - delta_byte_)] = new_data[i];

            if (checkChecksum(buffer_)) {
                packet_complete_ = true;
                packet_valid_ = true;
                delta_byte_ = 0;
                return true;
            } else {
                packet_valid_ = false;
                delta_byte_ = 0;
                return false;
            }
        }

        int16_t index = 1;
        for (auto it = (new_data.begin() + 1); it < new_data.end(); it++, index++) {
            if (*it != 0xD1) continue;
            delta_byte_ = index;
            int16_t buffer_index, new_data_index;
            for (new_data_index = index, buffer_index = 0; new_data_index < new_data.size(); new_data_index++, buffer_index++)
                buffer_[buffer_index] = new_data[new_data_index];

            for (; buffer_index < buffer_.size(); buffer_index++)
                buffer_[buffer_index] = '0';
            packet_complete_ = false;
            break;
        }
        return false;
    }

    bool PartialBuffer::checkChecksum(const std::array<unsigned char, PARTIAL_BUFFER_PACKET_LENGTH> &byte_array) const {
        int checksum = 0x40;
        for (auto it = byte_array.begin(); it < (byte_array.end() - 1); it++)
            checksum -= *it;

        while (checksum < 0) checksum += 256;

        return (checksum == *(byte_array.end() - 1));
    }
}