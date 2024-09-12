cmake_minimum_required(VERSION 3.22)

project(worTCS_DLL
        VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################
#  ThirdParty  #
################
add_subdirectory(ThirdParty)

file(GLOB Source src/freeD/*.cpp)
list(APPEND Sources ${Source})
file(GLOB Source src/socket/*.cpp)
list(APPEND Sources ${Source})
file(GLOB Source src/speaker/*.cpp)
list(APPEND Sources ${Source})

# ------------------------------------------------------------------------------------------ #
# If u want to directly export via WinAPI functions entry point with just TCSSpeaker handle, #
# uncomment lines 32-33 of code and comment all the rest                                     #
# ------------------------------------------------------------------------------------------ #
#add_library(worTCS STATIC ${worTS_src}
#        src/wrapper/TCSWrapper.cpp)

# Configure link and compile process #
if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()
set(CMAKE_DEBUG_POSTFIX d)

add_library(worTCS)
target_sources(worTCS
        PRIVATE ${Sources})
target_include_directories(worTCS
        PUBLIC include)
target_link_libraries(worTCS
        PRIVATE
        Wor::Network
        Wor::Math)

# Next project usually locate at another projects

# ---------------------------------------- #
# Project to check TCS as external module  #
# ---------------------------------------- #
#project(worTCS_DllTest)
#set(CMAKE_CXX_STANDARD 17)
#
#set(worTCS_DIR C:/bibles/worTCS)
#find_package(worTCS)
#
#add_executable(worTCS_DllTest TCS_UserExample.cpp)
#target_link_libraries(worTCS_DllTest worTCS)
#
# ---------------------------------------- #
# Project to check TCS as internal source  #
# ---------------------------------------- #
#project(worTCS_ExeTest)
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(worTCS_ExeTest TCS_UserExample.cpp ${worTCS_Sources})
#target_link_libraries(worTCS_ExeTest ws2_32 iphlpapi.lib)
#target_include_directories(worTCS_ExeTest PUBLIC ${worTCS_Include_Root})
