#include "TrackingCameraSpeakerWrapper.hpp"

#define CHECK_PTR(ptr) if(!ptr) return false;
#define CHECK_PTR_WITH_VAL(ptr, value) return ptr ? value : 0;

const std::string password = "CameraLikesTracking";
const std::string passwordPath = "C:/Program Files (x86)/.password";

bool initializeSpeaker() {
    CHECK_PTR(ptrWrapper)
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
    ptrWrapper = new TrackingCameraSpeakerWrapper();
    return ptrWrapper != nullptr;
}

bool deinitializeSpeaker() {
    CHECK_PTR(ptrWrapper)
    delete ptrWrapper;
    ptrWrapper = nullptr;
    return true;
}

bool setOsFlag(int flag_) {
    CHECK_PTR(ptrWrapper)
    ptrWrapper->setOsFlag(worCameraTracking::FreeDPacket::CameraDataType(flag_));
    return true;
}

bool startReader(const std::string &localAddress_, int localPort_) {
    CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->startReader(localAddress_, localPort_))
}

bool stopReader() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->stopReader()) }

float getRx() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getRx()) }

float getRy() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getRy()) }

float getRz() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getRz()) }

float getX() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getX()) }

float getY() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getY()) }

float getZ() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getZ()) }

int getZoom() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getZoom()) }

int getFocus() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getFocus()) }

bool getServerActivity() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getServerActivity()) }

bool getSpeakerActivity() { CHECK_PTR_WITH_VAL(ptrWrapper, ptrWrapper->getSpeakerActivity()) }
