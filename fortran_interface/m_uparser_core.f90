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
!! @file m_uparser_core.f90
!! @author Issam SAID
!! @brief This file implements the Fortran interface of the uparser main  
!! routines.
!! @see uparser/core.h
!<
module m_uparser_core
    use, intrinsic :: iso_c_binding

    implicit none

    private

    interface
        subroutine c_uparser_init(argc, argv) bind(c, name = "uparser_init")
            use, intrinsic :: iso_c_binding, only: c_int, c_ptr
            implicit none
            integer(kind=c_int), intent(in), value :: argc
            type(c_ptr), intent(in),         value :: argv
        end subroutine c_uparser_init

        subroutine c_uparser_load(filename) bind(c, name = "uparser_load")
            use, intrinsic :: iso_c_binding, only: c_char
            implicit none
            character(kind=c_char), intent(in) :: filename
        end subroutine c_uparser_load
    end interface

    interface
        subroutine uparser_parse() bind(c, name = "uparser_parse")
        end subroutine uparser_parse

        subroutine uparser_release() bind(c, name = "uparser_release")
        end subroutine uparser_release

        subroutine uparser_usage() bind(c, name = "uparser_usage")
        end subroutine uparser_usage 
    end interface

    public :: uparser_init
    public :: uparser_load
    public :: uparser_parse
    public :: uparser_release
    public :: uparser_usage

contains
    
    subroutine uparser_init()
        integer                                 :: i, argc
        character(len=128), allocatable, target :: argv(:) 
        type(c_ptr),        allocatable, target :: cargv(:) 
        character(len=128)                      :: tmp
        argc = command_argument_count() + 1
        allocate(argv(argc), cargv(argc))
        call get_command_argument(0, tmp)
        tmp      = trim(tmp)//c_null_char
        argv(1)  = tmp
        cargv(1) = c_loc(argv(1))
        write(*,*) tmp 
        do i=2, argc
            call get_command_argument(i, tmp)
            tmp      = trim(tmp)//c_null_char
            argv(i)  = tmp
            cargv(i) = c_loc(argv(i))
        end do
        call c_uparser_init(argc, cargv)
        deallocate(argv, cargv)
    end subroutine uparser_init
    
    subroutine uparser_load(filename)
        character(len=*), intent(in) :: filename
        call c_uparser_load(filename // c_null_char)
    end subroutine uparser_load
    
end module m_uparser_core
