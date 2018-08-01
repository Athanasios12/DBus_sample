project(DBus_sample)
cmake_minimum_required(VERSION 3.5)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
message(STATUS "${CMAKE_MODULE_PATH} is cmake module path")
find_package(DBus REQUIRED)
# Use results of find_package() call.
message(STATUS "${DBUS_INCLUDE_DIRS} is dbus include dirs")
message(STATUS "${DBUS_LIBRARIES} is dbus libraries")
include_directories(${DBUS_INCLUDE_DIRS})
#
#Needed by DBus
#### GLIB ####
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories (${GLIB_INCLUDE_DIRS})
link_directories (${GLIB_LIBRARY_DIRS})
##############


set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -ldbus-1 -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
message(STATUS "Source files: " ${SRC})
add_subdirectory("${PROJECT_SOURCE_DIR}/include")
message(STATUS "Header files: " ${HEADERS})

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory("${PROJECT_SOURCE_DIR}/tests")
message(STATUS "Tests Source files: " ${TESTS_SRC})

set(UNIT_TESTS "${PROJECT_NAME}_Tests")
add_executable(${PROJECT_NAME} main.cpp ${SRC} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${DBUS_LIBRARIES} ${GLIB_LIBRARIES})
#unit tests executable
add_executable(${UNIT_TESTS} ${TESTS_SRC} ${SRC} ${HEADERS})

target_link_libraries(${UNIT_TESTS} ${DBUS_LIBRARIES} ${GLIB_LIBRARIES} gtest_main)
add_test(NAME ${UNIT_TESTS} COMMAND test)








