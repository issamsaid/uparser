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
!! FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPY OR
!! ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
!! EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
!! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
!! PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
!! LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
!! NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
!! SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
!!
!! @file m_uparser_get.f90
!! @author Issam SAID
!! @brief This file implements the Fortran interface of the uparser put routine.  
!! @see uparser/put.h
!<
module m_uparser_put
    use, intrinsic :: iso_c_binding

    implicit none

    private

    interface
        subroutine c_uparser_put(short_key, long_key,         &
                                 default_value, help_message) &
                                 bind(c, name = "uparser_put")
            use, intrinsic :: iso_c_binding, only: c_char
            implicit none
            character(kind=c_char, len=1), value, intent(in) :: short_key
            character(kind=c_char),               intent(in) :: long_key
            character(kind=c_char),               intent(in) :: default_value
            character(kind=c_char),               intent(in) :: help_message
        end subroutine c_uparser_put
    end interface

    public :: uparser_put
    interface uparser_put
        module procedure uparser_put_with_short_key
        module procedure uparser_put_no_short_key
    end interface uparser_put

contains
    
    subroutine uparser_put_with_short_key(short_key, long_key, &
                                          default_value, help_message)
        character(len=1),  intent(in) :: short_key
        character(len=*),  intent(in) :: long_key
        character(len=*),  intent(in) :: default_value
        character(len=*),  intent(in) :: help_message

        character(len=1, kind=c_char) :: c 
        c = short_key
        call c_uparser_put(c,                                &
                           trim(long_key)//c_null_char,      &
                           trim(default_value)//c_null_char, &
                           trim(help_message)//c_null_char)
    end subroutine uparser_put_with_short_key

    subroutine uparser_put_no_short_key(long_key, default_value, help_message)
        character(len=*),  intent(in) :: long_key
        character(len=*),  intent(in) :: default_value
        character(len=*),  intent(in) :: help_message
        
        call c_uparser_put(c_null_char,                      &
                           trim(long_key)//c_null_char,      &
                           trim(default_value)//c_null_char, &
                           trim(help_message)//c_null_char)
    end subroutine uparser_put_no_short_key
        
end module m_uparser_put
