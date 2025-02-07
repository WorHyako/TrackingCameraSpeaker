#include "speaker/TrackingCameraSpeaker.hpp"

#include "Wor/Network/Utils/IoService.hpp"

using namespace WorTCS;
using namespace Wor;

TrackingCameraSpeaker::~TrackingCameraSpeaker() noexcept {
	stopSpeaker();
}

bool TrackingCameraSpeaker::startSpeaker(const std::string_view& address, std::uint16_t port) noexcept {
	Server::Endpoint endpoint;
	endpoint.port(port);
	boost::asio::ip::address endpoint_address{boost::asio::ip::make_address_v4(address)};
	endpoint.address(endpoint_address);

	_server = std::make_unique<Server>();
	_server->start(endpoint);
	if (!_server->bound()) {
		_server->stop();
		return false;
	}
	_server->receiveCallback(endpoint,
							 [this](const std::string_view& message) {
								 parsePacket(message);
							 });

	Network::Utils::IoService::run();
	return true;
}

void TrackingCameraSpeaker::stopSpeaker() noexcept {
	if (_server == nullptr) {
		return;
	}

	_server->stop();
}

void TrackingCameraSpeaker::parsePacket(const std::string_view& message) noexcept {
	if (message.size() != FreeDPacket::length) {
		return;
	}
	std::array<std::byte, FreeDPacket::length> data_array{};
	for (int i{0}; i < FreeDPacket::length; i++) {
		data_array[i] = static_cast<std::byte>(message[i]);
	}

	_freed_packet.packetToData(data_array);
}

#pragma region Accessors/Mutators

const std::array<std::byte, FreeDPacket::length>& TrackingCameraSpeaker::rawBuffer() const noexcept {
	return _freed_packet.rawBuffer();
}

TrackingCameraSpeaker::Server::Endpoint TrackingCameraSpeaker::endPoint() const noexcept {
	if (!speakerActivity()) {
		return {};
	}
	return _server->endpoint();
}

bool TrackingCameraSpeaker::speakerActivity() const noexcept {
	return _server || _server->bound();
}

int TrackingCameraSpeaker::zoom() const noexcept {
	return _freed_packet.cameraData().zoom;
}

int TrackingCameraSpeaker::focus() const noexcept {
	return _freed_packet.cameraData().focus;
}

bool TrackingCameraSpeaker::useFracture() const noexcept {
	return _freed_packet.useFracture();
}

const Math::Vector::Vector3<float>& TrackingCameraSpeaker::rotation() const noexcept {
	return _freed_packet.cameraData().rotation;
}

const Math::Vector::Vector3<float>& TrackingCameraSpeaker::position() const noexcept {
	return _freed_packet.cameraData().position;
}

std::string TrackingCameraSpeaker::str(FreeDPacket::StrView str_view_flag) const noexcept {
	return _freed_packet.str(str_view_flag);
}

#pragma endregion Accessors/Mutators
