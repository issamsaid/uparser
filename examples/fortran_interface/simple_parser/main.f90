!>
!! @copyright Copyright (c) 2016-, Issam SAID <said.issam@gmail.com>
!! All rights reserved.
!!
!! Redistribution and use in source and binary forms, with or without
!! modification, are permetted provided that the following conditions
!! are met:
!!
!! 1. Redistributions of source code must retain the above copyright
!!    notice, this list of conditions and the following disclaimer.
!! 2. Redistributions in binary form must reproduce the above copyright
!!    notice, this list of conditions and the following disclaimer inthe
!!    documentation and/or other materials provided with the distribution.
!! 3. Neither the name of the copyright holder nor the names of its contributors
!!    may be used to endorse or promote products derived from this software
!!    without specific prior written permission.
!!
!! THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
!! INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
!! FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
!! HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
!! SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
!! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR
!! PROFITS OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
!! LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
!! NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
!! SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
!!
!! @file simple_parser/main.f90
!! @author Issam SAID 
!! @brief An example of a simple parser code based on the uparser
!!  Fortran interface.
!!
!<
program simple_parser_fortran
    use m_uparser

    integer(kind=8)   :: i8 
    integer(kind=4)   :: i4 
    character(len=64) :: s
    logical           :: b
    real(kind=4)      :: r4
    real(kind=8)      :: r8
    integer(kind=4)   :: vect_i4(3) 
    integer(kind=8)   :: vect_i8(3) 
    real(kind=4)      :: vect_r4(3) 
    real(kind=8)      :: vect_r8(3) 

    write(*,*) "... start of the uparser simple parser Fortran example"

    !!< Initialize uparser.
    call uparser_init()

    !!< Populate the parser.
    call uparser_opt('i', "int32",   "2",        "this is a 32 bits integer")
    call uparser_opt('I', "int64",   "-9",       "this is a 64 bits integer")
    call uparser_opt('b', "boolean", "false",    "this is a boolean")
    call uparser_opt('s', "string",  "foo",      "this is a string")
    call uparser_opt('f', "float",   "1.234",    "this is a float")
    call uparser_opt('d', "double",  "9.876543", "this is a double")
    
    call uparser_opt("vint32",  "1,2,3", "this is a 32 bits integer tab")
    call uparser_opt("vint64",  "7,8,9", "this is a 64 bits integer tab")
    call uparser_opt("vfloat",  "1.23,4.56,7.89",  "this is a float tab")
    call uparser_opt("vdouble", "7.65,8.76,9.87", "this is a double tab")

    !!< Parse the command line arguments.
    call uparser_parse()

    !!< Show the uparser help.
    call uparser_usage()

    !!< Get values.
    call uparser_get("i",      i4)
    call uparser_get("int32",  i4)
    call uparser_get("I",      i8)
    call uparser_get("int64",  i8)
    call uparser_get("boolean", b)
    call uparser_get("string",  s)
    call uparser_get("f",      r4)
    call uparser_get("float",  r4)
    call uparser_get("d",      r8)
    call uparser_get("double", r8)

    call uparser_get("vint32",  vect_i4)
    call uparser_get("vint64",  vect_i8)
    call uparser_get("vfloat",  vect_r4)
    call uparser_get("vdouble", vect_r8)

    write(*,*) "... param int32   value is ", i4
    write(*,*) "... param int64   value is ", i8
    write(*,*) "... param boolean value is ", b 
    write(*,*) "... param string  value is ", s
    write(*,*) "... param float   value is ", r4
    write(*,*) "... param double  value is ", r8
    write(*,*) "... param vint32  value is ", vect_i4
    write(*,*) "... param vint64  value is ", vect_i8
    write(*,*) "... param vfloat  value is ", vect_r4
    write(*,*) "... param vdouble value is ", vect_r8

    !!< Release uparser.
    call uparser_release()
    write(*,*) "... end   of the uparser simple parser Fortran example"
end program simple_parser_fortran