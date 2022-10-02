#include "TrackingSpeaker.hpp"

int main() {
    std::string targetAddress = "127.0.0.1";

    worCameraTracking::TrackingSpeaker reader;
    if(!reader.startSpeaker(targetAddress, 6001))
    {
        return -1;
    }
    if (worCameraTracking::BaseSocket::checkEndPoint(targetAddress)) {
        int k = 0;
        while (k < 5) {
            reader.setOsFlag(worCameraTracking::FreeDPacket::CameraDataType::LOC_ROT);
            for (auto each : reader.getBuffer()) {
                std::cout << std::hex << "_" << (int) each;
            }
            std::cout << "\n-----------------------------\n";
            Sleep(500);
            k++;
        }
    }
    return 0;
}
