#include <spdlog/spdlog.h>

#include "speaker/TrackingCameraSpeaker.hpp"

int main() {
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
