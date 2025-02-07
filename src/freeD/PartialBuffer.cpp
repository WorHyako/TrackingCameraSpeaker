#include "freeD/PartialBuffer.hpp"

using namespace WorTCS;

PartialBuffer::PartialBuffer() noexcept
	: _packet{},
	  _delta_byte{0},
	  _packet_valid{false},
	  _packet_complete{true} {
	_packet.fill(static_cast<std::byte>(0x00));
}

void PartialBuffer::tryToAppendNewData(const std::array<std::byte, length>& new_data) {
	if (*std::begin(new_data) == static_cast<std::byte>(0xD1)) {
		std::copy(std::begin(new_data), std::end(new_data), std::begin(_packet));
		_packet_complete = true;

		_packet_valid = checkChecksum(_packet);
	}

	if (!_packet_complete && _delta_byte) {
		for (int i{0}; i < _delta_byte; i++) {
			_packet[i + (std::size(_packet) - _delta_byte)] = new_data[i];
		}

		_packet_complete = checkChecksum(_packet);
	}

	std::uint16_t index{1};
	for (auto it{std::begin(new_data) + 1}; it < std::end(new_data); it++, index++) {
		if (static_cast<int>(*it) != 0xD1) {
			continue;
		}
		_delta_byte = index;
		std::size_t buffer_index;
		std::uint16_t new_data_index;
		for (new_data_index = index, buffer_index = 0; new_data_index < std::size(new_data); new_data_index++,
			 buffer_index++) {
			_packet[buffer_index] = new_data[new_data_index];
		}
		for (; buffer_index < std::size(_packet); buffer_index++) {
			_packet[buffer_index] = static_cast<std::byte>(0x00);
		}
		_packet_complete = false;
		break;
	}
}

bool PartialBuffer::checkChecksum(const std::array<std::byte, length>& byte_array) const {
	int checksum{0x40};
	std::for_each(std::begin(byte_array),
				  std::end(byte_array),
				  [&checksum](std::byte byte) {
					  checksum -= static_cast<int>(byte);
				  });

	while (checksum < 0) {
		checksum += 256;
	}
	return checksum == static_cast<int>(*(std::end(byte_array) - 1));
}

#pragma region Accessors/Mutators

bool PartialBuffer::valid() const noexcept {
	return _packet_valid;
}

const std::array<std::byte, PartialBuffer::length>& PartialBuffer::packet() const noexcept {
	return _packet;
}

bool PartialBuffer::completed() const noexcept {
	return _packet_complete;
}

#pragma endregion Accessors/Mutators
