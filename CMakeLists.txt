cmake_minimum_required(VERSION 3.22)
project(TrackingCameraSpeaker)
set(CMAKE_CXX_STANDARD 14)

list(APPEND worTS_inc_dirs
        worTrackingSpeaker/include/FreeD
        worTrackingSpeaker/include/Socket)

list(APPEND worTS_src_dirs
        worTrackingSpeaker/src/FreeD
        worTrackingSpeaker/src/Socket)

list(APPEND worTS_src
        worTrackingSpeaker/src/FreeD/CameraData.cpp
        worTrackingSpeaker/src/FreeD/FreedPacket.cpp
        worTrackingSpeaker/src/FreeD/PartialBuffer.cpp
        worTrackingSpeaker/src/Socket/BaseSocket.cpp
        worTrackingSpeaker/src/Socket/ServerUdpSocket.cpp
        worTrackingSpeaker/src/Socket/ServerDependencies.cpp)

list(APPEND worTS_inc
        worTrackingSpeaker/include/FreeD/CameraData.hpp
        worTrackingSpeaker/include/FreeD/PartialBuffer.hpp
        worTrackingSpeaker/include/FreeD/FreedPacket.hpp
        worTrackingSpeaker/include/Socket/BaseSocket.hpp
        worTrackingSpeaker/include/Socket/ServerUdpSocket.hpp
        worTrackingSpeaker/include/Socket/ServerDependencies.hpp)

include_directories(${worTS_inc_dirs} ${worTS_src_dirs})

add_executable(TrackingCameraSpeaker TCS_UserExample.cpp
        TrackingSpeaker.cpp TrackingSpeaker.hpp ${worTS_inc} ${worTS_src})

target_link_libraries(TrackingCameraSpeaker ws2_32)
target_link_libraries(TrackingCameraSpeaker iphlpapi.lib)
