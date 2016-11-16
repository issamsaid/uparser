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
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
## HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
## PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
## LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
## NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
## @file test/src/CMakeLists.txt
## @author Issam SAID
## @brief CMake build script for the uparser C/C++ unit testing.
##
project (uparser_test CXX)
cmake_minimum_required (VERSION 2.8)

## Include the uparser and the googletest headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB CXX_SRCS "*.cc")

add_executable(uparser_test ${CXX_SRCS})

## Link to the uparser and gtest libraries
target_link_libraries (uparser_test LINK_PUBLIC uparser)
target_link_libraries (uparser_test LINK_PUBLIC liburb_tree)
target_link_libraries (uparser_test LINK_PUBLIC libgtest)
add_dependencies(uparser_test uparser)

## Install the binary into test/bin
install(TARGETS uparser_test 
        DESTINATION test/bin 
        OPTIONAL)

## Add the test to the make test target
add_test(NAME uparser_test COMMAND ${EXECUTABLE_OUTPUT_PATH}/uparser_test)

##
## Workaround to install this target simultaneously with the main target.
## This is due to a cmake restriction: 
##  - Installing a target with the EXCLUDE_FROM_ALL target property 
##    set to TRUE has undefined behavior. 
##  
## First: inform the build location of the target. 
get_target_property(UPARSER_TEST_BUILD_EXE uparser_test LOCATION)

## Then : inform the location where the target is to be installed. 
set (UPARSER_TEST_INSTALL_DIR ${CMAKE_SOURCE_DIR}/test/bin)