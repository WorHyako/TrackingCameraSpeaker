cmake_minimum_required(VERSION 3.22)

project(worTrackingSpeaker VERSION 1.0.1 DESCRIPTION "mylib description")

set(CMAKE_CXX_STANDARD 14)

list(APPEND worTS_src
        src/FreeD/CameraData.cpp
        src/FreeD/FreedPacket.cpp
        src/FreeD/PartialBuffer.cpp
        src/Socket/BaseSocket.cpp
        src/Socket/ServerUdpSocket.cpp)

list(APPEND worTS_inc
        include/FreeD/CameraData.hpp
        include/FreeD/PartialBuffer.hpp
        include/FreeD/FreedPacket.hpp
        include/Socket/BaseSocket.hpp
        include/Socket/ServerUdpSocket.hpp)

list(APPEND worTS_inc_dirs
        include/FreeD
        include/Socket)

list(APPEND worTS_src_dirs
        src/FreeD
        src/Socket)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(VAR gerg)

include(GNUInstallDirs)

include_directories(${worTS_inc_dirs})

add_library(worTrackingSpeaker STATIC ${worTS_src})

target_include_directories(worTrackingSpeaker PRIVATE ${worTS_inc_dirs})

