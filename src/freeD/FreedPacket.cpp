#include "freeD/FreedPacket.hpp"

#include <sstream>

using namespace WorTCS;

void FreeDPacket::packetToData(const std::array<std::byte, length>& data) {
	_partial_buffer.tryToAppendNewData(data);
	if (!(_partial_buffer.completed() && _partial_buffer.valid())) {
		return;
	}
	CameraData new_camera_data;
	new_camera_data.rotation.z = bytesToAngles(_partial_buffer.packet()[2],
											   _partial_buffer.packet()[3],
											   _partial_buffer.packet()[4]);
	new_camera_data.rotation.y = bytesToAngles(_partial_buffer.packet()[5],
											   _partial_buffer.packet()[6],
											   _partial_buffer.packet()[7]);
	new_camera_data.rotation.x = bytesToAngles(_partial_buffer.packet()[8],
											   _partial_buffer.packet()[9],
											   _partial_buffer.packet()[10]);
	new_camera_data.position.x = bytesToLocation(_partial_buffer.packet()[11],
												 _partial_buffer.packet()[12],
												 _partial_buffer.packet()[13]);
	new_camera_data.position.y = bytesToLocation(_partial_buffer.packet()[14],
												 _partial_buffer.packet()[15],
												 _partial_buffer.packet()[16]);
	new_camera_data.position.z = bytesToLocation(_partial_buffer.packet()[17],
												 _partial_buffer.packet()[18],
												 _partial_buffer.packet()[19]);
	new_camera_data.zoom = bytesToLens(_partial_buffer.packet()[20],
									   _partial_buffer.packet()[21],
									   _partial_buffer.packet()[22]);
	new_camera_data.focus = bytesToLens(_partial_buffer.packet()[23],
										_partial_buffer.packet()[24],
										_partial_buffer.packet()[25]);
	_camera_data = new_camera_data;
}

float FreeDPacket::bytesToAngles(std::byte a_, std::byte b_, std::byte c_) const noexcept {
	/// Pre-cast to simple coding
	const int a{static_cast<int>(a_)};
	const int b{static_cast<int>(b_)};
	const int c{static_cast<int>(c_)};

	const bool negative_sign{(a & 0b10000000) > 0};
	float value;

	if (_camera_data.use_fracture) {
		float frac_part;
		int int_part;
		if (negative_sign) {
			int_part = ((~a & 0b01111111) << 1) | ((~b & 0b10000000) >> 7);
			frac_part =
					static_cast<float>((((b & 0b01111111) << 8) | c) & 0b0111111111111111) / 0b0111111111111111;
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

float FreeDPacket::bytesToLocation(std::byte a_, std::byte b_, std::byte c_) const noexcept {
	/// Pre-cast to simple coding
	const int a{static_cast<int>(a_)};
	const int b{static_cast<int>(b_)};
	const int c{static_cast<int>(c_)};

	const bool negative_sign = (a & 0b10000000) > 0;
	float value;

	if (_camera_data.use_fracture) {
		float frac_part;
		int int_part;
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
		if (negative_sign) {
			temp = (~temp) & 0b011111111111111111111111;
		}
		value = static_cast<float>(temp) / 64.0f;
	}
	return negative_sign ? -value : value;
}

int FreeDPacket::bytesToLens(std::byte a, std::byte b, std::byte c) const noexcept {
	if (_camera_data.use_fracture) {
		return static_cast<int>((b << 8) | c);
	}
	const bool sign{(static_cast<int>(a) & 0b10000000) > 0};
	int temp{static_cast<int>((a << 16) | (b << 8) | c)};

	if (sign) {
		temp = (~temp) & 0b111111111111111111111111;
	}
	return sign ? -temp : temp;
}

#pragma region Accessors/Mutators

const CameraData& FreeDPacket::cameraData() const noexcept {
	return _camera_data;
}

bool FreeDPacket::useFracture() const noexcept {
	return _camera_data.use_fracture;
}

void FreeDPacket::useFracture(bool fracture_) noexcept {
	_camera_data.use_fracture = fracture_;
}

const std::array<std::byte, FreeDPacket::length>& FreeDPacket::rawBuffer() const noexcept {
	return _partial_buffer.packet();
}

std::string FreeDPacket::str(StrView str_view_flag) const noexcept {
	std::stringstream ss;
	if (str_view_flag & StrView::Pos) {
		ss << "Position: "
				<< "\n\tx: " << _camera_data.position.x
				<< "\n\ty: " << _camera_data.position.y
				<< "\n\tz: " << _camera_data.position.z;
	}
	if (str_view_flag & StrView::Rot) {
		ss << "\nRotation: "
				<< "\n\trx: " << _camera_data.rotation.x
				<< "\n\try: " << _camera_data.rotation.y
				<< "\n\trz: " << _camera_data.rotation.z;
	}
	if (str_view_flag & StrView::Lens) {
		ss << "\nLens: "
				<< "\n\tfocus: " << _camera_data.focus
				<< "\n\tzoom: " << _camera_data.zoom;
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
