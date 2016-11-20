#ifndef __UPARSER_UTIL_INL_H_
#define __UPARSER_UTIL_INL_H_
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
/// @file __uparser/util-inl.h
/// @author Issam SAID
/// @brief Private functions used by the uparser utilities.    
///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <uparser/types.h>
#include <__uparser/error-inl.h>
#include <__uparser/config/guard.h>
#include <__uparser/config/util.h>
#include <__uparser/config/private.h>
#include <__uparser/config/log.h>

CPPGUARD_BEGIN();

#ifdef  __UPARSER_DEBUG
#define UPARSER_DEBUG(fmt,...)                                                 \
{                                                                              \
    fprintf(stdout,                                                            \
            UPARSER_PURPLE"[UPARSER DBG]: "fmt"\n"UPARSER_END, ##__VA_ARGS__); \
}
#else 
#define UPARSER_DEBUG(fmt,...) 
#endif  // __UPARSER_DEBUG

#ifdef __UPARSER_VERBOSE                             
#define UPARSER_PRINT(fmt,...)                                                 \
{                                                                              \
    fprintf(stdout,                                                            \
            UPARSER_GREEN"[UPARSER MSG]: "fmt"\n"UPARSER_END, ##__VA_ARGS__);  \
}
#define UPARSER_WARN(fmt,...)                                                  \
{                                                                              \
    fprintf(stdout,                                                            \
            UPARSER_YELLOW"[UPARSER WRN]: "fmt"\n"UPARSER_END, ##__VA_ARGS__); \
}
#define UPARSER_WARN_IF(predicate, fmt,...)                                    \
{                                                                              \
    if (predicate) {                                                           \
        fprintf(stdout,                                                        \
                UPARSER_YELLOW"[UPARSER WRN]: "fmt"\n"UPARSER_END,             \
                ##__VA_ARGS__);                                                \
    }                                                                          \
}
#else 
#define UPARSER_PRINT(fmt,...) 
#define UPARSER_WARN(fmt,...) 
#define UPARSER_WARN_IF(fmt,...) 
#endif  // __UPARSER_VERBOSE 

__UPARSER_PRIVATE void
__uparser_ptr_del(void *ptr) { free(ptr); }

__UPARSER_PRIVATE int
__uparser_char_cmp(void *c, void *d) {
    return *(char*)c - *(char*)d;
}

__UPARSER_PRIVATE int
__uparser_str_cmp(void *cur, void *otr) {
    return strcmp((char*)cur, (char*)otr);
}

__UPARSER_PRIVATE int
__uparser_str_tokcount(const char *str, char *delim) {
    int j = 0, count = 1;
    for (j=0; j<strlen(str) ; ++j)
        if (str[j] == delim[0]) count++;
    return count;
}

__UPARSER_PRIVATE void
__uparser_str_split(const char *str, 
                    char *delim, int count, 
                    char toks[count][__UPARSER_STR_SIZE]) {
    int i=0; char *pch; char tmp[__UPARSER_STR_SIZE];
    sprintf(tmp, "%s", str);
    pch = strtok(tmp, delim);
    while (pch != NULL) {
        sprintf(toks[i++], "%s", pch);
        pch = strtok(NULL, delim);
    }
}

__UPARSER_PRIVATE bool
__uparser_file_exists(const char* filename) {
    FILE* fd = NULL;
    if ((fd = fopen(filename, "rb")) == NULL) {
        return false;
    } else {
        fclose(fd);
        return true;        
    }
}

__UPARSER_PRIVATE size_t
__uparser_file_size(const char* filename) {
    FILE* fd = NULL;
    size_t size;
    UPARSER_EXIT_IF((fd = fopen(filename, "rb"))==NULL,
               "file '%s' not found", filename);
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fclose(fd);
    return size;
}

__UPARSER_PRIVATE void
__uparser_file_read(char* buffer, size_t size, const char* filename) {
    FILE* fd = NULL;
    UPARSER_EXIT_IF((fd = fopen(filename, "rb"))==NULL,
                "file '%s' not found", filename);
    if (fread(buffer, 1, size-1, fd) != (size-1)) {        
        fclose(fd);
        UPARSER_EXIT("couldn't read file '%s'", filename);
    }
    fclose(fd);
    buffer[size-1] = '\0';
}

__UPARSER_PRIVATE void
__uparser_line_trim(char *line){
    int i;                                            
    while(isspace(*line)) line++;                     
    for(i = strlen(line)-1; (isspace(line[i])); i--); 
    line[i+1] = '\0';
}

__UPARSER_PRIVATE bool
__uparser_line_iscomment(const char *line) {
    return (line[0]=='#');
}

__UPARSER_PRIVATE bool
__uparser_line_isempty(const char *line) {
    return ((NULL == line) || (strlen(line) == 0));
}

__UPARSER_PRIVATE bool
__uparser_key_isshort(const char *key) {
    int i;
    if ((key == NULL)     || 
        (strlen(key) < 2) || 
        (key[0] != '-')   || 
        (key[1] == '-')) return false;
    for (i=1; i<strlen(key); i++) 
        if ((!isalnum(key[i])) || (isspace(key[i]))) return false;
    return true;
}

__UPARSER_PRIVATE bool
__uparser_key_islong(const char *key) {
    int i;
    if ((key == NULL)     || 
        (strlen(key) < 4) || 
        (key[0] != '-')   ||
        (key[1] != '-')) return false;
    for (i=2; i<strlen(key); i++) if (! isalnum(key[i])) return false;
    return true;
}

__UPARSER_PRIVATE bool
__uparser_value_isvalid(const char *value) {
    return (NULL != value) && (strlen(value) != 0);
}

__UPARSER_PRIVATE void 
__uparser_arg_print(void *ptr) {
    uparser_arg_t *arg = (uparser_arg_t *)ptr;
    UPARSER_PRINT("--%-12s%s%s%c%s%-10s %s",
                  arg->long_key,
                  arg->short_key ? ", "           : " ",
                  arg->short_key ? "-"            : " ",
                  arg->short_key ? arg->short_key : ' ',
                  arg->short_key ? " "            : "  ",
                  arg->boolean   ? " "            : "= [value]",
                  arg->help_message);
}

__UPARSER_PRIVATE void 
__uparser_arg_del(void *ptr) {
    if (ptr) {
        uparser_arg_t *arg = (uparser_arg_t *)ptr;
        free(arg->long_key);
        free(arg->value);
        free(arg->help_message);
        arg = NULL;
    }
}

CPPGUARD_END();

#endif  // __UPARSER_UTIL_INL_H_