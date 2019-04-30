#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::cairo::cairo" for configuration "Debug"
set_property(TARGET unofficial::cairo::cairo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::cairo::cairo PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/cairod.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/cairod.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS unofficial::cairo::cairo )
list(APPEND _IMPORT_CHECK_FILES_FOR_unofficial::cairo::cairo "${_IMPORT_PREFIX}/debug/lib/cairod.lib" "${_IMPORT_PREFIX}/debug/bin/cairod.dll" )

# Import target "unofficial::cairo::cairo-gobject" for configuration "Debug"
set_property(TARGET unofficial::cairo::cairo-gobject APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::cairo::cairo-gobject PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/cairo-gobjectd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/cairo-gobjectd.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS unofficial::cairo::cairo-gobject )
list(APPEND _IMPORT_CHECK_FILES_FOR_unofficial::cairo::cairo-gobject "${_IMPORT_PREFIX}/debug/lib/cairo-gobjectd.lib" "${_IMPORT_PREFIX}/debug/bin/cairo-gobjectd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
