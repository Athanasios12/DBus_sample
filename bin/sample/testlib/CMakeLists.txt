#add library to usr/lib/ using deploy_lib.sh script before running this cmake
project(testLib)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
#find dbus
find_package(DBus REQUIRED)
# Use results of find_package() call.
include_directories(${DBUS_INCLUDE_DIRS})
#
#Needed by DBus
#### GLIB ####
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories (${GLIB_INCLUDE_DIRS})
link_directories (${GLIB_LIBRARY_DIRS})
#custom includes
include_directories (../../../include)
find_library(
LIB_PATH
NAME libCppDBusLib.so
HINTS "/usr/lib/"
)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow-compatible-local -std=c++17 -ldbus-1 -pthread -L/usr/lib/ -lCppDBusLib")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow-compatible-local -std=c++17")
add_executable(TestLib main.cpp)
target_link_libraries(TestLib CppDBusLib ${DBUS_LIBRARIES})
