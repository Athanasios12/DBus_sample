#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "googletest_gmock_main" for configuration "Debug"
set_property(TARGET googletest_gmock_main APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(googletest_gmock_main PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "-pthread;googletest_gmock"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libgmock_maind.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS googletest_gmock_main )
list(APPEND _IMPORT_CHECK_FILES_FOR_googletest_gmock_main "${_IMPORT_PREFIX}/lib/libgmock_maind.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
