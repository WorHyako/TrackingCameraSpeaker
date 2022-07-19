#ifndef TRACKINGCAMERASPEAKER_FREEDPACKET_H
#define TRACKINGCAMERASPEAKER_FREEDPACKET_H

#include "CameraData.h"
#include "PartialBuffer.h"

#include <iostream>
#include <array>

namespace worLib {

    const int FREED_PACKET_LENGTH = 29;

    class FreeDPacket {
    public:
        enum camera_data_type {
            loc_rot_lens, loc_rot, loc, rot, lens, rot_lens, loc_lens,
        } os_flag_ = rot;

        FreeDPacket() = default;

        friend std::ostream &operator<<(std::ostream &os, const FreeDPacket &freeDPacket);

    private:
        CameraData camera_data_;

        PartialBuffer partialBuffer_;

    public:
        void parseData(std::array<unsigned char, FREED_PACKET_LENGTH> data);

    private:
        float parseAngle(unsigned char &a, unsigned char &b, unsigned char &c) const;

        float parseLocation(unsigned char &a, unsigned char &b, unsigned char &c) const;

        int parseLens(unsigned char &a, unsigned char &b, unsigned char &c) const;

    public:
        float getRz() const { return camera_data_.rz_; }

        float getRy() const { return camera_data_.ry_; }

        float getRx() const { return camera_data_.rx_; }

        float getX() const { return camera_data_.x_; }

        float getY() const { return camera_data_.y_; }

        float getZ() const { return camera_data_.z_; }

        int getZoom() const { return camera_data_.zoom_; }

        int getFocus() const { return camera_data_.focus_; }

        bool getUseFracture() const { return camera_data_.use_fracture_; }

        void setUseFracture(bool frac) { camera_data_.use_fracture_ = frac; }
    };
}

#endif
