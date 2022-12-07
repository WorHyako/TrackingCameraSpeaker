#include "freeD/PartialBuffer.hpp"

using namespace worTCS;

PartialBuffer::PartialBuffer() noexcept {
    _deltaByte = 0;
    _packet.fill(std::byte(0x00));
    _packetValid = false;
    _packetComplete = true;
}

void PartialBuffer::tryToAppendNewData(const std::array<std::byte, partial_buffer_length> &newData_) {
    if (*newData_.begin() == std::byte(0xD1)) {
        std::copy(newData_.begin(), newData_.end(), _packet.begin());
        _packetComplete = true;

        _packetValid = checkChecksum(_packet);
    }

    if (!_packetComplete && _deltaByte) {
        for (int i = 0; i < _deltaByte; i++) {
            _packet[i + (_packet.size() - _deltaByte)] = newData_[i];
        }

        _packetComplete = checkChecksum(_packet);
    }

    int16_t index = 1;
    for (auto it = (newData_.begin() + 1); it < newData_.end(); it++, index++) {
        if (static_cast<int>(*it) != 0xD1) {
            continue;
        }
        _deltaByte = index;
        int16_t bufferIndex;
        int16_t newDataIndex;
        for (newDataIndex = index, bufferIndex = 0; newDataIndex < newData_.size(); newDataIndex++, bufferIndex++) {
            _packet[bufferIndex] = newData_[newDataIndex];
        }
        for (; bufferIndex < _packet.size(); bufferIndex++) {
            _packet[bufferIndex] = std::byte(0x00);
        }
        _packetComplete = false;
        break;
    }
}

bool PartialBuffer::checkChecksum(const std::array<std::byte, partial_buffer_length> &byteArray_) const {
    int checksum = 0x40;
    for (auto it = byteArray_.begin(); it < (byteArray_.end() - 1); it++) {
        checksum -= static_cast<int>(*it);
    }

    while (checksum < 0) {
        checksum += 256;
    }
    return (checksum == static_cast<int>(*(byteArray_.end() - 1)));
}

#pragma region Accessors

bool PartialBuffer::isPacketValid() const noexcept {
    return _packetValid;
}

const std::array<std::byte, partial_buffer_length> &PartialBuffer::getPacket() const noexcept {
    return _packet;
}

bool PartialBuffer::isPacketCompleted() const noexcept {
    return _packetComplete;
}

#pragma region Accessors
