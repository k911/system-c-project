cmake_minimum_required(VERSION 3.9)
project(systemc_hellow)

set (CMAKE_PREFIX_PATH /opt/systemc)
find_package(SystemCLanguage CONFIG REQUIRED)

set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD} CACHE STRING
        "C++ standard to build all targets. Supported values are 98, 11, and 14.")
set (CMAKE_CXX_STANDARD_REQUIRED ${SystemC_CXX_STANDARD_REQUIRED} CACHE BOOL
        "The with CMAKE_CXX_STANDARD selected C++ standard is a requirement.")

add_executable(systemc_hellow Hardware.cpp Hardware.h MyDataChannel.cpp MyDataChannel.h Main.cpp)

target_link_libraries(systemc_hellow SystemC::systemc)
