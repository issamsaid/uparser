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
!! @brief This file implements the Fortran interface of the uparser get routine.  
!! @see uparser/get.h
!<
module m_uparser_get
    use, intrinsic :: iso_c_binding

    implicit none

    private

    interface
        subroutine c_uparser_get_bool(key, val) &
            bind(c, name = "uparser_get_bool")
            use, intrinsic :: iso_c_binding, only: c_char, c_bool
            implicit none
            character(kind=c_char), intent(in) :: key
            logical(kind=c_bool),  intent(out) :: val
        end subroutine c_uparser_get_bool

        subroutine c_uparser_get_char(key, val) &
            bind(c, name='uparser_get_char')
            use, intrinsic :: iso_c_binding, only: c_char
            character(kind=c_char),  intent(in) :: key
            character(kind=c_char), intent(out) :: val
        end subroutine c_uparser_get_char

        subroutine c_uparser_get_string(key, val) &
            bind(c, name='uparser_get_string')
            use, intrinsic :: iso_c_binding, only: c_char
            character(kind=c_char),  intent(in) :: key
            character(kind=c_char), intent(out) :: val
        end subroutine c_uparser_get_string

        subroutine c_uparser_get_int32(key, val) &
            bind(c, name='uparser_get_int32')
            use, intrinsic :: iso_c_binding, only: c_char, c_ptr
            character(kind=c_char), intent(in) :: key
            type(c_ptr),     value, intent(in) :: val
        end subroutine c_uparser_get_int32

        subroutine c_uparser_get_int64(key, val) &
            bind(c, name='uparser_get_int64')
            use, intrinsic :: iso_c_binding, only: c_char, c_ptr
            character(kind=c_char), intent(in) :: key
            type(c_ptr),     value, intent(in) :: val
        end subroutine c_uparser_get_int64

        subroutine c_uparser_get_float(key, val) &
            bind(c, name='uparser_get_float')
            use, intrinsic :: iso_c_binding, only: c_char, c_ptr
            character(kind=c_char), intent(in) :: key
            type(c_ptr),     value, intent(in) :: val
        end subroutine c_uparser_get_float

        subroutine c_uparser_get_double(key, val) &
            bind(c, name='uparser_get_double')
            use, intrinsic :: iso_c_binding, only: c_char, c_ptr
            character(kind=c_char), intent(in) :: key
            type(c_ptr),     value, intent(in) :: val
        end subroutine c_uparser_get_double

    end interface

    public :: uparser_get
    interface uparser_get
        module procedure uparser_get_bool
        module procedure uparser_get_string
        module procedure uparser_get_int32
        module procedure uparser_get_vect_int32
        module procedure uparser_get_int64
        module procedure uparser_get_vect_int64
        module procedure uparser_get_float
        module procedure uparser_get_vect_float
        module procedure uparser_get_double
        module procedure uparser_get_vect_double
    end interface uparser_get

contains
    
    subroutine uparser_get_bool(key, val)
        character(len=*), intent(in) :: key
        logical,         intent(out) :: val
        logical(kind=c_bool)         :: cval
        call c_uparser_get_bool(trim(key)//c_null_char, cval)
        val = cval
    end subroutine uparser_get_bool

    subroutine uparser_get_string(key, val)
        character(len=*),  intent(in) :: key
        character(len=*), intent(out) :: val
        integer(kind=4)               :: len_val
        val          = ""
        if (len(key) .eq. 1) then
            call c_uparser_get_char(trim(key)//c_null_char, val)
        else
            call c_uparser_get_string(trim(key)//c_null_char, val)
            len_val                = len_trim(val)
            val(len_val:len_val+1) = ''
        endif
    end subroutine uparser_get_string

    subroutine uparser_get_int32(key, val)
        character(len=*), intent(in) :: key
        integer(kind=4), intent(out) :: val

        integer(kind=c_int), target :: tab(1)
        call c_uparser_get_int32(trim(key)//c_null_char, c_loc(tab))
        val = tab(1)
    end subroutine uparser_get_int32

    subroutine uparser_get_vect_int32(key, val)
        character(len=*), intent(in) :: key
        integer(kind=4), intent(out) :: val(:)

        integer(kind=c_int), dimension(size(val)), target :: tab
        call c_uparser_get_int32(trim(key)//c_null_char, c_loc(tab))
        val = tab
    end subroutine uparser_get_vect_int32

    subroutine uparser_get_int64(key, val)
        character(len=*), intent(in) :: key
        integer(kind=8), intent(out) :: val

        integer(kind=c_int64_t), target :: tab(1)
        call c_uparser_get_int64(trim(key)//c_null_char, c_loc(tab))
        val = tab(1)
    end subroutine uparser_get_int64

    subroutine uparser_get_vect_int64(key, val)
        character(len=*), intent(in) :: key
        integer(kind=8), intent(out) :: val(:)

        integer(kind=c_int64_t), dimension(size(val)), target :: tab
        call c_uparser_get_int64(trim(key)//c_null_char, c_loc(tab))
        val = tab
    end subroutine uparser_get_vect_int64

    subroutine uparser_get_float(key, val)
        character(len=*), intent(in) :: key
        real(kind=4),    intent(out) :: val

        real(kind=c_float), target :: tab(1)
        call c_uparser_get_float(trim(key)//c_null_char, c_loc(tab))
        val = tab(1)
    end subroutine uparser_get_float

    subroutine uparser_get_vect_float(key, val)
        character(len=*), intent(in) :: key
        real(kind=4),    intent(out) :: val(:)

        real(kind=c_float), dimension(size(val)), target :: tab
        call c_uparser_get_float(trim(key)//c_null_char, c_loc(tab))
        val = tab
    end subroutine uparser_get_vect_float

    subroutine uparser_get_double(key, val)
        character(len=*), intent(in) :: key
        real(kind=8),    intent(out) :: val

        real(kind=c_double), target :: tab(1)
        call c_uparser_get_double(trim(key)//c_null_char, c_loc(tab))
        val = tab(1)
    end subroutine uparser_get_double

    subroutine uparser_get_vect_double(key, val)
        character(len=*), intent(in) :: key
        real(kind=8),    intent(out) :: val(:)

        real(kind=c_double), dimension(size(val)), target :: tab
        call c_uparser_get_double(trim(key)//c_null_char, c_loc(tab))
        val = tab
    end subroutine uparser_get_vect_double
        
end module m_uparser_get
