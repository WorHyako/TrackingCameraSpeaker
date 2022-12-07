# worTCS vars
set(worTCS_INCLUDE_DIR ${worTCS_DIR}/include)
set(worTCS_LIB_DIR ${worTCS_DIR}/bin)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(worTCS_Lib ${worTCS_LIB_DIR}/worTCSd.lib)
    set(worTCS_Dll ${worTCS_LIB_DIR}/worTCSd.dll)
elseif (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(worTCS_Lib ${worTCS_LIB_DIR}/worTCSd.lib)
    set(worTCS_Dll ${worTCS_LIB_DIR}/worTCSd.dll)
endif ()

file(COPY ${worTCS_Lib} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${worTCS_Dll} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_library(worTCS STATIC IMPORTED)
set_property(TARGET worTCS PROPERTY
        IMPORTED_LOCATION ${worTCS_Lib})
set_property(TARGET worTCS PROPERTY
        IMPORTED_IMPLIB ${worTCS_Dll})
target_include_directories(worTCS INTERFACE
        ${worTCS_INCLUDE_DIR} ${worTCS_DIR}/include)