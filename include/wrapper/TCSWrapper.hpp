#pragma once

/**
 * This files (wrapper\\*.hpp and wrapper\\*.cpp) show simple way to use only dll with directly dllImport via WinAPI.
 * U can override export/import functions as u want.
 * I don't recommend u to do this, but this is good idea to secure your class declaration and export just management
 * function, that work with Speaker handle and just .dll file, without all the rest.
 * Example of import directly exported .dll see in file DllMethods.h, that describe all function to import.
 * Remember that directly export must have only C-types data or u must describe all extra structs in import space.
 * Don't forget change CMake file to export only directly function.
 * In big project prefer full import/export(install version *.lib + *.dll and all *.hpp pack).
 */

#include "speaker/TrackingCameraSpeaker.hpp"

extern const std::string password;
extern const std::string passwordPath;

class TCSWrapper final
        : public worTCS::TrackingCameraSpeaker {
};

TCSWrapper *ptrTCSWrapper;

#pragma region Methods to Export
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
#pragma endregion Methods to Export
