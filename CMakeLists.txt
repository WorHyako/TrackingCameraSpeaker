cmake_minimum_required(VERSION 3.22)

project(WorTCS
        VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################
#  ThirdParty  #
################
add_subdirectory(ThirdParty)

# Configure link and compile process #
if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()
set(CMAKE_DEBUG_POSTFIX d)

file(GLOB Source src/freeD/*.cpp)
list(APPEND Sources ${Source})
file(GLOB Source src/socket/*.cpp)
list(APPEND Sources ${Source})
file(GLOB Source src/speaker/*.cpp)
list(APPEND Sources ${Source})

add_library(WorTCS)
add_library(Wor::TCS ALIAS WorTCS)
target_sources(WorTCS
        PRIVATE ${Sources})
target_include_directories(WorTCS
        PUBLIC include)
target_link_libraries(WorTCS
        PUBLIC
        Wor::Network
        Wor::Math
        Wor::Log)

# ---------------------------------------- #
# Project to check TCS as internal source  #
# ---------------------------------------- #
add_executable(WorTCS_ExeTest)
target_sources(WorTCS_ExeTest
        PRIVATE TCS_UserExample.cpp)
target_link_libraries(WorTCS_ExeTest
        PRIVATE Wor::TCS)
