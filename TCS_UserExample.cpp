#include "TrackingSpeaker.h"

using std::cout;

int main() {

    std::string targetAddress = "127.0.0.1";

    cout << "Welcome back\n";
    worLib::TrackingSpeaker reader;
    reader.startReader(targetAddress, 6001);
    if (worLib::BaseSocket::checkEndPoint(targetAddress)) {
        int k = 0;
        while (k < 100) {
            reader.setOsFlag(worLib::FreeDPacket::CameraDataType::LOC_ROT);
            cout << reader;
            cout << "\n-----------------------------\n";
            Sleep(500);
            k++;
        }
    }
    return 0;
}
