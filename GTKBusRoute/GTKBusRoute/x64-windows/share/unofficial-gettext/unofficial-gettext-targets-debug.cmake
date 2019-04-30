#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::gettext::libintl" for configuration "Debug"
set_property(TARGET unofficial::gettext::libintl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::gettext::libintl PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/libintl.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/libintl.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS unofficial::gettext::libintl )
list(APPEND _IMPORT_CHECK_FILES_FOR_unofficial::gettext::libintl "${_IMPORT_PREFIX}/debug/lib/libintl.lib" "${_IMPORT_PREFIX}/debug/bin/libintl.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
