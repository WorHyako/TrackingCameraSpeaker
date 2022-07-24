#ifndef TRACKINGCAMERASPEAKER_TRACKINGCAMERASPEAKERWRAPPER_H
#define TRACKINGCAMERASPEAKER_TRACKINGCAMERASPEAKERWRAPPER_H

#include "../TrackingSpeaker.h"

#include <fstream>

namespace worLib {

    extern const std::string password;
    extern const std::string password_path;

    class TrackingCameraSpeakerWrapper
            : public TrackingSpeaker {

    };
}

worLib::TrackingSpeaker *ptr_wrapper;

#pragma region Methods to export
extern "C" {

__declspec(dllexport) bool initializeSpeaker();

__declspec(dllexport) bool deinitializeSpeaker();

__declspec(dllexport) bool setOsFlag(int flag);

__declspec(dllexport) bool startReader(const std::string &local_address, int local_port);

__declspec(dllexport) bool stopReader();

__declspec(dllexport) float getRx();

__declspec(dllexport) float getRy();

__declspec(dllexport) float getRz();

__declspec(dllexport) float getX();

__declspec(dllexport) float getY();

__declspec(dllexport) float getZ();

__declspec(dllexport) int getZoom();

__declspec(dllexport) int getFocus();

__declspec(dllexport) bool getServerActivity();

__declspec(dllexport) bool getSpeakerActivity();
}
#pragma endregion Methods to export

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // well, let's go
            break;
        case DLL_PROCESS_DETACH:
            if (!ptr_wrapper) break;
            if (ptr_wrapper->getServerActivity())
                ptr_wrapper->stopReader();
            delete ptr_wrapper;
            break;
        default:
            break;
    }
    return true;
}

#endif
