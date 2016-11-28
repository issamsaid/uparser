#ifndef __UPARSER_CONFIG_LOG_H_
#define __UPARSER_CONFIG_LOG_H_
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
/// @file config/log.h
/// @author Issam SAID
/// @brief Configuration file for logging in uparser.
///


///
/// @brief Set the verbose mode of uparser up.
///
#ifdef __VERBOSE
#endif // __VERBOSE          

///
/// @brief Set the debug mode of uparser up.
///
#ifdef __DEBUG

#ifndef __VERBOSE
#define __VERBOSE
#endif // __VERBOSE         

#endif // __DEBUG           

///
/// @brief Terminal colors.
///
#ifdef __VERBOSE
#define UPARSER_GREEN  "\x1B[32m"
#define UPARSER_PURPLE "\x1B[35m"
#define UPARSER_YELLOW "\x1B[33m"
#define UPARSER_RED    "\x1B[31m"
#define UPARSER_END    "\x1B[0m"
#else
#define UPARSER_GREEN  ""
#define UPARSER_PURPLE ""
#define UPARSER_YELLOW ""
#define UPARSER_RED    ""
#define UPARSER_END    ""
#endif  // __VERBOSE

#endif  // __UPARSER_CONFIG_LOG_H_