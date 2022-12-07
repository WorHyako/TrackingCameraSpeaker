#ifndef TRACKINGCAMERASPEAKER_PARTIALBUFFER_HPP
#define TRACKINGCAMERASPEAKER_PARTIALBUFFER_HPP

#include <array>
#include <string>

namespace worTCS {

    constexpr int partial_buffer_length = 29;

    /**
     * Class to repair packet and fold data
     */
    class PartialBuffer final {
    public:
        PartialBuffer() noexcept;

        void tryToAppendNewData(const std::array<std::byte, partial_buffer_length> &newData_);

        [[nodiscard]] bool checkChecksum(const std::array<std::byte, partial_buffer_length> &byteArray_) const;

    private:
        std::array<std::byte, partial_buffer_length> _packet{};

        int _deltaByte;

        bool _packetValid;

        bool _packetComplete;

    public:
#pragma region Accessors

        [[nodiscard]] const std::array<std::byte, partial_buffer_length> &getPacket() const noexcept;

        [[nodiscard]] bool isPacketValid() const noexcept;

        [[nodiscard]] bool isPacketCompleted() const noexcept;

#pragma endregion Accessors
    };
}
#endif
