#ifndef __UUPARSER_TYPES_H_
#define __UUPARSER_TYPES_H_
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
/// @file uparser/types.h
/// @author Issam SAID
/// @brief
///
#include <stdbool.h>
#include <stdint.h>
#include <uparser/flags.h>
#include <__uparser/config/guard.h>
#include <__uparser/config/util.h>
#include <urb_tree/urb_tree.h>

CPPGUARD_BEGIN();

typedef struct __uparser_arg_t {
    char short_key;
    char *long_key;
    char *help_message;
    char *value;
    bool boolean;
} uparser_arg_t;

typedef struct __uparser_t {
    char  *exe_name;
    int argc;
    char **argv;
    urb_t *short_lookup;
    urb_t *long_lookup;
} uparser_t;

typedef void (*uparser_get_bool_function_t)   (const char*, bool*);
typedef void (*uparser_get_char_function_t)   (const char*, char*);
typedef void (*uparser_get_string_function_t) (const char*, char*);
typedef void (*uparser_get_int32_function_t)  (const char*, int*);
typedef void (*uparser_get_int64_function_t)  (const char*, int64_t*);
typedef void (*uparser_get_float_function_t)  (const char*, float*);
typedef void (*uparser_get_double_function_t) (const char*, double*);

CPPGUARD_END();

#endif  // __UPARSER_TYPES_H_ 
