cmake_minimum_required(VERSION 3.22)
project(TrackingCameraSpeaker)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrackingCameraSpeaker TCS_UserExample.cpp
        lib/FreeD/CameraData.cpp lib/FreeD/CameraData.h
        lib/FreeD/FreedPacket.cpp lib/FreeD/FreedPacket.h
        lib/FreeD/PartialBuffer.cpp lib/FreeD/PartialBuffer.h
        lib/Socket/BaseSocket.cpp lib/Socket/BaseSocket.h
        lib/Socket/ServerUdpSocket.cpp lib/Socket/ServerUdpSocket.h
        TrackingSpeaker.cpp TrackingSpeaker.h)

target_link_libraries(TrackingCameraSpeaker ws2_32)
target_link_libraries(TrackingCameraSpeaker iphlpapi.lib)
