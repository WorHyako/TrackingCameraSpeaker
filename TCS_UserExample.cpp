#include <spdlog/spdlog.h>
#include <Wor/Network/Utils/IoService.hpp>

#include "speaker/TrackingCameraSpeaker.hpp"
#include "Wor/Log/Log.hpp"

#include "Wor/Network/UdpClient.hpp"
#include "Wor/Network/UdpServer.hpp"

using namespace Wor;

int main() {
	Log::configureLogger();

	Network::UdpServer server;
	Network::UdpServer::Endpoint endpoint;
	endpoint.port(6001);
	auto address = boost::asio::ip::address(boost::asio::ip::make_address_v4("127.0.0.1"));
	endpoint.address(address);
	server.start(endpoint);
	if(!server.bound()) {
		return 2;
	}
	Network::Utils::IoService::run();

	const std::string targetAddress = "127.0.0.1";
	constexpr int targetPort = 6001;

	WorTCS::TrackingCameraSpeaker reader;
	if (!reader.startSpeaker(targetAddress, targetPort)) {
		return 20;
	}

	while (true) {
		const auto buffer = reader.rawBuffer();
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
		spdlog::info(ss.str());
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	return 0;
}
