#include "speaker/TrackingCameraSpeaker.hpp"
#include "socket/BaseSocket.hpp"
#include "freeD/FreedPacket.hpp"

#include <iostream>

int main() {
    const std::string targetAddress = "127.0.0.1";
    constexpr int targetPort = 6001;

    worTCS::TrackingCameraSpeaker reader;
    reader.setPacketLength(29);
    reader.getServerState();
    if (!reader.startSpeaker(targetAddress, targetPort)) {
        return -1;
    }
    if (worTCS::BaseSocket::checkEndPoint(targetAddress)) {
        while (true) {
            reader.setOsFlag(worTCS::FreeDPacket::CameraDataType::LOC_ROT);
            for (auto each: reader.getBuffer()) {
                std::cout << std::hex << "\n_" << (int) each;
            }
            std::cout << "\n-----------------------------";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return 0;
}
