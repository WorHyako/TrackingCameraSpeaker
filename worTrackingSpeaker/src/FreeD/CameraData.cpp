#include "CameraData.hpp"

#include <cmath>

using namespace worCameraTracking;

CameraData::CameraData(int jointValue_) {
    _rz = static_cast<float>(jointValue_);
    _rx = static_cast<float>(jointValue_);
    _ry = static_cast<float>(jointValue_);
    _x = static_cast<float>(jointValue_);
    _y = static_cast<float>(jointValue_);
    _z = static_cast<float>(jointValue_);
    _focus = jointValue_;
    _zoom = jointValue_;
    _useFracture = false;
    _empty = true;
}

CameraData CameraData::absCameraData() {
    CameraData result;
    result._rz = std::abs(_rz);
    result._rx = std::abs(_rx);
    result._ry = std::abs(_ry);
    result._x = std::abs(_x);
    result._y = std::abs(_y);
    result._z = std::abs(_z);
    result._focus = std::abs(_focus);
    result._zoom = std::abs(_zoom);
    result._useFracture = false;
    result._empty = true;
    return result;
}

bool CameraData::operator==(const CameraData &b_) const {
    return (_rz == b_._rz
            && _ry == b_._ry
            && _rx == b_._rx
            && _x == b_._x
            && _y == b_._y
            && _z == b_._z
            && _zoom == b_._zoom
            && _focus == b_._focus);
}

bool CameraData::operator!=(const CameraData &b_) const {
    return (_rz != b_._rz
            && _ry != b_._ry
            && _rx != b_._rx
            && _x != b_._x
            && _y != b_._y
            && _z != b_._z
            && _zoom != b_._zoom
            && _focus != b_._focus);
}

bool CameraData::operator<(const CameraData &b_) const {
    return (_rz < b_._rz
            && _ry < b_._ry
            && _rx < b_._rx
            && _x < b_._x
            && _y < b_._y
            && _z < b_._z
            && _zoom < b_._zoom
            && _focus < b_._focus);
}

bool CameraData::operator>(const CameraData &b_) const {
    return (_rz > b_._rz
            && _ry > b_._ry
            && _rx > b_._rx
            && _x > b_._x
            && _y > b_._y
            && _z > b_._z
            && _zoom > b_._zoom
            && _focus > b_._focus);
}

CameraData CameraData::operator-(const CameraData &b_) const {
    CameraData c;
    c._rz = _rz - b_._rz;
    c._ry = _ry - b_._ry;
    c._rx = _rx - b_._rx;
    c._x = _x - b_._x;
    c._y = _y - b_._y;
    c._z = _z - b_._z;
    c._zoom = _zoom - b_._zoom;
    c._focus = _focus - b_._focus;
    return c;
}

CameraData CameraData::operator-(const float &b_) const {
    CameraData c;
    c._rz = _rz - b_;
    c._ry = _ry - b_;
    c._rx = _rx - b_;
    c._x = _x - b_;
    c._y = _y - b_;
    c._z = _z - b_;
    c._zoom = _zoom - static_cast<int>(b_);
    c._focus = _focus - static_cast<int>(b_);
    return c;
}

CameraData CameraData::operator+(const CameraData &b_) const {
    CameraData c;
    c._rz = _rz + b_._rz;
    c._ry = _ry + b_._ry;
    c._rx = _rx + b_._rx;
    c._x = _x + b_._x;
    c._y = _y + b_._y;
    c._z = _z + b_._z;
    c._zoom = _zoom + b_._zoom;
    c._focus = _focus + b_._focus;
    return c;
}

CameraData CameraData::operator+(const float &b_) const {
    CameraData c;
    c._rz = _rz + b_;
    c._ry = _ry + b_;
    c._rx = _rx + b_;
    c._x = _x + b_;
    c._y = _y + b_;
    c._z = _z + b_;
    c._zoom = _zoom + static_cast<int>(b_);
    c._focus = _focus + static_cast<int>(b_);
    return c;
}

CameraData CameraData::operator*(const CameraData &b_) const {
    CameraData c;
    c._rz = _rz * b_._rz;
    c._ry = _ry * b_._ry;
    c._rx = _rx * b_._rx;
    c._x = _x * b_._x;
    c._y = _y * b_._y;
    c._z = _z * b_._z;
    c._zoom = _zoom * b_._zoom;
    c._focus = _focus * b_._focus;
    return c;
}

CameraData CameraData::operator*(const float &b_) const {
    CameraData c;
    c._rz = _rz * b_;
    c._ry = _ry * b_;
    c._rx = _rx * b_;
    c._x = _x * b_;
    c._y = _y * b_;
    c._z = _z * b_;
    c._zoom = _zoom * static_cast<int>(b_);
    c._focus = _focus * static_cast<int>(b_);
    return c;
}

CameraData CameraData::operator/(const CameraData &b_) const {
    CameraData c;
    c._rz = _rz / b_._rz;
    c._ry = _ry / b_._ry;
    c._rx = _rx / b_._rx;
    c._x = _x / b_._x;
    c._y = _y / b_._y;
    c._z = _z / b_._z;
    c._zoom = _zoom / b_._zoom;
    c._focus = _focus / b_._focus;
    return c;
}

CameraData CameraData::operator/(const float &b_) const {
    CameraData c;
    c._rz = _rz / b_;
    c._ry = _ry / b_;
    c._rx = _rx / b_;
    c._x = _x / b_;
    c._y = _y / b_;
    c._z = _z / b_;
    c._zoom = _zoom / static_cast<int>(b_);
    c._focus = _focus / static_cast<int>(b_);
    return c;
}
