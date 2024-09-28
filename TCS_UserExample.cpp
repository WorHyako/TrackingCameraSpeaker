#include "speaker/TrackingCameraSpeaker.hpp"

#include "Wor/Log/Log.hpp"
#include "Wor/Network/Utils/IoService.hpp"
#include "Wor/Network/UdpServer.hpp"

using namespace Wor;

int main() {
	Log::configureLogger();

	/**
	 * Pseudo local server.
	 */
	Network::UdpServer server;
	Network::UdpServer::Endpoint endpoint;
	endpoint.port(6001);
	auto address = boost::asio::ip::address(boost::asio::ip::make_address_v4("127.0.0.1"));
	endpoint.address(address);
	server.start(endpoint);
	if (!server.bound()) {
		return 2;
	}
	/**
	 * Speaker part.
	 */
	constexpr std::string_view targetAddress{"127.0.0.1"};
	constexpr std::uint16_t targetPort{6001};

	WorTCS::TrackingCameraSpeaker reader;
	if (!reader.startSpeaker(targetAddress.data(), targetPort)) {
		return 20;
	}

	Network::Utils::IoService::run();

	while (true) {
		const auto buffer{reader.rawBuffer()};
		std::stringstream ss;
		ss << "\nCurrent data:";
		ss << "\n\tRaw buffer: ";
		std::for_each(std::begin(buffer),
					  std::end(buffer),
					  [&ss](std::byte byte) {
						  ss << std::hex << static_cast<std::uint8_t>(byte);
					  });
		ss << "\n\tData: ";
		ss << reader.str(WorTCS::FreeDPacket::StrView::Rot
						 | WorTCS::FreeDPacket::StrView::Pos
						 | WorTCS::FreeDPacket::StrView::Lens);
		worInfo(ss.str());
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	return 0;
}
