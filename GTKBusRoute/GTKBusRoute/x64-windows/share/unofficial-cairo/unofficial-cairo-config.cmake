
include(CMakeFindDependencyMacro)
find_dependency(ZLIB)
find_dependency(PNG)
find_dependency(Freetype)
find_dependency(unofficial-glib CONFIG)
find_dependency(unofficial-fontconfig CONFIG)
find_dependency(unofficial-pixman CONFIG)

include(${CMAKE_CURRENT_LIST_DIR}/unofficial-cairo-targets.cmake)
