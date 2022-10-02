#include "FreedPacket.hpp"

using namespace worCameraTracking;

void FreeDPacket::packetToData(const std::array<byte, FREED_PACKET_LENGTH> &data_) {
    _partialBuffer.tryToAppendNewData(data_);
    if (!(_partialBuffer._packetComplete && _partialBuffer._packetValid)) {
        return;
    }
    CameraData newCameraData;
    newCameraData._rz =
            parseAngle(_partialBuffer._buffer[2], _partialBuffer._buffer[3], _partialBuffer._buffer[4]);
    newCameraData._ry =
            parseAngle(_partialBuffer._buffer[5], _partialBuffer._buffer[6], _partialBuffer._buffer[7]);
    newCameraData._rx =
            parseAngle(_partialBuffer._buffer[8], _partialBuffer._buffer[9], _partialBuffer._buffer[10]);
    newCameraData._x =
            parseLocation(_partialBuffer._buffer[11], _partialBuffer._buffer[12], _partialBuffer._buffer[13]);
    newCameraData._y =
            parseLocation(_partialBuffer._buffer[14], _partialBuffer._buffer[15], _partialBuffer._buffer[16]);
    newCameraData._z =
            parseLocation(_partialBuffer._buffer[17], _partialBuffer._buffer[18], _partialBuffer._buffer[19]);
    newCameraData._zoom =
            parseLens(_partialBuffer._buffer[20], _partialBuffer._buffer[21], _partialBuffer._buffer[22]);
    newCameraData._focus =
            parseLens(_partialBuffer._buffer[23], _partialBuffer._buffer[24], _partialBuffer._buffer[25]);

    _cameraData = newCameraData;
}

float FreeDPacket::parseAngle(byte &a_, byte &b_, byte &c_) const {
    const bool negativeSign = (a_ & 0b10000000) > 0;
    float value;
    int intPart;
    float fracPart;

    if (_cameraData._useFracture) {
        if (negativeSign) {
            intPart = ((~a_ & 0b01111111) << 1) | ((~b_ & 0b10000000) >> 7);
            fracPart =
                    static_cast<float>((((b_ & 0b01111111) << 8) | c_) & 0b0111111111111111) / 0b0111111111111111;
            fracPart = 1 - fracPart;
        } else {
            intPart = ((a_ & 0b01111111) << 1) | ((b_ & 0b10000000) >> 7);
            fracPart =
                    static_cast<float>((((b_ & 0b01111111) << 8) | c_) & 0b0111111111111111) / 0b0111111111111111;
        }
        value = static_cast<float>(intPart) + fracPart;
    } else {
        int temp = ((((a_ & 0b01111111) << 16) | (b_ << 8) | c_) & 0b011111111111111111111111);
        if (negativeSign) {
            temp = (~temp) & 0b011111111111111111111111;
        }
        value = static_cast<float>(temp) / 32768.0f;
    }
    return negativeSign ? -value : value;
}

float FreeDPacket::parseLocation(byte &a_, byte &b_, byte &c_) const {
    const bool negativeSign = (a_ & 0b10000000) > 0;
    float value;
    int intPart;
    float fracPart;

    if (_cameraData._useFracture) {
        if (negativeSign) {
            intPart = ((~a_ & 0b01111111) << 10) | ((~b_ & 0b11111111) << 2) | ((~c_ & 0b11000000) >> 2);
            fracPart = static_cast<float>(c_ & 0b00111111) / 0b00111111;
            fracPart = 1 - fracPart;
        } else {
            intPart = ((a_ & 0b01111111) << 10) | ((b_ & 0b11111111) << 2) | ((c_ & 0b11000000) >> 2);
            fracPart = static_cast<float>(c_ & 0b00111111) / 0b00111111;
        }
        value = static_cast<float>(intPart) + fracPart;
    } else {
        int temp = ((((a_ & 0b01111111) << 16) | (b_ << 8) | c_) & 0b011111111111111111111111);
        if (negativeSign) {
            temp = (~temp) & 0b011111111111111111111111;
        }
        value = static_cast<float>(temp) / 64.0f;
    }
    return negativeSign ? -value : value;
}

int FreeDPacket::parseLens(byte &a_, byte &b_, byte &c_) const {
    if (_cameraData._useFracture) {
        return ((b_ << 8) | c_);
    } else {
        const bool sign = (a_ & 0b10000000) > 0;
        int temp = (a_ << 16) | (b_ << 8) | c_;

        if (sign) {
            temp = (~temp) & 0b111111111111111111111111;
        }
        return sign ? -temp : temp;
    }
}

std::ostream &worCameraTracking::operator<<(std::ostream &os_, const FreeDPacket &freeDPacket_) {
    os_ << "\nCompleted camera data:";
    switch (freeDPacket_._streamFlag) {
        using std::cout;
        case FreeDPacket::CameraDataType::LOC_ROT_LENS:
            cout << freeDPacket_.getLocationViaString()
                 << freeDPacket_.getRotationViaString()
                 << freeDPacket_.getLensViaString();
            break;
        case FreeDPacket::CameraDataType::LOC_ROT:
            cout << freeDPacket_.getLocationViaString()
                 << freeDPacket_.getRotationViaString();
            break;
        case FreeDPacket::CameraDataType::LOC:
            cout << freeDPacket_.getLocationViaString();
            break;
        case FreeDPacket::CameraDataType::ROT:
            cout << freeDPacket_.getRotationViaString();
            break;
        case FreeDPacket::CameraDataType::LENS:
            cout << freeDPacket_.getLensViaString();
            break;
        case FreeDPacket::CameraDataType::ROT_LENS:
            cout << freeDPacket_.getRotationViaString()
                 << freeDPacket_.getLensViaString();
            break;
        case FreeDPacket::CameraDataType::LOC_LENS:
            cout << freeDPacket_.getLocationViaString()
                 << freeDPacket_.getLensViaString();
            break;
        default:
            cout << "\nERROR: Unknown flag_";
            break;
    }
    return os_;
}

std::string FreeDPacket::getRotationViaString() const {
    std::stringstream ss;
    ss << "\npan: " << _cameraData._rz
       << "\ntilt: " << _cameraData._rx
       << "\nroll: " << _cameraData._ry;
    return ss.str();
}

std::string FreeDPacket::getLocationViaString() const {
    std::stringstream ss;
    ss << "\nx: " << _cameraData._x
       << "\ny: " << _cameraData._y
       << "\nz: " << _cameraData._z;
    return ss.str();
}

std::string FreeDPacket::getLensViaString() const {
    std::stringstream ss;
    ss << "\nzoom: " << _cameraData._zoom
       << "\nfocus: " << _cameraData._focus;
    return ss.str();
}

#pragma region Accessors

float FreeDPacket::getRz() const {
    return _cameraData._rz;
}

float FreeDPacket::getRy() const {
    return _cameraData._ry;
}

float FreeDPacket::getRx() const {
    return _cameraData._rx;
}

float FreeDPacket::getX() const {
    return _cameraData._x;
}

float FreeDPacket::getY() const {
    return _cameraData._y;
}

float FreeDPacket::getZ() const {
    return _cameraData._z;
}

int FreeDPacket::getZoom() const {
    return _cameraData._zoom;
}

int FreeDPacket::getFocus() const {
    return _cameraData._focus;
}

bool FreeDPacket::getUseFracture() const {
    return _cameraData._useFracture;
}

#pragma endregion Accessors

#pragma region Mutators

void FreeDPacket::setUseFracture(bool fracture_) {
    _cameraData._useFracture = fracture_;
}

#pragma endregion Mutators
