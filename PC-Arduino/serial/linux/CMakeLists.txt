# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.10)

# Define colors
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset "${Esc}[m")
  set(ColorBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

project ("TinySerializer-Demo-Serial-Host" C CXX)
set (CMAKE_CXX_STANDARD 20) # We use new features like std::endian, std::float_32, ...

add_compile_definitions(USING_STANDARD_LIBRARY=1)

#########################   Libraries   #########################


# Find packages used throughout this repository
message("${BoldYellow}Searching for libraries...${ColorReset}")


# Serial
# add_subdirectory(thirdparty/serial)
# The Serial cmake file is not meant for this configuration,
# so we remake our own.
add_library (serial
thirdparty/serial/include/serial/impl
thirdparty/serial/src/impl/list_ports/list_ports_linux.cc
thirdparty/serial/src/impl/unix.cc
thirdparty/serial/include/serial/impl/unix.h
thirdparty/serial/include/serial/serial.h
thirdparty/serial/include/serial/v8stdint.h
thirdparty/serial/src/serial.cc
)
target_link_libraries (serial rt pthread)
target_include_directories(serial PUBLIC thirdparty/serial/include/)


message("${BoldYellow}Library search complete!${ColorReset}")


#########################   Project   #########################


set(PROJECT_SOURCES
    src/shared/messages.hpp
    src/main.cpp
    src/shared/TinySerializer.cpp
    src/shared/TinySerializer.hpp
)
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} serial)


#########################   Tests   #########################


# Include tests.
if(BUILD_TESTS)
include(CTest)
add_subdirectory ("test")
endif()

if(BUILD_EXAMPLES)
add_subdirectory(cmake_examples)
endif()