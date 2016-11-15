#ifndef __UPARSER_ERROR_INL_H_
#define __UPARSER_ERROR_INL_H_
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
/// 3. Neither the name of the copyright holder nor the names of its contributors
///    may be used to endorse or promote products derived from this software
///    without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE copyright holder OR
/// ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
/// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file __uparser/error-inl.h
/// @author Issam SAID
/// @brief Private functions used to handle errors in uparser.    
///
#include <stdio.h>
#include <__uparser/config/guard.h>
#include <__uparser/config/log.h>

CPPGUARD_BEGIN();

extern void uparser_release();

#define UPARSER_FAIL(fmt,...)                                                  \
{                                                                              \
    fprintf(stderr, UPARSER_RED"[UPARSER FATAL]: "fmt" @%s:%d.\n"UPARSER_END,  \
            ##__VA_ARGS__, __FILE__, __LINE__);                                \
    exit(EXIT_FAILURE);                                                        \
}

#define UPARSER_FAIL_IF(predicate, fmt,...)                                    \
{                                                                              \
    if (predicate) {                                                           \
        fprintf(stderr,                                                        \
                UPARSER_RED"[UPARSER FATAL]: "fmt" @%s:%d.\n"UPARSER_END,      \
                ##__VA_ARGS__, __FILE__, __LINE__);                            \
        exit(EXIT_FAILURE);                                                    \
    }                                                                          \
}

#define UPARSER_EXIT(fmt,...)                                                  \
{                                                                              \
    fprintf(stderr, UPARSER_RED"[UPARSER ERR]: "fmt" @%s:%d.\n"UPARSER_END,    \
            ##__VA_ARGS__, __FILE__, __LINE__);                                \
    uparser_release();                                                         \
    exit(EXIT_FAILURE);                                                        \
}

#define UPARSER_EXIT_IF(predicate, fmt,...)                                    \
{                                                                              \
    if (predicate) {                                                           \
        fprintf(stderr,                                                        \
                UPARSER_RED"[UPARSER ERR]: "fmt" @%s:%d.\n"UPARSER_END,        \
                ##__VA_ARGS__, __FILE__, __LINE__);                            \
        uparser_release();                                                     \
        exit(EXIT_FAILURE);                                                    \
    }                                                                          \
}

CPPGUARD_END();

#endif  // __UPARSER_ERROR_INL_H_
