cmake_minimum_required(VERSION 3.22)
# --------------------------------------------------------------------- #
# First project TrackingCameraSpeaker to link, compile and install GAPI #
# --------------------------------------------------------------------- #
#project(worTCS_DLL
#        VERSION 1.0.0)
#set(CMAKE_CXX_STANDARD 17)
#
#set(worTCS_Include_Root include)
#set(worTCS_Source_Root src)
#set(worTCS_Source_FreeD ${worTCS_Source_Root}/freeD)
#set(worTCS_Source_Socket ${worTCS_Source_Root}/socket)
#set(worTCS_Source_Wrapper ${worTCS_Source_Root}/wrapper)
#set(worTCS_Source_Speaker ${worTCS_Source_Root}/speaker)
#
## Vars to easily using #
#list(APPEND worTCS_Sources
#        ${worTCS_Source_FreeD}/CameraData.cpp
#        ${worTCS_Source_FreeD}/FreedPacket.cpp
#        ${worTCS_Source_FreeD}/PartialBuffer.cpp
#        ${worTCS_Source_Socket}/BaseSocket.cpp
#        ${worTCS_Source_Socket}/ServerUdpSocket.cpp
#        ${worTCS_Source_Socket}/ServerDependencies.cpp
#        ${worTCS_Source_Socket}/SocketInfo.cpp
#        ${worTCS_Source_Speaker}/TrackingCameraSpeaker.cpp
#        )
## ------------------------------------------------------------------------------------------ #
## If u want to directly export via WinAPI functions entry point with just TCSSpeaker handle, #
## uncomment lines 32-33 of code and comment all the rest                                     #
## ------------------------------------------------------------------------------------------ #
##add_library(worTCS STATIC ${worTS_src}
##        ${worTCS_Source_Wrapper}/TCSWrapper.cpp)
#
## Configure link and compile process #
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#set(CMAKE_DEBUG_POSTFIX d)
#add_library(worTCS STATIC SHARED)
#target_sources(worTCS PRIVATE ${worTCS_Sources} ${worTCS_Source_Root}/DllEntryPoint.cpp)
#target_include_directories(worTCS PUBLIC ${worTCS_Include_Root})
#target_link_libraries(worTCS ws2_32 iphlpapi.lib)
#
## ------------ #
## Install part #
## ------------ #
#set(CMAKE_INSTALL_PREFIX C:/bibles)
#set(Install_Folder worTCS)
#set(Include_Root_Include_Folder ${Install_Folder}/include)
#install(TARGETS worTCS DESTINATION ${Install_Folder}
#        RUNTIME DESTINATION ${Install_Folder}/bin
#        ARCHIVE DESTINATION ${Install_Folder}/bin
#        )
#list(APPEND Install_Includes_Filters
#        ${worTCS_Include_Root}/freeD/*.hpp
#        ${worTCS_Include_Root}/socket/*.hpp
#        ${worTCS_Include_Root}/speaker/*.hpp
#        ${worTCS_Include_Root}/vector/*.hpp
#        )
#file(GLOB_RECURSE list ${CMAKE_CURRENT_SOURCE_DIR} ${Install_Includes_Filters})
#foreach (Each_File ${list})
#    file(RELATIVE_PATH Each_File_Rel_Path ${CMAKE_CURRENT_SOURCE_DIR}/${worTCS_Include_Root} ${Each_File})
#    list(APPEND Install_Includes ${Each_File_Rel_Path})
#endforeach (Each_File)
#
#foreach (Each_Include_File ${Install_Includes})
#    get_filename_component(File_Path ${Each_Include_File} PATH)
#    install(FILES ${worTCS_Include_Root}/${Each_Include_File} DESTINATION ${Include_Root_Include_Folder}/${File_Path})
#endforeach (Each_Include_File)
#
#install(FILES worTCSConfig.cmake DESTINATION ${Install_Folder})


# Next project usually locate at another projects

# ---------------------------------------- #
# Project to check TCS as external module  #
# ---------------------------------------- #
project(worTCS_DllTest)
set(CMAKE_CXX_STANDARD 17)

set(worTCS_DIR C:/bibles/worTCS)
find_package(worTCS)

add_executable(worTCS_DllTest TCS_UserExample.cpp)
target_link_libraries(worTCS_DllTest worTCS)

# ---------------------------------------- #
# Project to check TCS as internal source  #
# ---------------------------------------- #
#project(worTCS_ExeTest)
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(worTCS_ExeTest TCS_UserExample.cpp ${worTCS_Sources})
#target_link_libraries(worTCS_ExeTest ws2_32 iphlpapi.lib)
#target_include_directories(worTCS_ExeTest PUBLIC ${worTCS_Include_Root})
