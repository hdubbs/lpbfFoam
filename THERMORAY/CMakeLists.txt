cmake_minimum_required(VERSION 3.16)

include (GNUInstallDirs)

# CUDA 11.3 is required for this library
set(CMAKE_CUDA_STANDARD_REQUIRED 11.3)
set(CMAKE_CUDA_STANDARD_REQUIRED True)

# TODO: add cuda version checking

# Check that OpenFOAM environment variables are available
if (NOT DEFINED ENV{FOAM_USER_LIBBIN} OR NOT DEFINED ENV{FOAM_SRC})
    message(FATAL_ERROR "OpenFOAM environment variables not available")
endif()


# Project name
project(THERMORAY LANGUAGES CUDA CXX)


# Set default install path
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
endif()

#===============================================================================
#   Set OpenFOAM Environment
#===============================================================================


message("\n-------------------------------------------------------------------") 
message("\tGenerate THERMORAY code rules for OpenFOAM version $ENV{WM_PROJECT_VERSION}")
message("-------------------------------------------------------------------")

# Check the OpenFOAM version and set the correct include statements
string(REGEX MATCH "([0-9]+)" _ $ENV{WM_PROJECT_VERSION})
set(OF_VERSION_NUMBER ${CMAKE_MATCH_1})

# If VERSION > 1000 then it is a OpenFOAM.com (ESI) version
# In OpenFOAM (ESI) the triSurface is moved into the surfaceMesh 
# Note: The if() statement evaluates a set variable to true if no
# $-Sign is used. For the cmakedefine statement this means that all set 
# variables are resolved as true
# if (${OF_VERSION_NUMBER} GREATER_EQUAL 1000)
#     SET(OF_FORK_ESI true BOOL "OpenFOAM Fork: ESI")
#     SET(OF_FORK_VERSION ${OF_VERSION_NUMBER})
#     message("OF_VERSION: ${OF_FORK_VERSION}")
# else()
#     SET(OF_FORK_ORG true BOOL "OpenFOAM Fork: Org")
#     SET(OF_FORK_VERSION ${OF_VERSION_NUMBER})
#     message("OF_VERSION: ${OF_FORK_VERSION}")
# endif()



# configure_file(
#     ${CMAKE_SOURCE_DIR}/versionRules/codeRules.H.in
#     ${CMAKE_BINARY_DIR}/generated/codeRules.H
# )


SET(cuda_src "hello.cu")

ADD_LIBRARY(${PROJECT_NAME} SHARED "${cuda_src}")


#===============================================================================
#                      Install CMake Exports
#===============================================================================
# Note EXPORT THERMORAYTargets only works if called by added sublibrary
# And this is exported in that subfolder's CMakeLists.txt

# install(EXPORT THERMORAYTargets 
#         FILE THERMORAY.cmake
#         NAMESPACE THERMORAY::
#         DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/THERMORAY
# )

# TODO: this has to changed to above when subdirectories are added
message ("CMAKE INSTALL LIBDIR IS: ${CMAKE_INSTALL_LIBDIR}")

install(TARGETS ${PROJECT_NAME} 
        # FILE THERMORAY.cmake
        # NAMESPACE THERMORAY::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/THERMORAY
)