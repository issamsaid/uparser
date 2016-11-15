##
## @copyright Copyright (c) 2016-, Issam SAID <said.issam@gmail.com>
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions
## are met:
##
## 1. Redistributions of source code must retain the above copyright
##    notice, this list of conditions and the following disclaimer.
## 2. Redistributions in binary form must reproduce the above copyright
##    notice, this list of conditions and the following disclaimer in the
##    documentation and/or other materials provided with the distribution.
## 3. Neither the name of the copyright holder nor the names of its contributors
##    may be used to endorse or promote products derived from this software
##    without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
## INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE copyright 
## holder OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
## PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
## LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
## NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
## @file CMakeLists.txt
## @author Issam SAID
## @brief CMake main build script for uparser.
##
project (uparser_distribution C CXX Fortran)
cmake_minimum_required (VERSION 2.8)

## Enable ExternalProject CMake module
include(ExternalProject)
find_package(Threads REQUIRED)

## Overwrite the install prefix
set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

## Add extra cmake modules dir
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

## Configurable options for how we want to build uparser
option(uparser_debug       "Build uparser with the debug mode."                  OFF)
option(uparser_verbose     "Build uparser with the verbose mode activated."       ON)
option(uparser_use_tty     "Build uparser with logging into  the terminal."       ON)
option(uparser_roundup_wrk "Build uparser with rounding up the workgroup sizes."  ON)

## Set the build type (DEFAULT is Release)
if (NOT CMAKE_BUILD_TYPE)
   set (CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)
if (uparser_debug)
	 set (CMAKE_BUILD_TYPE Debug)
endif (uparser_debug)
message(STATUS "... CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

## Set the compilation flags 
if ("${CMAKE_C_COMPILER_ID}"     MATCHES "Cray")
  	include(${CMAKE_MODULE_PATH}/cray_c.cmake)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    include(${CMAKE_MODULE_PATH}/gnu_c.cmake)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "Intel")
    include(${CMAKE_MODULE_PATH}/intel_c.cmake)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "PGI")
    include(${CMAKE_MODULE_PATH}/pgi_c.cmake)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "MSVC")
  	include(${CMAKE_MODULE_PATH}/msvc_c.cmake)
endif ("${CMAKE_C_COMPILER_ID}"     MATCHES "Cray")

if ("${CMAKE_Fortran_COMPILER_ID}"     MATCHES "Cray")
  	include(${CMAKE_MODULE_PATH}/cray_fortran.cmake)
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "GNU")
	include(${CMAKE_MODULE_PATH}/gnu_fortran.cmake)
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "Intel")
  	include(${CMAKE_MODULE_PATH}/intel_fortran.cmake)
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "PGI")
    	include(${CMAKE_MODULE_PATH}/pgi_fortran.cmake)
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "MSVC")
  	include(${CMAKE_MODULE_PATH}/msvc_fortran.cmake)
endif ("${CMAKE_Fortran_COMPILER_ID}"     MATCHES "Cray")

if ("${CMAKE_CXX_COMPILER_ID}"     MATCHES "Cray")
  	include(${CMAKE_MODULE_PATH}/cray_cxx.cmake)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	include(${CMAKE_MODULE_PATH}/gnu_cxx.cmake)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
    include(${CMAKE_MODULE_PATH}/intel_cxx.cmake)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "PGI")
    include(${CMAKE_MODULE_PATH}/pgi_cxx.cmake)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
  	include(${CMAKE_MODULE_PATH}/msvc_cxx.cmake)
endif ("${CMAKE_CXX_COMPILER_ID}"     MATCHES "Cray")

if (uparser_verbose)
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -D__UPARSER_VERBOSE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__UPARSER_VERBOSE")
endif (uparser_verbose)
if (uparser_use_tty)
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -D__UPARSER_LOG_STD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__UPARSER_LOG_STD")
endif (uparser_use_tty)
if (uparser_roundup_wrk)
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -D__UPARSER_ROUNDUP_WRK")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__UPARSER_ROUNDUP_WRK")
endif (uparser_roundup_wrk)

##
## Use the urb_tree library if the user sets its path 
## or download and install it as an external project.
##
if (DEFINED ENV{URB_TREE_DIR})
    include_directories("$ENV{URB_TREE_DIR}/include")
    add_library(liburb_tree STATIC IMPORTED GLOBAL)
    set_target_properties(liburb_tree PROPERTIES
        "IMPORTED_LOCATION" "$ENV{URB_TREE_DIR}/lib/liburb_tree.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")
else (DEFINED ENV{URB_TREE_DIR})
    ExternalProject_Add(
        urb_tree
        GIT_REPOSITORY https://github.com/issamsaid/urb_tree.git
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/urb_tree
        INSTALL_COMMAND ""
        UPDATE_COMMAND  "")

    ## Get urb_tree source and binary directories.
    ExternalProject_Get_Property(urb_tree SOURCE_DIR BINARY_DIR)

    ## Create a liburb_tree target to be used as a dependency by uparser.
    add_library(liburb_tree IMPORTED STATIC GLOBAL)
    add_dependencies(liburb_tree urb_tree)

    ## Set liburb_tree properties.
    set_target_properties(liburb_tree PROPERTIES
        "IMPORTED_LOCATION" "${BINARY_DIR}/src/liburb_tree.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

    ## Include urb_tree headers.
    include_directories("${SOURCE_DIR}/include")
endif (DEFINED ENV{URB_TREE_DIR})

## Build the uparser C/C++ library.
add_subdirectory(src)

## Build the uparser Fortran interface.
#add_subdirectory(fortran_interface EXCLUDE_FROM_ALL)

## Build the uparser unit testing suit (develop branch only).
add_subdirectory(test EXCLUDE_FROM_ALL)

## Build the uparser examples.
#add_subdirectory(examples EXCLUDE_FROM_ALL)

## Build the uparser documentation.
#add_subdirectory(doc EXCLUDE_FROM_ALL)

# ##
# ## Workarounds for the lack of post_install steps:
# ##
# ## Add the path to ulist which we need during post-install.
# get_target_property(ULIST_LIB libulist IMPORTED_LOCATION)
# install(CODE "set(ULIST_LIB \"${ULIST_LIB}\")")

# ## Add the path to urb_tree which we need during post install.
# get_target_property(URB_TREE_LIB liburb_tree IMPORTED_LOCATION)
# install(CODE "set(URB_TREE_LIB \"${URB_TREE_LIB}\")")

# ## Add the paths of the uparser_fortran target which we need during post-install.
# get_directory_property(UPARSER_FORTRAN_BUILD_LIB DIRECTORY 
#                        fortran_interface DEFINITION UPARSER_FORTRAN_BUILD_LIB)
# get_directory_property(UPARSER_FORTRAN_INSTALL_DIR DIRECTORY 
#                        fortran_interface DEFINITION UPARSER_FORTRAN_INSTALL_DIR)
# install(CODE "set(UPARSER_FORTRAN_BUILD_LIB \"${UPARSER_FORTRAN_BUILD_LIB}\")")
# install(CODE "set(UPARSER_FORTRAN_INSTALL_DIR \"${UPARSER_FORTRAN_INSTALL_DIR}\")")

# ## Add the paths of the uparser_test target which we need during post-install.
# get_directory_property(UPARSER_TEST_BUILD_EXE DIRECTORY 
#                        test/src DEFINITION UPARSER_TEST_BUILD_EXE)
# get_directory_property(UPARSER_TEST_INSTALL_DIR DIRECTORY 
#                        test/src DEFINITION UPARSER_TEST_INSTALL_DIR)
# install(CODE "set(UPARSER_TEST_BUILD_EXE \"${UPARSER_TEST_BUILD_EXE}\")")
# install(CODE "set(UPARSER_TEST_INSTALL_DIR \"${UPARSER_TEST_INSTALL_DIR}\")")

# ## Add the paths of uparser_test_fortran which we need during post-install.
# get_directory_property(UPARSER_TEST_FORTRAN_BUILD_EXE DIRECTORY 
#                        test/fortran_interface 
#                        DEFINITION UPARSER_TEST_FORTRAN_BUILD_EXE)
# get_directory_property(UPARSER_TEST_FORTRAN_INSTALL_DIR DIRECTORY 
#                        test/fortran_interface 
#                        DEFINITION UPARSER_TEST_FORTRAN_INSTALL_DIR)
# install(CODE 
#         "set(UPARSER_TEST_FORTRAN_BUILD_EXE \"${UPARSER_TEST_FORTRAN_BUILD_EXE}\")")
# install(CODE 
#         "set(UPARSER_TEST_FORTRAN_INSTALL_DIR \"${UPARSER_TEST_FORTRAN_INSTALL_DIR}\")")

# ## Add the paths of the c_examples target which we need during post-install.
# get_directory_property(UPARSER_C_EXAMPLES_FILES DIRECTORY 
#                        examples/src DEFINITION UPARSER_C_EXAMPLES_FILES)
# get_directory_property(UPARSER_C_EXAMPLES_INSTALL_DIR DIRECTORY 
#                        examples/src DEFINITION UPARSER_C_EXAMPLES_INSTALL_DIR)
# install(CODE 
#         "set(UPARSER_C_EXAMPLES_FILES \"${UPARSER_C_EXAMPLES_FILES}\")")
# install(CODE 
#         "set(UPARSER_C_EXAMPLES_INSTALL_DIR \"${UPARSER_C_EXAMPLES_INSTALL_DIR}\")")

# ## Add the paths of the fortran_examples target which 
# ## we need during post-install.
# get_directory_property(UPARSER_FORTRAN_EXAMPLES_FILES DIRECTORY 
#                        examples/fortran_interface 
#                        DEFINITION UPARSER_FORTRAN_EXAMPLES_FILES)
# get_directory_property(UPARSER_FORTRAN_EXAMPLES_INSTALL_DIR DIRECTORY 
#                        examples/fortran_interface 
#                        DEFINITION UPARSER_FORTRAN_EXAMPLES_INSTALL_DIR)
# install(CODE 
#         "set(UPARSER_FORTRAN_EXAMPLES_FILES \"${UPARSER_FORTRAN_EXAMPLES_FILES}\")")
# install(CODE 
#         "set(UPARSER_FORTRAN_EXAMPLES_INSTALL_DIR \"${UPARSER_FORTRAN_EXAMPLES_INSTALL_DIR}\")")

# ## Add a subdirectory that contains the post-install scripts.
# add_subdirectory(${CMAKE_SOURCE_DIR}/cmake/post_install)