#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::gettext::libintl" for configuration "Release"
set_property(TARGET unofficial::gettext::libintl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(unofficial::gettext::libintl PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libintl.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libintl.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS unofficial::gettext::libintl )
list(APPEND _IMPORT_CHECK_FILES_FOR_unofficial::gettext::libintl "${_IMPORT_PREFIX}/lib/libintl.lib" "${_IMPORT_PREFIX}/bin/libintl.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
