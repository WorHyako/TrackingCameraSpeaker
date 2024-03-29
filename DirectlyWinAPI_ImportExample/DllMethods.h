#ifndef TRACKINGCAMERASPEAKER_DLLMETHODS_H
#define TRACKINGCAMERASPEAKER_DLLMETHODS_H

/**
 * Import example directly exported .dll without all the rest.
 * Sorry about the 'define', but it looks like a pretty comfortable.
 */

#include <Windows.h>
#include <string>

#define IMPORT_METHOD(funcPtr, funcType) \
const auto funcPtr = reinterpret_cast<funcType>(GetProcAddress(h.Get(), #funcPtr));

#define IMPORT_METHOD_WITH_NAME(func_ptr, func_name, func_type) \
const auto func_ptr = reinterpret_cast<func_type>(GetProcAddress(h.Get(), func_ptr));

typedef bool (*m_startReader)(const std::string &localAddress_, int localPort_);

typedef bool (*m_stopReader)();

typedef bool (*m_initializeSpeaker)();

typedef bool (*m_deinitializeSpeaker)();

typedef float (*m_getRx)();

typedef float (*m_getRy)();

typedef float (*m_getRz)();

typedef float (*m_getX)();

typedef float (*m_getY)();

typedef float (*m_getZ)();

typedef int (*m_getZoom)();

typedef int (*m_getFocus)();

typedef bool (*m_getServerActivity)();

typedef bool (*m_getSpeakerActivity)();

struct DllHandle {
    explicit DllHandle(LPCSTR filename_)
            : handle(LoadLibrary(filename_)) {}

    ~DllHandle() {
        if (handle) {
            FreeLibrary(handle);
        }
    }

private:
    HINSTANCE handle;

public:
#pragma region Accessors

    HINSTANCE Get() const {
        return handle;
    }

#pragma endregion Accessors
};

#endif
