cmake_minimum_required(VERSION 3.22)
project(TrackingCameraSpeaker)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrackingCameraSpeaker TCS_UserExample.cpp
        lib/FreeD/CameraData.cpp lib/FreeD/CameraData.hpp
        lib/FreeD/FreedPacket.cpp lib/FreeD/FreedPacket.hpp
        lib/FreeD/PartialBuffer.cpp lib/FreeD/PartialBuffer.hpp
        lib/Socket/BaseSocket.cpp lib/Socket/BaseSocket.hpp
        lib/Socket/ServerUdpSocket.cpp lib/Socket/ServerUdpSocket.hpp
        TrackingSpeaker.cpp TrackingSpeaker.h)

target_link_libraries(TrackingCameraSpeaker ws2_32)
target_link_libraries(TrackingCameraSpeaker iphlpapi.lib)

add_executable(TrackingCameraSpeaker_DLLUserExample TCSDll_UserExample.cpp
        DllMethods.h)

add_library(TrackingCameraSpeaker_DLL MODULE
        lib/FreeD/CameraData.cpp lib/FreeD/CameraData.hpp
        lib/FreeD/FreedPacket.cpp lib/FreeD/FreedPacket.hpp
        lib/FreeD/PartialBuffer.cpp lib/FreeD/PartialBuffer.hpp
        lib/Socket/BaseSocket.cpp lib/Socket/BaseSocket.hpp
        lib/Socket/ServerUdpSocket.cpp lib/Socket/ServerUdpSocket.hpp
        TrackingSpeaker.cpp TrackingSpeaker.h
        Wrapper/TrackingCameraSpeakerWrapper.cpp Wrapper/TrackingCameraSpeakerWrapper.hpp)

target_link_libraries(TrackingCameraSpeaker_DLL ws2_32)
target_link_libraries(TrackingCameraSpeaker_DLL iphlpapi.lib)