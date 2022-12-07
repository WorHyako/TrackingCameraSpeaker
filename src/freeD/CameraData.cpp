#include "freeD/CameraData.hpp"

#include <cmath>

using namespace worTCS;

CameraData::CameraData(float jointValue_) noexcept {
    position = jointValue_;
    rotation = jointValue_;
    focus = static_cast<int>(jointValue_);
    zoom = static_cast<int>(jointValue_);
    useFracture = false;
    empty = true;
}

CameraData CameraData::absCameraData() noexcept {
    CameraData result;
    result.rotation.x = std::abs(rotation.x);
    result.rotation.y = std::abs(rotation.y);
    result.rotation.z = std::abs(rotation.z);
    result.position.x = std::abs(position.x);
    result.position.y = std::abs(position.y);
    result.position.z = std::abs(position.z);
    result.focus = std::abs(focus);
    result.zoom = std::abs(zoom);
    result.useFracture = false;
    result.empty = true;
    return result;
}

#pragma region Operators

bool CameraData::operator==(const CameraData &rhs_) const noexcept {
    return position == rhs_.position
           && rotation == rhs_.rotation
           && zoom == rhs_.zoom
           && focus == rhs_.focus;
}

bool CameraData::operator!=(const CameraData &rhs_) const noexcept {
    return rotation != rhs_.rotation
           && position != rhs_.position
           && zoom != rhs_.zoom
           && focus != rhs_.focus;
}

CameraData operator-(CameraData lhs_, float rhs_) noexcept {
    lhs_.position -= rhs_;
    lhs_.rotation -= rhs_;
    lhs_.zoom -= static_cast<int>(rhs_);
    lhs_.focus -= static_cast<int>(rhs_);
    return lhs_;
}

CameraData operator-(CameraData lhs_, CameraData rhs_) noexcept {
    lhs_.rotation -= rhs_.rotation;
    lhs_.position -= rhs_.position;
    lhs_.zoom -= rhs_.zoom;
    lhs_.focus -= rhs_.focus;
    return lhs_;
}

CameraData operator+(CameraData lhs_, CameraData rhs_) noexcept {
    lhs_.rotation += rhs_.rotation;
    lhs_.position += rhs_.position;
    lhs_.zoom += rhs_.zoom;
    lhs_.focus += rhs_.focus;
    return lhs_;
}

CameraData operator+(CameraData lhs_, float rhs_) noexcept {
    lhs_.position += rhs_;
    lhs_.rotation += rhs_;
    lhs_.zoom += static_cast<int>(rhs_);
    lhs_.focus += static_cast<int>(rhs_);
    return lhs_;
}

CameraData operator*(CameraData lhs_, CameraData rhs_) noexcept {
    lhs_.position *= rhs_.position;
    lhs_.rotation *= rhs_.rotation;
    lhs_.zoom *= static_cast<int>(rhs_.zoom);
    lhs_.focus *= static_cast<int>(rhs_.focus);
    return lhs_;
}

CameraData operator*(CameraData lhs_, float rhs_) noexcept {
    lhs_.position *= rhs_;
    lhs_.rotation *= rhs_;
    lhs_.zoom *= static_cast<int>(rhs_);
    lhs_.focus *= static_cast<int>(rhs_);
    return lhs_;
}

CameraData operator/(CameraData lhs_, CameraData rhs_) noexcept {
    lhs_.position /= rhs_.position;
    lhs_.rotation /= rhs_.rotation;
    lhs_.zoom /= static_cast<int>(rhs_.zoom);
    lhs_.focus /= static_cast<int>(rhs_.focus);
    return lhs_;
}

CameraData operator/(CameraData lhs_, float rhs_) noexcept {
    lhs_.position /= rhs_;
    lhs_.rotation /= rhs_;
    lhs_.zoom /= static_cast<int>(rhs_);
    lhs_.focus /= static_cast<int>(rhs_);
    return lhs_;
}

#pragma endregion Operators
