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
## 3. Neither the name of the copyright holder nor the names of its 
##    contributors may be used to endorse or promote products derived from 
##    this software without specific prior written permission.
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
## @file CMakeLists.txt
## @author Issam SAID
## @brief Install all the subdirectories when make install is invoked.
##

## Install the uparser Fortran interface.
if (EXISTS ${UPARSER_FORTRAN_BUILD_LIB})
    message(STATUS "Post-install: install the Fortran interface")
    file(COPY ${UPARSER_FORTRAN_BUILD_LIB}
         DESTINATION ${UPARSER_FORTRAN_INSTALL_DIR})
endif (EXISTS ${UPARSER_FORTRAN_BUILD_LIB})

## Install the uparser C unit testing executable.
if (EXISTS ${UPARSER_TEST_BUILD_EXE})
    message(STATUS "Post-install: install the uparser C unit test binary")
    file(COPY ${UPARSER_TEST_BUILD_EXE}
         DESTINATION ${UPARSER_TEST_INSTALL_DIR})
endif (EXISTS ${UPARSER_TEST_BUILD_EXE})

## Install the uparser Fortran interface unit testing executable.
if (EXISTS ${UPARSER_TEST_FORTRAN_BUILD_EXE})
    message(STATUS "Post-install: install the uparser Fortran unit test binary")
    file(COPY ${UPARSER_TEST_FORTRAN_BUILD_EXE}
         DESTINATION ${UPARSER_TEST_FORTRAN_INSTALL_DIR})
endif (EXISTS ${UPARSER_TEST_FORTRAN_BUILD_EXE})

## Install the uparser C examples.
if (DEFINED UPARSER_C_EXAMPLES_FILES)
    foreach (file ${UPARSER_C_EXAMPLES_FILES})
        if (EXISTS ${file})
            get_filename_component(n ${file} NAME)
            message(STATUS "Post-install: install the uparser C example ${n}")
            file(COPY ${file} 
                 DESTINATION ${UPARSER_C_EXAMPLES_INSTALL_DIR})
        endif (EXISTS ${file})
    endforeach(file ${UPARSER_C_EXAMPLES_FILES})
endif (DEFINED UPARSER_C_EXAMPLES_FILES)

## Install the uparser Fortran examples.
if (DEFINED UPARSER_FORTRAN_EXAMPLES_FILES)
    foreach (file ${UPARSER_FORTRAN_EXAMPLES_FILES})
        if (EXISTS ${file})
            get_filename_component(n ${file} NAME)
            message(STATUS "Post-install: install the uparser Fortran example ${n}")
            file(COPY ${file} 
                 DESTINATION ${UPARSER_FORTRAN_EXAMPLES_INSTALL_DIR})
        endif (EXISTS ${file})
    endforeach(file ${UPARSER_FORTRAN_EXAMPLES_FILES})
endif (DEFINED UPARSER_FORTRAN_EXAMPLES_FILES)