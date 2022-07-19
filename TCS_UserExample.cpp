#include "TrackingSpeaker.h"

int main() {

    std::string target_address = "127.0.0.1";

    using std::cout;
    using std::endl;
    cout << "Welcome back" << endl;
    worLib::TrackingSpeaker reader;
    reader.startReader(target_address, 6001);
    if (worLib::BaseSocket::checkEndPoint(target_address)) {
        int k = 0;
        while (k < 100) {
            k++;
            reader.setOsFlag(worLib::FreeDPacket::loc_rot);
            cout << reader;
            cout << endl << "-----------------------------" << endl;
            Sleep(500);
        }
    }
    return 0;
}