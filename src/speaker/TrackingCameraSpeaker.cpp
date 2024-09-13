#include "speaker/TrackingCameraSpeaker.hpp"

#include "Wor/Network/Utils/IoService.hpp"

using namespace WorTCS;
using namespace Wor;

TrackingCameraSpeaker::~TrackingCameraSpeaker() noexcept {
	stopSpeaker();
}

bool TrackingCameraSpeaker::startSpeaker(const std::string& address, std::uint16_t port) noexcept {
	boost::asio::ip::tcp::endpoint endpoint;
	endpoint.port(port);
	auto endPointAddress = boost::asio::ip::address(boost::asio::ip::make_address_v4(address));
	endpoint.address(endPointAddress);

	if (!_server->bindTo(endpoint)) {
		_server->stop();
		return false;
	}
	if (_server->start(); !_server->isRunning()) {
		return false;
	}
	_server->receiveCallback(endpoint,
							 [this](const std::string& message) {
								 parsePacket(message);
							 });

	Network::Utils::IoService::run();
	return true;
}

void TrackingCameraSpeaker::stopSpeaker() noexcept {
	if (!_server || !_server->isRunning()) {
		return;
	}

	_server->stop();
}

void TrackingCameraSpeaker::parsePacket(const std::string& message) noexcept {
	if (message.size() != FreeDPacket::length) {
		return;
	}
	std::array<std::byte, FreeDPacket::length> dataArray{};
	for (int i = 0; i < FreeDPacket::length; i++) {
		dataArray[i] = static_cast<std::byte>(message[i]);
	}

	_freedPacket.packetToData(dataArray);
}

#pragma region Accessors/Mutators

boost::asio::ip::tcp::endpoint TrackingCameraSpeaker::endPoint() const noexcept {
	if (!speakerActivity() || _server->sessionList().empty()) {
		return {};
	}
	return _server->sessionList().front().get()->endpoint();
}

bool TrackingCameraSpeaker::speakerActivity() const noexcept {
	if (!_server) {
		return false;
	}
	return _server->isRunning();
}

int TrackingCameraSpeaker::zoom() const noexcept {
	return _freedPacket.cameraData().zoom;
}

int TrackingCameraSpeaker::focus() const noexcept {
	return _freedPacket.cameraData().focus;
}

bool TrackingCameraSpeaker::useFracture() const noexcept {
	return _freedPacket.useFracture();
}

const Math::Vector::Vector3<float>& TrackingCameraSpeaker::rotation() const noexcept {
	return _freedPacket.cameraData().rotation;
}

const Math::Vector::Vector3<float>& TrackingCameraSpeaker::position() const noexcept {
	return _freedPacket.cameraData().position;
}

std::string TrackingCameraSpeaker::str(FreeDPacket::StrView strViewFlag) const noexcept {
	return _freedPacket.str(strViewFlag);
}

#pragma endregion Accessors/Mutators
