#ifndef __UPARSER_GET_H_
#define __UPARSER_GET_H_
///
/// @copyright Copyright (c) 2016-, Issam SAID <said.issam@gmail.com>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
///
/// 1. Redistributions of source code must retain the above copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. Neither the name of the copyright holder nor the names of its
///    contributors may be used to endorse or promote products derived from
///    this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
/// HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file uparser/get.h
/// @author Issam SAID
/// @brief
///
#include <uparser/types.h>
#include <__uparser/config/guard.h>

CPPGUARD_BEGIN();

extern uparser_get_bool_function_t    uparser_get_bool;
extern uparser_get_char_function_t    uparser_get_char;
extern uparser_get_string_function_t  uparser_get_string;
extern uparser_get_int32_function_t   uparser_get_int32;
extern uparser_get_int64_function_t   uparser_get_int64;
extern uparser_get_float_function_t   uparser_get_float;
extern uparser_get_double_function_t  uparser_get_double;

CPPGUARD_END();

#endif // __UPARSER_GET_H_
