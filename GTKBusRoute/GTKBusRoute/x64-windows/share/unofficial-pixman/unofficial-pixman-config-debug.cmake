#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::pixman::pixman-1" for configuration "Debug"
set_property(TARGET unofficial::pixman::pixman-1 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::pixman::pixman-1 PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/pixman-1d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/pixman-1d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS unofficial::pixman::pixman-1 )
list(APPEND _IMPORT_CHECK_FILES_FOR_unofficial::pixman::pixman-1 "${_IMPORT_PREFIX}/debug/lib/pixman-1d.lib" "${_IMPORT_PREFIX}/debug/bin/pixman-1d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
