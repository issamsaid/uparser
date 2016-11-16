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
/// SPECIAL, EXEMPLARY, OR CONsingleUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file src/single/single_get.c
/// @author Issam SAID
/// @brief
///
#include <uparser/single/get.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <__uparser/util-inl.h>
#include <__uparser/config/util.h>
#include <urb_tree/urb_tree.h>

extern uparser_t *up;

void uparser_get_bool_single(const char *key, bool *value) {
    urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be both empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    if (strcmp(vptr, "true") == 0) *value = true;
    else *value = false;
}

void uparser_get_char_single(const char *key, char *value) {
    int i; urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    int count = __uparser_str_tokcount(vptr, ",");
    char tmp[count][__UPARSER_STR_SIZE];
    __uparser_str_split(vptr, ",", count, tmp);
    for (i=0; i<count; i++) 
        value[i]  = tmp[i][0];
}

void uparser_get_string_single(const char *key, char *value) {
    urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    sprintf(value, "%s", vptr);
}

void uparser_get_int32_single(const char *key, int *value) {
    int i; urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    int count = __uparser_str_tokcount(vptr, ",");
    char tmp[count][__UPARSER_STR_SIZE];
    __uparser_str_split(vptr, ",", count, tmp);
    for (i=0; i<count; i++) 
        value[i] = atoi(tmp[i]);
}

void uparser_get_int64_single(const char *key, int64_t *value) {
    int i; urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    int count = __uparser_str_tokcount(vptr, ",");
    char tmp[count][__UPARSER_STR_SIZE];
    __uparser_str_split(vptr, ",", count, tmp);
    for (i=0; i<count; i++) 
        value[i] = atol(tmp[i]);
}

void uparser_get_float_single(const char *key, float *value) {
    int i; urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    int count = __uparser_str_tokcount(vptr, ",");
    char tmp[count][__UPARSER_STR_SIZE];
    __uparser_str_split(vptr, ",", count, tmp);
    for (i=0; i<count; i++) 
        value[i] = atof(tmp[i]);
}

void uparser_get_double_single(const char *key, double *value) {
    int i; urb_t *n; const char *vptr;
    UPARSER_EXIT_IF((key == NULL) || (strlen(key) == 0),
                    "key can not be empty");
    if (strlen(key)==1) {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, (void*)&key[0],
                        __uparser_char_cmp)) == &urb_sentinel,
                        "key '%c' not recognized", key[0]);
    } else {
        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, (void*)key,
                        __uparser_str_cmp)) == &urb_sentinel,
                        "key '%s' not recognized", key);
    }
    vptr = ((uparser_arg_t *)n->value)->value;
    int count = __uparser_str_tokcount(vptr, ",");
    char tmp[count][__UPARSER_STR_SIZE];
    __uparser_str_split(vptr, ",", count, tmp);
    for (i=0; i<count; i++) 
        value[i] = atof(tmp[i]);
}
