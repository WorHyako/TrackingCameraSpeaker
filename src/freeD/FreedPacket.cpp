#include "freeD/FreedPacket.hpp"

#include <sstream>

using namespace WorTCS;

void FreeDPacket::packetToData(const std::array<std::byte, length>& data) {
	_partialBuffer.tryToAppendNewData(data);
	if (!(_partialBuffer.completed() && _partialBuffer.valid())) {
		return;
	}
	CameraData newCameraData;
	newCameraData.rotation.z = bytesToAngles(_partialBuffer.packet()[2],
											 _partialBuffer.packet()[3],
											 _partialBuffer.packet()[4]);
	newCameraData.rotation.y = bytesToAngles(_partialBuffer.packet()[5],
											 _partialBuffer.packet()[6],
											 _partialBuffer.packet()[7]);
	newCameraData.rotation.x = bytesToAngles(_partialBuffer.packet()[8],
											 _partialBuffer.packet()[9],
											 _partialBuffer.packet()[10]);
	newCameraData.position.x = bytesToLocation(_partialBuffer.packet()[11],
											   _partialBuffer.packet()[12],
											   _partialBuffer.packet()[13]);
	newCameraData.position.y = bytesToLocation(_partialBuffer.packet()[14],
											   _partialBuffer.packet()[15],
											   _partialBuffer.packet()[16]);
	newCameraData.position.z = bytesToLocation(_partialBuffer.packet()[17],
											   _partialBuffer.packet()[18],
											   _partialBuffer.packet()[19]);
	newCameraData.zoom = bytesToLens(_partialBuffer.packet()[20],
									 _partialBuffer.packet()[21],
									 _partialBuffer.packet()[22]);
	newCameraData.focus = bytesToLens(_partialBuffer.packet()[23],
									  _partialBuffer.packet()[24],
									  _partialBuffer.packet()[25]);
	_cameraData = newCameraData;
}

float FreeDPacket::bytesToAngles(std::byte a_, std::byte b_, std::byte c_) const noexcept {
	/// Pre-cast to simple coding
	const int a = static_cast<int>(a_);
	const int b = static_cast<int>(b_);
	const int c = static_cast<int>(c_);

	const bool negativeSign = (a & 0b10000000) > 0;
	float value;

	if (_cameraData.useFracture) {
		float fracPart;
		int intPart;
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

float FreeDPacket::bytesToLocation(std::byte a_, std::byte b_, std::byte c_) const noexcept {
	/// Pre-cast to simple coding
	const int a = static_cast<int>(a_);
	const int b = static_cast<int>(b_);
	const int c = static_cast<int>(c_);

	const bool negativeSign = (a & 0b10000000) > 0;
	float value;

	if (_cameraData.useFracture) {
		float fracPart;
		int intPart;
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

int FreeDPacket::bytesToLens(std::byte a_, std::byte b_, std::byte c_) const noexcept {
	if (_cameraData.useFracture) {
		return static_cast<int>((b_ << 8) | c_);
	}
	const bool sign = (static_cast<int>(a_) & 0b10000000) > 0;
	int temp = static_cast<int>((a_ << 16) | (b_ << 8) | c_);

	if (sign) {
		temp = (~temp) & 0b111111111111111111111111;
	}
	return sign ? -temp : temp;
}

#pragma region Accessors/Mutators

const CameraData& FreeDPacket::cameraData() const noexcept {
	return _cameraData;
}

bool FreeDPacket::useFracture() const noexcept {
	return _cameraData.useFracture;
}

void FreeDPacket::useFracture(bool fracture_) noexcept {
	_cameraData.useFracture = fracture_;
}

const std::array<std::byte, FreeDPacket::length>& FreeDPacket::rawBuffer() const noexcept {
	return _partialBuffer.packet();
}

std::string FreeDPacket::str(StrView strViewFlag) const noexcept {
	std::stringstream ss;
	ss << "\nCompleted camera data:";
	if (strViewFlag & StrView::Pos) {
		ss << "\n\tPosition: "
				<< "\n\t\tx: " << _cameraData.position.x
				<< "\n\t\ty: " << _cameraData.position.y
				<< "\n\t\tz: " << _cameraData.position.z;
	}
	if (strViewFlag & StrView::Rot) {
		ss << "\n\tRotation: "
				<< "\n\t\trx: " << _cameraData.rotation.x
				<< "\n\t\try: " << _cameraData.rotation.y
				<< "\n\t\trz: " << _cameraData.rotation.z;
	}
	if (strViewFlag & StrView::Lens) {
		ss << "\n\tLens: "
				<< "\n\t\tfocus: " << _cameraData.focus
				<< "\n\t\tzoom: " << _cameraData.zoom;
	}
	return ss.str();
}

#pragma endregion Accessors/Mutators

FreeDPacket::StrView WorTCS::operator|(FreeDPacket::StrView lhs, FreeDPacket::StrView rhs) noexcept {
	return static_cast<FreeDPacket::StrView>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

bool WorTCS::operator&(FreeDPacket::StrView lhs, FreeDPacket::StrView rhs) noexcept {
	return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));
}
