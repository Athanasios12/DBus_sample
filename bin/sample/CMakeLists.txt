find_package(PkgConfig) # Include functions provided by PkgConfig module.

pkg_check_modules(DBUS dbus-1) # This calls pkgconfig with appropriate arguments
pkg_check_modules(DBUS_GLIB dbus-glib-1)
pkg_check_modules(GIO gio-2.0)
# Use results of pkg_check_modules() call.
include_directories(${DBUS_INCLUDE_DIRS} ${GIO_INCLUDE_DIRS} ${DBUS_GLIB_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS} ${GIO_LIBRARY_DIRS} ${DBUS_GLIB_LIBRARY_DIRS})

add_executable(DBusServer Server.cpp)
add_executable(DBusClient Client.cpp)

target_link_libraries(DBusServer ${DBUS_LIBRARIES} ${DBUS_GLIB_LIBRARIES} ${GIO_LIBRARIES})
target_link_libraries(DBusClient ${DBUS_LIBRARIES})
