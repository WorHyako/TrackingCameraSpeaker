#include "freeD/FreedPacket.hpp"

using namespace worTCS;

void FreeDPacket::packetToData(const std::array<std::byte, FREED_PACKET_LENGTH> &data_) {
    _partialBuffer.tryToAppendNewData(data_);
    if (!(_partialBuffer.isPacketCompleted() && _partialBuffer.isPacketValid())) {
        return;
    }
    CameraData newCameraData;
    newCameraData.rotation.z = bytesToAngles(
            _partialBuffer.getPacket()[2], _partialBuffer.getPacket()[3], _partialBuffer.getPacket()[4]);
    newCameraData.rotation.y =
            bytesToAngles(_partialBuffer.getPacket()[5], _partialBuffer.getPacket()[6], _partialBuffer.getPacket()[7]);
    newCameraData.rotation.x =
            bytesToAngles(_partialBuffer.getPacket()[8], _partialBuffer.getPacket()[9], _partialBuffer.getPacket()[10]);
    newCameraData.position.x =
            bytesToLocation(_partialBuffer.getPacket()[11], _partialBuffer.getPacket()[12],
                            _partialBuffer.getPacket()[13]);
    newCameraData.position.y =
            bytesToLocation(_partialBuffer.getPacket()[14], _partialBuffer.getPacket()[15],
                            _partialBuffer.getPacket()[16]);
    newCameraData.position.z =
            bytesToLocation(_partialBuffer.getPacket()[17], _partialBuffer.getPacket()[18],
                            _partialBuffer.getPacket()[19]);
    newCameraData.zoom =
            bytesToLens(_partialBuffer.getPacket()[20], _partialBuffer.getPacket()[21], _partialBuffer.getPacket()[22]);
    newCameraData.focus =
            bytesToLens(_partialBuffer.getPacket()[23], _partialBuffer.getPacket()[24], _partialBuffer.getPacket()[25]);
    _cameraData = newCameraData;
}

float FreeDPacket::bytesToAngles(const std::byte &a_, const std::byte &b_, const std::byte &c_) const noexcept {
    /// Pre-cast to simple coding
    int a = static_cast<int>(a_);
    int b = static_cast<int>(b_);
    int c = static_cast<int>(c_);

    const bool negativeSign = (a & 0b10000000) > 0;
    float value;
    int intPart;
    float fracPart;

    if (_cameraData.useFracture) {
        if (negativeSign) {
            intPart = ((~a & 0b01111111) << 1) | ((~b & 0b10000000) >> 7);
            fracPart =
                    static_cast<float>((((b & 0b01111111) << 8) | c) & 0b0111111111111111) / 0b0111111111111111;
            fracPart = 1 - fracPart;
        } else {
            intPart = ((a & 0b01111111) << 1) | ((b & 0b10000000) >> 7);
            fracPart = static_cast<float>((((b & 0b01111111) << 8) | c) & 0b0111111111111111) / 0b0111111111111111;
        }
        value = static_cast<float>(intPart) + fracPart;
    } else {
        int temp = ((((a & 0b01111111) << 16) | (b << 8) | c) & 0b011111111111111111111111);
        if (negativeSign) {
            temp = (~temp) & 0b011111111111111111111111;
        }
        value = static_cast<float>(temp) / 32768.0f;
    }
    return negativeSign ? -value : value;
}

float FreeDPacket::bytesToLocation(const std::byte &a_, const std::byte &b_, const std::byte &c_) const noexcept {
    /// Pre-cast to simple coding
    int a = static_cast<int>(a_);
    int b = static_cast<int>(b_);
    int c = static_cast<int>(c_);

    const bool negativeSign = (a & 0b10000000) > 0;
    float value;
    int intPart;
    float fracPart;

    if (_cameraData.useFracture) {
        if (negativeSign) {
            intPart = ((~a & 0b01111111) << 10) | ((~b & 0b11111111) << 2) | ((~c & 0b11000000) >> 2);
            fracPart = static_cast<float>(c & 0b00111111) / 0b00111111;
            fracPart = 1 - fracPart;
        } else {
            intPart = ((a & 0b01111111) << 10) | ((b & 0b11111111) << 2) | ((c & 0b11000000) >> 2);
            fracPart = static_cast<float>(c & 0b00111111) / 0b00111111;
        }
        value = static_cast<float>(intPart) + fracPart;
    } else {
        int temp = ((((a & 0b01111111) << 16) | (b << 8) | c) & 0b011111111111111111111111);
        if (negativeSign) {
            temp = (~temp) & 0b011111111111111111111111;
        }
        value = static_cast<float>(temp) / 64.0f;
    }
    return negativeSign ? -value : value;
}

int FreeDPacket::bytesToLens(const std::byte &a_, const std::byte &b_, const std::byte &c_) const noexcept {
    if (_cameraData.useFracture) {
        return static_cast<int>((b_ << 8) | c_);
    } else {
        const bool sign = (static_cast<int>(a_) & 0b10000000) > 0;
        int temp = static_cast<int>((a_ << 16) | (b_ << 8) | c_);

        if (sign) {
            temp = (~temp) & 0b111111111111111111111111;
        }
        return sign ? -temp : temp;
    }
}

std::ostream &operator<<(std::ostream &os_, const FreeDPacket &freeDPacket_) {
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

std::string FreeDPacket::getRotationViaString() const noexcept {
    std::stringstream ss;
    ss << "\npan: " << _cameraData.rotation.z
       << "\ntilt: " << _cameraData.rotation.x
       << "\nroll: " << _cameraData.rotation.y;
    return ss.str();
}

std::string FreeDPacket::getLocationViaString() const noexcept {
    std::stringstream ss;
    ss << "\nx: " << _cameraData.position.x
       << "\ny: " << _cameraData.position.y
       << "\nz: " << _cameraData.position.z;
    return ss.str();
}

std::string FreeDPacket::getLensViaString() const noexcept {
    std::stringstream ss;
    ss << "\nzoom: " << _cameraData.zoom
       << "\nfocus: " << _cameraData.focus;
    return ss.str();
}

#pragma region Accessors

int FreeDPacket::getZoom() const noexcept {
    return _cameraData.zoom;
}

int FreeDPacket::getFocus() const noexcept {
    return _cameraData.focus;
}

bool FreeDPacket::getUseFracture() const noexcept {
    return _cameraData.useFracture;
}

const Vector3<float> &FreeDPacket::getPosition() const noexcept {
    return _cameraData.position;
}

const Vector3<float> &FreeDPacket::getRotation() const noexcept {
    return _cameraData.rotation;
}

#pragma endregion Accessors

#pragma region Mutators

void FreeDPacket::setUseFracture(bool fracture_) noexcept {
    _cameraData.useFracture = fracture_;
}

#pragma endregion Mutators
