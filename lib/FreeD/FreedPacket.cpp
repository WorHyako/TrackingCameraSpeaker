#include "FreedPacket.h"

namespace worLib {

    void FreeDPacket::parseData(std::array<unsigned char, FREED_PACKET_LENGTH> data) {
        CameraData new_camera_data;
        partialBuffer_.tryToAppendNewData(data);
        if (!(partialBuffer_.packet_complete_ && partialBuffer_.packet_valid_)) return;

        new_camera_data.rz_ =
                parseAngle(partialBuffer_.buffer_[2], partialBuffer_.buffer_[3], partialBuffer_.buffer_[4]);
        new_camera_data.ry_ =
                parseAngle(partialBuffer_.buffer_[5], partialBuffer_.buffer_[6], partialBuffer_.buffer_[7]);
        new_camera_data.rx_ =
                parseAngle(partialBuffer_.buffer_[8], partialBuffer_.buffer_[9], partialBuffer_.buffer_[10]);
        new_camera_data.x_ =
                parseLocation(partialBuffer_.buffer_[11], partialBuffer_.buffer_[12], partialBuffer_.buffer_[13]);
        new_camera_data.y_ =
                parseLocation(partialBuffer_.buffer_[14], partialBuffer_.buffer_[15], partialBuffer_.buffer_[16]);
        new_camera_data.z_ =
                parseLocation(partialBuffer_.buffer_[17], partialBuffer_.buffer_[18], partialBuffer_.buffer_[19]);
        new_camera_data.zoom_ =
                parseLens(partialBuffer_.buffer_[20], partialBuffer_.buffer_[21], partialBuffer_.buffer_[22]);
        new_camera_data.focus_ =
                parseLens(partialBuffer_.buffer_[23], partialBuffer_.buffer_[24], partialBuffer_.buffer_[25]);

        camera_data_ = new_camera_data;
    }

    float FreeDPacket::parseAngle(unsigned char &a, unsigned char &b, unsigned char &c) const {
        bool negative_sign = (a & 0b10000000) > 0;
        float value;
        int int_part;
        float frac_part;

        if (camera_data_.use_fracture_) {
            if (negative_sign) {
                int_part = ((~a & 0b01111111) << 1) | ((~b & 0b10000000) >> 7);
                frac_part = static_cast<float>((((b & 0b01111111) << 8) | c) & 0b0111111111111111) / 0b0111111111111111;
                frac_part = 1 - frac_part;
            } else {
                int_part = ((a & 0b01111111) << 1) | ((b & 0b10000000) >> 7);
                frac_part = static_cast<float>((((b & 0b01111111) << 8) | c) & 0b0111111111111111) / 0b0111111111111111;
            }
            value = static_cast<float>(int_part) + frac_part;
        } else {
            int temp = ((((a & 0b01111111) << 16) | (b << 8) | c) & 0b011111111111111111111111);
            if (negative_sign) {
                temp = (~temp) & 0b011111111111111111111111;
            }
            value = static_cast<float>(temp) / 32768.0f;
        }
        return negative_sign ? -value : value;
    }

    float FreeDPacket::parseLocation(unsigned char &a, unsigned char &b, unsigned char &c) const {
        bool negative_sign = (a & 0b10000000) > 0;
        float value;
        int int_part;
        float frac_part;

        if (camera_data_.use_fracture_) {
            if (negative_sign) {
                int_part = ((~a & 0b01111111) << 10) | ((~b & 0b11111111) << 2) | ((~c & 0b11000000) >> 2);
                frac_part = static_cast<float>(c & 0b00111111) / 0b00111111;
                frac_part = 1 - frac_part;
            } else {
                int_part = ((a & 0b01111111) << 10) | ((b & 0b11111111) << 2) | ((c & 0b11000000) >> 2);
                frac_part = static_cast<float>(c & 0b00111111) / 0b00111111;
            }
            value = static_cast<float>(int_part) + frac_part;
        } else {
            int temp = ((((a & 0b01111111) << 16) | (b << 8) | c) & 0b011111111111111111111111);
            if (negative_sign)
                temp = (~temp) & 0b011111111111111111111111;

            value = static_cast<float>(temp) / 64.0f;
        }
        return negative_sign ? -value : value;
    }

    int FreeDPacket::parseLens(unsigned char &a, unsigned char &b, unsigned char &c) const {
        if (camera_data_.use_fracture_)
            return ((b << 8) | c);
        else {
            bool sign = (a & 0b10000000) > 0;
            int temp = (a << 16) | (b << 8) | c;

            if (sign)
                temp = (~temp) & 0b111111111111111111111111;

            return sign ? -temp : temp;
        }
    }

    std::ostream &operator<<(std::ostream &os, const FreeDPacket &freeDPacket) {
        os << "Completed camera data:";
        switch (freeDPacket.os_flag_) {
            using std::cout;
            case FreeDPacket::loc_rot_lens:
                cout << "\nx: " << freeDPacket.camera_data_.x_
                     << "\ny: " << freeDPacket.camera_data_.y_
                     << "\nz: " << freeDPacket.camera_data_.z_;
                cout << "\npan: " << freeDPacket.camera_data_.rz_
                     << "\ntilt: " << freeDPacket.camera_data_.rx_
                     << "\nroll: " << freeDPacket.camera_data_.ry_;
                cout << "\nzoom: " << freeDPacket.camera_data_.zoom_
                     << "\nfocus: " << freeDPacket.camera_data_.focus_;
                break;
            case FreeDPacket::loc_rot:
                cout << "\nx: " << freeDPacket.camera_data_.x_
                     << "\ny: " << freeDPacket.camera_data_.y_
                     << "\nz: " << freeDPacket.camera_data_.z_;
                cout << "\npan: " << freeDPacket.camera_data_.rz_
                     << "\ntilt: " << freeDPacket.camera_data_.rx_
                     << "\nroll: " << freeDPacket.camera_data_.ry_;
                break;
            case FreeDPacket::loc:
                cout << "\nx: " << freeDPacket.camera_data_.x_
                     << "\ny: " << freeDPacket.camera_data_.y_
                     << "\nz: " << freeDPacket.camera_data_.z_;
                break;
            case FreeDPacket::rot:
                cout << "\npan: " << freeDPacket.camera_data_.rz_
                     << "\ntilt: " << freeDPacket.camera_data_.rx_
                     << "\nroll: " << freeDPacket.camera_data_.ry_;
                break;
            case FreeDPacket::lens:
                cout << "\nzoom: " << freeDPacket.camera_data_.zoom_
                     << "\nfocus: " << freeDPacket.camera_data_.focus_;
                break;
            case FreeDPacket::rot_lens:
                cout << "\npan: " << freeDPacket.camera_data_.rz_
                     << "\ntilt: " << freeDPacket.camera_data_.rx_
                     << "\nroll: " << freeDPacket.camera_data_.ry_;
                cout << "\nzoom: " << freeDPacket.camera_data_.zoom_
                     << "\nfocus: " << freeDPacket.camera_data_.focus_;
                break;
            case FreeDPacket::loc_lens:
                cout << "\nx: " << freeDPacket.camera_data_.x_
                     << "\ny: " << freeDPacket.camera_data_.y_
                     << "\nz: " << freeDPacket.camera_data_.z_;
                cout << "\nzoom: " << freeDPacket.camera_data_.zoom_
                     << "\nfocus: " << freeDPacket.camera_data_.focus_;
                break;
            default:
                cout << "\nERROR: Unknown flag";
                break;
        }
        return os;
    }
}
