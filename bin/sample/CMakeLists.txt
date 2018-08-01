find_package(PkgConfig) # Include functions provided by PkgConfig module.

pkg_check_modules(DBUS dbus-1) # This calls pkgconfig with appropriate arguments
# Use results of pkg_check_modules() call.
include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})

add_executable(DBusServer Server.cpp)
add_executable(DBusClient Client.cpp)

target_link_libraries(DBusServer ${DBUS_LIBRARIES})
target_link_libraries(DBusClient ${DBUS_LIBRARIES})
