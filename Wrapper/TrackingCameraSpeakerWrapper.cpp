#include "TrackingCameraSpeakerWrapper.h"

#define CHECK_PTR(ptr) if(!ptr) return false;
#define CHECK_PTR_WITH_VAL(ptr, value) return ptr ? value : 0;

namespace worLib {
    const std::string password = "CameraLikesTracking";
    const std::string password_path = "C:/Program Files (x86)/.password";
}

bool initializeSpeaker() {
    if (ptr_wrapper) return false;
    // Simple way to set password. U can just delete this part and initialize speaker right away
    std::ifstream in_stream;
    in_stream.open(worLib::password_path);
    if (in_stream.is_open()) {
        std::string line;
        std::getline(in_stream, line);
        // Or read ONE WORD. NOT line, just ONE WORD:
        // in_stream >> line;
        if (line != worLib::password)
            return false;
    } else {
        in_stream.close();
        return false;
    }
    in_stream.close();
    ptr_wrapper = new worLib::TrackingCameraSpeakerWrapper();
    return ptr_wrapper != nullptr;
}

bool deinitializeSpeaker() {
    CHECK_PTR(ptr_wrapper)
    delete ptr_wrapper;
    ptr_wrapper = nullptr;
    return true;
}

bool setOsFlag(int flag) {
    CHECK_PTR(ptr_wrapper)
    ptr_wrapper->setOsFlag(worLib::FreeDPacket::camera_data_type(flag));
    return true;
}

bool startReader(const std::string &local_address, int local_port) {
    CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->startReader(local_address, local_port))
}

bool stopReader() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->stopReader()) }

float getRx() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getRx()) }

float getRy() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getRy()) }

float getRz() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getRz()) }

float getX() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getX()) }

float getY() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getY()) }

float getZ() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getZ()) }

int getZoom() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getZoom()) }

int getFocus() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getFocus()) }

bool getServerActivity() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getServerActivity()) }

bool getSpeakerActivity() { CHECK_PTR_WITH_VAL(ptr_wrapper, ptr_wrapper->getSpeakerActivity()) }
