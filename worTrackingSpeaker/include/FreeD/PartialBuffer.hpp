#ifndef TRACKINGCAMERASPEAKER_PARTIALBUFFER_HPP
#define TRACKINGCAMERASPEAKER_PARTIALBUFFER_HPP

#include <array>
#include <string>

typedef unsigned char byte;

namespace worCameraTracking {

    constexpr int PARTIAL_BUFFER_LENGTH = 29;

    class PartialBuffer final {
    public:
        PartialBuffer();

        std::array<byte, PARTIAL_BUFFER_LENGTH> _buffer;
        int _deltaByte;
        bool _packetValid;
        bool _packetComplete;

        bool tryToAppendNewData(const std::array<byte, PARTIAL_BUFFER_LENGTH> &newData_);

        bool checkChecksum(const std::array<byte, PARTIAL_BUFFER_LENGTH> &byteArray_) const;
    };
}
#endif
