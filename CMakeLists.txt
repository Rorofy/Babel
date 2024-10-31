cmake_minimum_required(VERSION 3.10)
project(BABEL)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/server/include/")
include_directories("${PROJECT_SOURCE_DIR}/client/include/")
include_directories("${PROJECT_SOURCE_DIR}/client/include/network")
include_directories("${PROJECT_SOURCE_DIR}/common/include/")

file(GLOB_RECURSE COMMON_SRC RELATIVE ${CMAKE_SOURCE_DIR} "common/src/*.cpp")
file(GLOB_RECURSE SERVER_SRC RELATIVE ${CMAKE_SOURCE_DIR} "server/src/*.cpp")
file(GLOB_RECURSE CLIENT_SRC RELATIVE ${CMAKE_SOURCE_DIR} "client/src/*.cpp")
add_executable(babel_client ${CLIENT_SRC} ${COMMON_SRC})
target_link_libraries(babel_client ${CONAN_LIBS})

add_executable(babel_server ${SERVER_SRC} ${COMMON_SRC})
target_link_libraries(babel_server ${CONAN_LIBS})