#ifndef TRACKINGCAMERASPEAKER_TRACKINGCAMERASPEAKERWRAPPER_HPP
#define TRACKINGCAMERASPEAKER_TRACKINGCAMERASPEAKERWRAPPER_HPP

#include "../TrackingSpeaker.hpp"

#include <fstream>

extern const std::string password;
extern const std::string passwordPath;

class TrackingCameraSpeakerWrapper final
        : public worCameraTracking::TrackingSpeaker {

};

worCameraTracking::TrackingSpeaker *ptrWrapper;

#pragma region Methods to export
extern "C" {
__declspec(dllexport) bool initializeSpeaker();

__declspec(dllexport) bool deinitializeSpeaker();

__declspec(dllexport) bool setOsFlag(int flag_);

__declspec(dllexport) bool startReader(const std::string &localAddress_, int localPort_);

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

int WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // well, let's go
            break;
        case DLL_PROCESS_DETACH:
            if (!ptrWrapper) {
                break;
            }
            if (ptrWrapper->getServerActivity()) {
                ptrWrapper->stopReader();
            }
            delete ptrWrapper;
            break;
        default:
            break;
    }
    return 0;
}

#endif
