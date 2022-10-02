#include "PartialBuffer.hpp"

using namespace worCameraTracking;

PartialBuffer::PartialBuffer() {
    _deltaByte = 0;

    _buffer.fill('0');
    _packetValid = false;
    _packetComplete = true;
}

bool PartialBuffer::tryToAppendNewData(const std::array<byte, PARTIAL_BUFFER_LENGTH> &newData_) {
    if (*newData_.begin() == 0xD1) {
        std::copy(newData_.begin(), newData_.end(), _buffer.begin());
        _packetComplete = true;

        _packetValid = checkChecksum(_buffer);
        return _packetValid;
    }

    if (!_packetComplete && _deltaByte) {
        for (int i = 0; i < _deltaByte; i++) {
            _buffer[i + (_buffer.size() - _deltaByte)] = newData_[i];
        }

        _packetComplete = checkChecksum(_buffer);
        return _packetValid;
    }

    int16_t index = 1;
    for (auto it = (newData_.begin() + 1); it < newData_.end(); it++, index++) {
        if (*it != 0xD1) {
            continue;
        }
        _deltaByte = index;
        int16_t bufferIndex;
        int16_t newDataIndex;
        for (newDataIndex = index, bufferIndex = 0; newDataIndex < newData_.size(); newDataIndex++, bufferIndex++) {
            _buffer[bufferIndex] = newData_[newDataIndex];
        }
        for (; bufferIndex < _buffer.size(); bufferIndex++) {
            _buffer[bufferIndex] = '0';
        }
        _packetComplete = false;
        break;
    }
    return false;
}

bool PartialBuffer::checkChecksum(const std::array<byte, PARTIAL_BUFFER_LENGTH> &byteArray_) const {
    auto checksum = 0x40;
    for (auto it = byteArray_.begin(); it < (byteArray_.end() - 1); it++) {
        checksum -= *it;
    }

    while (checksum < 0) {
        checksum += 256;
    }
    return (checksum == *(byteArray_.end() - 1));
}
