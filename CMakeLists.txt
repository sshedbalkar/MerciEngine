cmake_minimum_required(VERSION 3.13)

# set VCPKG parameters before setting the project
set(VCPKG_TARGET_TRIPLET x64-linux)
set(ENV{VCPKG_ROOT} /home/mercileslie/WorkWork/Libraries/vcpkg)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
    message("Set VCPKG_ROOT: $ENV{VCPKG_ROOT}")
endif()

# Set the project name
set(PROJECT_NAME merci_engine)
project(${PROJECT_NAME})

# set a project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 1)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")
set(PROJECT_VERSION ALIAS ${${PROJECT_NAME}_VERSION})

# set cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# message("List of compile features: ${CMAKE_CXX_COMPILE_FEATURES}")

# add modules
add_subdirectory(src/net)
add_subdirectory(src/client)
add_subdirectory(src/server)