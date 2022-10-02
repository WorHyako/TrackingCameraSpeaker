#ifndef TRACKINGCAMERASPEAKER_FREEDPACKET_HPP
#define TRACKINGCAMERASPEAKER_FREEDPACKET_HPP

#include "CameraData.hpp"
#include "PartialBuffer.hpp"

#include <iostream>
#include <sstream>
#include <array>

typedef unsigned char byte;

namespace worCameraTracking {

    constexpr int FREED_PACKET_LENGTH = 29;

    class FreeDPacket final {
    public:
        enum class CameraDataType {
            LOC_ROT_LENS, LOC_ROT, LOC, ROT, LENS, ROT_LENS, LOC_LENS,
        } _streamFlag = CameraDataType::ROT;

        FreeDPacket() = default;

        friend std::ostream &operator<<(std::ostream &os_, const FreeDPacket &freeDPacket_);

    private:
        CameraData _cameraData;

        PartialBuffer _partialBuffer;

    public:
        void packetToData(const std::array<byte, FREED_PACKET_LENGTH> &data_);

    private:
        float parseAngle(byte &a_, byte &b_, byte &c_) const;

        float parseLocation(byte &a_, byte &b_, byte &c_) const;

        int parseLens(byte &a_, byte &b_, byte &c_) const;

    public:
#pragma region Accessors

        float getRz() const;

        float getRy() const;

        float getRx() const;

        float getX() const;

        float getY() const;

        float getZ() const;

        int getZoom() const;

        int getFocus() const;

        bool getUseFracture() const;

        std::string getRotationViaString() const;

        std::string getLocationViaString() const;

        std::string getLensViaString() const;

#pragma endregion Accessors

#pragma region Mutators

        void setUseFracture(bool fracture_);

#pragma endregion Mutators
    };
}
#endif
