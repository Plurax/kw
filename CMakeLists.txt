cmake_minimum_required(VERSION 3.2)
set (CMAKE_CXX_STANDARD 17)
set (CXX_STANDARD_REQUIRED true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Setting up project
project(kw)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)

# Avoid all symbols to be exported
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CHUHLICH_KW_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include/")
set(CHUHLICH_KW_SRC_BUILD_DIR "${PROJECT_SOURCE_DIR}/src/")

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    #configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KW.doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/KW.doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/../KW.doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

set(CHUHLICH_KW_TARGET_NAME               ${PROJECT_NAME})

# The version number.
# Set the version number of your project here (format is MAJOR.MINOR.PATCHLEVEL - e.g. 1.0.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "4")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

##
## OPTIONS
##
option(KW_BuildTests "Build the unit tests when BUILD_TESTING is enabled." OFF)

## Git (and its revision)
find_package(Git QUIET) # if we don't find git or FindGit.cmake is not on the system we ignore it.
## GetGitRevisionDescription module to retreive branch and revision information from Git
## Starting with Git 1.9 the module will be part of official cMake distribution, until then it has to be
## part of the application
## The Git module will trigger a reconfiguration for each pull that will bring a new revision on the local repository
set (VCS_REVISION "-1")
if(GIT_FOUND)
    include(GetGitRevisionDescription)
    get_git_head_revision(GIT_REFSPEC GIT_SHA1)
    git_get_exact_tag(GIT_TAG)
    if(GIT_TAG EQUAL "-128-NOTFOUND")
        set (GIT_TAG "none")
    endif()
    message(STATUS "GIT branch ${GIT_REFSPEC}")
    message(STATUS "GIT revision ${GIT_SHA1}")
    message(STATUS "GIT tag ${GIT_TAG}")
    set (VCS_REVISION ${GIT_SHA1})
endif()

# This line finds the boost lib and headers.
set(Boost_NO_BOOST_CMAKE ON) #  Don't do a find_package in config mode before searching for a regular boost install.
find_package(Boost COMPONENTS log_setup REQUIRED)
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

# This sets the include directory for the reference project. This is the -I flag in gcc.
# All the includes should be in this variable To add new directories to the include path,
# just add them in this list (after a space), or add an include_directories statement in a
# subdirectory's CMakeLists.
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/ext/json/include
    ${PROJECT_BINARY_DIR}/include   # add the binary tree to the search path so that we will find Version.h
    ${Boost_INCLUDE_DIRS}
)


add_subdirectory(include)
add_subdirectory(src)


##
## TESTS
## create and configure the unit test target
##
include(CTest) #adds option BUILD_TESTING (default ON)

if(BUILD_TESTING AND KW_BuildTests)
    enable_testing()
    add_subdirectory(test)
endif()

#
# SYSTEM PACKAGING (RPM, TGZ, ...)
# _____________________________________________________________________________

#include(CPackConfig)

#
# CMAKE PACKAGING (for other CMake projects to use this one easily)
# _____________________________________________________________________________

#include(PackageConfigurator)
