#include "wrapper/TCSWrapper.hpp"

#define CHECK_PTR(ptr) if(!ptr) return false;
#define CHECK_PTR_WITH_VAL(ptr, value) return ptr ? value : 0;

#include <fstream>

const std::string password = "CameraLikesTracking";
const std::string passwordPath = "C:/Program Files (x86)/.password";

bool initializeSpeaker() {
    CHECK_PTR(ptrTCSWrapper)
    // Simple way to set password. U can just delete this part and initialize speaker right away
    std::ifstream inStream;
    inStream.open(passwordPath);
    if (!inStream.is_open()) {
        return false;
    }
    std::string line;
    std::getline(inStream, line);
    // Or read ONE WORD. NOT line, just ONE WORD:
    // inStream >> line;
    if (line != password) {
        inStream.close();
        return false;
    }
    inStream.close();
    ptrTCSWrapper = new TCSWrapper();
    return ptrTCSWrapper != nullptr;
}

bool deinitializeSpeaker() {
    CHECK_PTR(ptrTCSWrapper)
    delete ptrTCSWrapper;
    ptrTCSWrapper = nullptr;
    return true;
}

bool setOsFlag(int flag_) {
    CHECK_PTR(ptrTCSWrapper)
    ptrTCSWrapper->setOsFlag(worTCS::FreeDPacket::CameraDataType(flag_));
    return true;
}

bool startReader(const std::string &localAddress_, int localPort_) {
    CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->startSpeaker(localAddress_, localPort_))
}

bool stopReader() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->stopSpeaker()) }

float getRx() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getRx()) }

float getRy() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getRy()) }

float getRz() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getRz()) }

float getX() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getX()) }

float getY() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getY()) }

float getZ() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getZ()) }

int getZoom() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getZoom()) }

int getFocus() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getFocus()) }

bool getSpeakerActivity() { CHECK_PTR_WITH_VAL(ptrTCSWrapper, ptrTCSWrapper->getSpeakerActivity()) }
