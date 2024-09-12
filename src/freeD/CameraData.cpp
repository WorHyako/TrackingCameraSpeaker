#include "freeD/CameraData.hpp"

#include <cmath>

using namespace WorTCS;

CameraData::CameraData() noexcept
	: zoom(0),
	  focus(0),
	  useFracture(false),
	  empty(true) {
}

CameraData CameraData::absCameraData() const noexcept {
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

bool CameraData::operator==(const CameraData& rhs) const noexcept {
	return position == rhs.position
			&& rotation == rhs.rotation
			&& zoom == rhs.zoom
			&& focus == rhs.focus;
}

bool CameraData::operator!=(const CameraData& rhs) const noexcept {
	return rotation != rhs.rotation
			&& position != rhs.position
			&& zoom != rhs.zoom
			&& focus != rhs.focus;
}

CameraData operator-(CameraData lhs, float rhs) noexcept {
	lhs.position -= rhs;
	lhs.rotation -= rhs;
	lhs.zoom -= static_cast<int>(rhs);
	lhs.focus -= static_cast<int>(rhs);
	return lhs;
}

CameraData operator-(CameraData lhs, CameraData rhs) noexcept {
	lhs.rotation -= rhs.rotation;
	lhs.position -= rhs.position;
	lhs.zoom -= rhs.zoom;
	lhs.focus -= rhs.focus;
	return lhs;
}

CameraData operator+(CameraData lhs, CameraData rhs) noexcept {
	lhs.rotation += rhs.rotation;
	lhs.position += rhs.position;
	lhs.zoom += rhs.zoom;
	lhs.focus += rhs.focus;
	return lhs;
}

CameraData operator+(CameraData lhs, float rhs) noexcept {
	lhs.position += rhs;
	lhs.rotation += rhs;
	lhs.zoom += static_cast<int>(rhs);
	lhs.focus += static_cast<int>(rhs);
	return lhs;
}

CameraData operator*(CameraData lhs, CameraData rhs) noexcept {
	lhs.position *= rhs.position;
	lhs.rotation *= rhs.rotation;
	lhs.zoom *= rhs.zoom;
	lhs.focus *= rhs.focus;
	return lhs;
}

CameraData operator*(CameraData lhs, float rhs) noexcept {
	lhs.position *= rhs;
	lhs.rotation *= rhs;
	lhs.zoom *= static_cast<int>(rhs);
	lhs.focus *= static_cast<int>(rhs);
	return lhs;
}

CameraData operator/(CameraData lhs, CameraData rhs) noexcept {
	lhs.position /= rhs.position;
	lhs.rotation /= rhs.rotation;
	lhs.zoom /= rhs.zoom;
	lhs.focus /= rhs.focus;
	return lhs;
}

CameraData operator/(CameraData lhs, float rhs) noexcept {
	lhs.position /= rhs;
	lhs.rotation /= rhs;
	lhs.zoom /= static_cast<int>(rhs);
	lhs.focus /= static_cast<int>(rhs);
	return lhs;
}

#pragma endregion Operators
