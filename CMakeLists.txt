cmake_minimum_required(VERSION 3.22)
# --------------------------------------------------------------------- #
# First project TrackingCameraSpeaker to link, compile and install GAPI #
# --------------------------------------------------------------------- #
project(TrackingCameraSpeaker
        VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

set(worTCS_Include_Root include)
set(worTCS_Source_Root src)
set(worTCS_Source_FreeD ${worTCS_Source_Root}/freeD)
set(worTCS_Source_Socket ${worTCS_Source_Root}/socket)
set(worTCS_Source_Wrapper ${worTCS_Source_Root}/wrapper)
set(worTCS_Source_Speaker ${worTCS_Source_Root}/speaker)

# Vars to easily using #
list(APPEND worTCS_Sources
        ${worTCS_Source_FreeD}/CameraData.cpp
        ${worTCS_Source_FreeD}/FreedPacket.cpp
        ${worTCS_Source_FreeD}/PartialBuffer.cpp
        ${worTCS_Source_Socket}/BaseSocket.cpp
        ${worTCS_Source_Socket}/ServerUdpSocket.cpp
        ${worTCS_Source_Socket}/ServerDependencies.cpp
        ${worTCS_Source_Socket}/SocketInfo.cpp
        ${worTCS_Source_Speaker}/TrackingCameraSpeaker.cpp
        ${worTCS_Source_Root}/DllEntryPoint.cpp
        )
# ------------------------------------------------------------------------------------------ #
# If u want to directly export via WinAPI functions entry point with just TCSSpeaker handle, #
# uncomment lines 32-33 of code and comment all the rest                                     #
# ------------------------------------------------------------------------------------------ #
#add_library(worTrackingSpeaker STATIC ${worTS_src}
#        ${worTCS_Source_Wrapper}/TCSWrapper.cpp)

# Configure link and compile process #
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_DEBUG_POSTFIX d)
add_library(TrackingCameraSpeaker STATIC SHARED)
target_sources(TrackingCameraSpeaker PRIVATE ${worTCS_Sources} ${worTCS_Source_Root}/DllEntryPoint.cpp)
target_include_directories(TrackingCameraSpeaker PUBLIC ${worTCS_Include_Root})
target_link_libraries(TrackingCameraSpeaker ws2_32)
target_link_libraries(TrackingCameraSpeaker iphlpapi.lib)

# ------------ #
# Install part #
# ------------ #

# ---------------------------------------- #
# Project to check TCS as external module  #
# ---------------------------------------- #

# ---------------------------------------- #
# Project to check TCS as internal source  #
# ---------------------------------------- #