#ifndef TRACKINGCAMERASPEAKER_FREEDPACKET_HPP
#define TRACKINGCAMERASPEAKER_FREEDPACKET_HPP

#include "freeD/CameraData.hpp"
#include "freeD/PartialBuffer.hpp"

#include <sstream>
#include <array>

namespace worTCS {

    /**
     * Class to convert received packet to camera data and store result
     */
    class FreeDPacket final {
    public:
        enum class CameraDataType {
            LOC_ROT_LENS, LOC_ROT, LOC, ROT, LENS, ROT_LENS, LOC_LENS,
        } _streamFlag = CameraDataType::ROT;

        FreeDPacket() = default;

        /// freeD protocol packet length
        static constexpr int freed_packet_length = 29;

        /**
         * Parse packet to data: x, y, z, rx, ry, rz, zoom, focus
         * Use PartialBuffer to repair broken packet
         * Fold data (in future)
         * @param data_ packet to parse
         */
        void packetToData(const std::array<std::byte, freed_packet_length> &data_);

    private:
        CameraData _cameraData;

        PartialBuffer _partialBuffer;

        [[nodiscard]] float bytesToAngles(const std::byte &a_, const std::byte &b_, const std::byte &c_) const noexcept;

        [[nodiscard]] float bytesToLocation(const std::byte &a_, const std::byte &b_, const std::byte &c_) const noexcept;

        [[nodiscard]] int bytesToLens(const std::byte &a_, const std::byte &b_,const  std::byte &c_) const noexcept;

    public:
#pragma region Accessors

        [[nodiscard]] const Vector3<float> &getPosition() const noexcept;

        [[nodiscard]] const Vector3<float> &getRotation() const noexcept;

        [[nodiscard]] int getZoom() const noexcept;

        [[nodiscard]] int getFocus() const noexcept;

        [[nodiscard]] bool getUseFracture() const noexcept;

        [[nodiscard]] std::string getRotationViaString() const noexcept;

        [[nodiscard]] std::string getLocationViaString() const noexcept;

        [[nodiscard]] std::string getLensViaString() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

        void setUseFracture(bool fracture_) noexcept;

#pragma endregion Mutators

#pragma region Operators

        friend std::ostream &operator<<(std::ostream &os_, const FreeDPacket &freeDPacket_);

#pragma endregion Operators
    };
}
#endif
