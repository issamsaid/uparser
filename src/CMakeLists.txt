##
## @copyright Copyright (c) 2016-, Issam SAID <said.issam@gmail.com>.
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
## @file src/CMakeLists.txt
## @author Issam SAID
## @brief CMake build script for the uparser C library.
##
project (uparser C)
cmake_minimum_required (VERSION 2.8)

## Build the uparser C static library.
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB C_SRCS "single/*.c" "*.c")
add_library(uparser STATIC ${C_SRCS})
set_target_properties(uparser PROPERTIES OUTPUT_NAME "uparser")
install(TARGETS uparser ARCHIVE DESTINATION lib)

## Add the pathes to uparser which we need during post install.
get_target_property(UPARSER_BUILD_LIB uparser LOCATION)
get_filename_component(UPARSER_BUILD_DIR ${UPARSER_BUILD_LIB} DIRECTORY)
string(REPLACE ${UPARSER_BUILD_DIR} 
       ${CMAKE_SOURCE_DIR}/lib UPARSER_INSTALL_LIB ${UPARSER_BUILD_LIB})

install(CODE "set(UPARSER_BUILD_LIB \"${UPARSER_BUILD_LIB}\")")
install(CODE "set(UPARSER_INSTALL_LIB \"${UPARSER_INSTALL_LIB}\")")

