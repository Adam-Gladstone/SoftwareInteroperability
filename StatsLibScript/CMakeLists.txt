cmake_minimum_required(VERSION 3.27)

project(StatsLibScript)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -Wall -std=c++20 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -std=c++20")

set(BOOST_ROOT "D:/Libraries/boost_1_91_0/")
set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.91.0) 

# Bring in the Boost headers and headers from the project
include_directories(${BOOST_ROOT} "../../Common/include/")

# Wildcard additions:
file(GLOB SOURCES "../Common/source/*.cpp")
file(GLOB HEADERS "../Common/include/*.h")

# Generate the output from the sources
add_executable(StatsLibScript ${SOURCES} ${HEADERS}
                lib/module.cpp 
                lib/Conversion.cpp 
                lib/Functions.cpp 
                lib/Classes.cpp
                )

set_target_properties(StatsLibScript PROPERTIES COMPILE_FLAGS "-O0 -std=c++20 -I D:/Libraries/boost_1_91_0/ -I D:/Development/Projects/C++/SoftwareInteroperability/Common/include/ -o StatsLibScript.js")

set_target_properties(StatsLibScript PROPERTIES LINK_FLAGS    "-o StatsLibScript.js --bind -O0 -g3 -sENVIRONMENT=web -sNO_DISABLE_EXCEPTION_CATCHING --no-entry")

