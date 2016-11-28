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
!! @file fortran_interface/m_uparser_arg.f90
!! @author Issam SAID
!! @brief This file implements the Fortran interface of the uparser_arg routine.  
!! @see uparser/arg.h
!<
module m_uparser_arg
    use, intrinsic :: iso_c_binding

    implicit none

    private

    interface
        subroutine c_uparser_arg(arg_name, help_message) &
                                 bind(c, name = "uparser_arg")
            use, intrinsic :: iso_c_binding, only: c_char
            implicit none
            character(kind=c_char), intent(in) :: arg_name
            character(kind=c_char), intent(in) :: help_message
        end subroutine c_uparser_arg
    end interface

    public :: uparser_arg

contains
    
    subroutine uparser_arg(arg_name, help_message)
        character(len=*),  intent(in) :: arg_name
        character(len=*),  intent(in) :: help_message
        
        call c_uparser_arg(trim(arg_name)//c_null_char,  &
                           trim(help_message)//c_null_char)
    end subroutine uparser_arg
        
end module m_uparser_arg
