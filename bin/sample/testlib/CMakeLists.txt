#add library to usr/lib/ using deploy_lib.sh script before running this cmake
project(testLib)
cmake_minimum_required(VERSION 3.5)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories (${GLIB_INCLUDE_DIRS})
include_directories (../../../include)
link_directories (${GLIB_LIBRARY_DIRS})

pkg_check_modules(DBUS REQUIRED dbus-1)
include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})
set(MyLib "")
find_library(
LIB_PATH 
NAME libCppDBusLib.so
HINTS "/usr/lib/"
)
message("Custom library ${LIB_PATH}, dbus lib ${DBUS_LIBRARIES}")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow-compatible-local -std=c++17")
add_executable(TestLib main.cpp)
target_link_libraries(TestLib ${DBUS_LIBRARIES} ${GLIB_LIBRARIES} ${LIB_PATH})

