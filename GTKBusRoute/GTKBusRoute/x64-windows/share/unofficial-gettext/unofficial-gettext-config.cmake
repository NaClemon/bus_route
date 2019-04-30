
include(CMakeFindDependencyMacro)
find_dependency(unofficial-iconv)
find_dependency(Threads)
include(${CMAKE_CURRENT_LIST_DIR}/unofficial-gettext-targets.cmake)
