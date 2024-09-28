#include "freeD/PartialBuffer.hpp"

using namespace WorTCS;

PartialBuffer::PartialBuffer() noexcept
	: _deltaByte(0),
	  _packetValid(false),
	  _packetComplete(true) {
	_packet.fill(static_cast<std::byte>(0x00));
}

void PartialBuffer::tryToAppendNewData(const std::array<std::byte, length>& newData) {
	if (*std::begin(newData) == static_cast<std::byte>(0xD1)) {
		std::copy(std::begin(newData), std::end(newData), std::begin(_packet));
		_packetComplete = true;

		_packetValid = checkChecksum(_packet);
	}

	if (!_packetComplete && _deltaByte) {
		for (int i{0}; i < _deltaByte; i++) {
			_packet[i + (_packet.size() - _deltaByte)] = newData[i];
		}

		_packetComplete = checkChecksum(_packet);
	}

	std::uint16_t index{1};
	for (auto it{std::begin(newData) + 1}; it < std::end(newData); it++, index++) {
		if (static_cast<int>(*it) != 0xD1) {
			continue;
		}
		_deltaByte = index;
		std::size_t bufferIndex;
		std::uint16_t newDataIndex;
		for (newDataIndex = index, bufferIndex = 0; newDataIndex < newData.size(); newDataIndex++, bufferIndex++) {
			_packet[bufferIndex] = newData[newDataIndex];
		}
		for (; bufferIndex < _packet.size(); bufferIndex++) {
			_packet[bufferIndex] = static_cast<std::byte>(0x00);
		}
		_packetComplete = false;
		break;
	}
}

bool PartialBuffer::checkChecksum(const std::array<std::byte, length>& byteArray) const {
	int checksum{0x40};
	std::for_each(std::begin(byteArray),
				  std::end(byteArray),
				  [&checksum](std::byte byte) {
					  checksum -= static_cast<int>(byte);
				  });

	while (checksum < 0) {
		checksum += 256;
	}
	return checksum == static_cast<int>(*(std::end(byteArray) - 1));
}

#pragma region Accessors/Mutators

bool PartialBuffer::valid() const noexcept {
	return _packetValid;
}

const std::array<std::byte, PartialBuffer::length>& PartialBuffer::packet() const noexcept {
	return _packet;
}

bool PartialBuffer::completed() const noexcept {
	return _packetComplete;
}

#pragma endregion Accessors/Mutators
