#include "DllMethods.h"

int main() {
    const DllHandle h("libTrackingCameraSpeaker_DLL.dll");
    if (!h.Get()) {
        MessageBox(nullptr, "Can't load DLL", "UnitCallDll", MB_OK);
        return 1;
    }

#pragma region DllMethods
    IMPORT_METHOD(initializeSpeaker, m_initializeSpeaker)
    IMPORT_METHOD(deinitializeSpeaker, m_deinitializeSpeaker)
    IMPORT_METHOD(startReader, m_startReader)
    IMPORT_METHOD(stopReader, m_stopReader)
    IMPORT_METHOD(getRx, m_getRx)
    IMPORT_METHOD(getRy, m_getRy)
    IMPORT_METHOD(getRz, m_getRz)
    IMPORT_METHOD(getX, m_getX)
    IMPORT_METHOD(getY, m_getY)
    IMPORT_METHOD(getZ, m_getZ)
    IMPORT_METHOD(getZoom, m_getZoom)
    IMPORT_METHOD(getFocus, m_getFocus)
    IMPORT_METHOD(getServerActivity, m_getServerActivity)
    IMPORT_METHOD(getSpeakerActivity, m_getSpeakerActivity)
#pragma endregion DllMethods

    if (!initializeSpeaker()) {
        MessageBox(nullptr, "Can't initialize Speaker", "UnitCallDll", MB_OK);
        return 0;
    }
    if (!startReader("127.0.0.1", 6301)) {
        MessageBox(nullptr, "Can't open socket", "UnitCallDll", MB_OK);
        return 0;
    }
    float t = getRx();
    stopReader();
    deinitializeSpeaker();

    return 1;
}
