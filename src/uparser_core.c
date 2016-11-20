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
/// @file src/uparser_core.c
/// @author Issam SAID
/// @brief Implementation of the core uparser functions which include the 
///        initialization, help and the finalization.
///
#include <uparser/core.h>
#include <uparser/types.h>
#include <uparser/get.h>
#include <uparser/put.h>
#include <uparser/single/get.h>
#include <__uparser/util-inl.h>
#include <__uparser/error-inl.h>
#include <urb_tree/urb_tree.h>

///
/// @brief A static uparser object that will be used internally.
///
uparser_t *up = NULL;

void uparser_init(int argc, char** argv) {
    if (up == NULL) {
        up               = (uparser_t *)malloc(sizeof(uparser_t));
        up->exe_name     = (char *)malloc(sizeof(char)*strlen(argv[0]));
        up->short_lookup = &urb_sentinel;
        up->long_lookup  = &urb_sentinel;
        up->argc         = argc;
        up->argv         = argv;
        sprintf(up->exe_name, "%s", argv[0]);

        up->get_bool    = &uparser_get_bool_single;
        up->get_char    = &uparser_get_char_single;
        up->get_string  = &uparser_get_string_single;
        up->get_int32   = &uparser_get_int32_single;
        up->get_int64   = &uparser_get_int64_single;
        up->get_float   = &uparser_get_float_single;
        up->get_double  = &uparser_get_double_single;

    }
}

void uparser_parse() {
    char tmp[__UPARSER_STR_SIZE];
    char *key, *value, **saved_value;
    urb_t *n; int i, j; uparser_arg_t *arg;
    if (up != NULL) {
        for (i=1; i < up->argc; i++) {
            sprintf(tmp, "%s", up->argv[i]);
            key   = strtok(tmp, "=");
            if (__uparser_key_isshort(key)) {
                if((value = strtok(NULL, "=")) == NULL) {
                    /// a series of boolean arguments: values are not needed,
                    /// we set them equal to true internally (false otherwise).
                    for (j=1; j<strlen(key); j++) { 
                        if (key[j] == 'h') {
                            uparser_usage();
                        } else {
                            UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, 
                                        (void*)&key[j], 
                                         __uparser_char_cmp)) == &urb_sentinel, 
                                         "key '%c' is not recognized", key[j]);
                            arg         = (uparser_arg_t*)n->value;
                            saved_value = &arg->value;
                            UPARSER_EXIT_IF(!arg->boolean,
                                "invalid boolean argument, found non boolean"
                                "'%c' with no assigned value", key[1]);
                            if (strlen("true") > strlen(*saved_value)) {
                                free(*saved_value);
                                *saved_value = 
                                    (char*)malloc(sizeof(char)*strlen("true"));
                            }
                            sprintf(*saved_value, "%s", "true");
                        }
                    }
                } else {
                    /// this should be a short_key=value statement.
                    UPARSER_EXIT_IF(strlen(key) !=2, 
                                    "'%s' is an invalid short key", key);
                    UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, 
                                    (void*)&key[1], 
                                    __uparser_char_cmp)) == &urb_sentinel, 
                                    "key '%c' is not recognized", key[1]);
                    UPARSER_EXIT_IF(!__uparser_value_isvalid(value),
                                    "argument value '%s' is not valid", value);
                    arg         = (uparser_arg_t*)n->value;
                    saved_value = &arg->value;
                    UPARSER_EXIT_IF(arg->boolean,
                                    "boolean arguments don't take values, "
                                    "found boolean '%c=%s'", key[1], value);
                    if (strlen(value) > strlen(*saved_value)) {
                        free(*saved_value);
                        *saved_value = 
                            (char*)malloc(sizeof(char)*strlen(value));
                    }
                    sprintf(*saved_value, "%s", value);
                }
            } else if (__uparser_key_islong(key)) {
                if((value = strtok(NULL, "=")) == NULL) {
                    /// this should be a long boolean argument,
                    /// the value equal to true internally (false otherwise).
                    if (strcmp(&key[2], "help") == 0) {
                        uparser_usage();
                    } else {
                        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, 
                                        (void*)&key[2],
                                         __uparser_str_cmp)) == &urb_sentinel,
                                        "key '%s' is not recognized", key);
                        arg         = (uparser_arg_t*)n->value;
                        saved_value = &arg->value;
                        UPARSER_EXIT_IF(!arg->boolean,
                                "invalid boolean argument, found non boolean"
                                "'%s' with no assigned value", &key[2]);
                        if (strlen("true") > strlen(*saved_value)) {
                            free(*saved_value);
                            *saved_value = 
                                (char*)malloc(sizeof(char)*strlen("true"));
                        }
                        sprintf(*saved_value, "%s", "true");
                    }
                } else {
                    /// this should be a long_key=value statement.
                    UPARSER_EXIT_IF(!__uparser_value_isvalid(value), 
                                    "argument value '%s' is not valid", value);
                    if (__uparser_str_cmp(&key[2], UPARSER_FILE_KEYWORD) == 0) {
                        uparser_load(value);
                    } else {
                        UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, 
                                        (void*)&key[2],
                                         __uparser_str_cmp)) == &urb_sentinel,
                                        "key '%s' is not recognized", key);
                        arg         = (uparser_arg_t*)n->value;
                        saved_value = &arg->value;
                        UPARSER_EXIT_IF(arg->boolean,
                                    "boolean arguments don't take values, "
                                    "found boolean '%s=%s'", 
                                    &key[2], value);
                        if (strlen(value) > strlen(*saved_value)) {
                            free(*saved_value);
                            *saved_value = 
                                (char*)malloc(sizeof(char)*strlen(value));
                        }
                        sprintf(*saved_value, "%s", value);
                    }
                }
            } else UPARSER_EXIT("invalid key '%s'", key);            
        }    
    }
}

///
/// @details
/// When parsing from a file the syntax should be key=value.
/// "key" can be short or long but the dashes are not needed.
/// Boolean values should be explicit,i.e. key=true or key=false.
///
void uparser_load(const char *filename) {
    urb_t *n;
    char *s, *ch, *line, *save_line, *save_param;
    size_t file_size;
    char *file_content, **saved_value;
    if (up != NULL) {
        UPARSER_EXIT_IF((NULL == filename) || 
                        (strlen(filename) == 0), "filename not valid");
        UPARSER_EXIT_IF(!__uparser_file_exists(filename), 
                        "file '%s' not found", filename);
        file_size    = __uparser_file_size(filename);
        file_content = (char*)malloc(file_size*sizeof(char)+1);
        __uparser_file_read(file_content, file_size+1, filename);
        for(ch = file_content; ;ch = NULL) {
            line = strtok_r(ch, "\n", &save_line);
            if (line == NULL) break;
            __uparser_line_trim(line);
            if ((__uparser_line_isempty(line)) || 
                (__uparser_line_iscomment(line))) continue;
            UPARSER_EXIT_IF((s=strtok_r(line, "=", &save_param)) == NULL,
                            "invalid argument '%s' (= not found)", line);
            if (strlen(s)==1) {
                /// this should be a short_key=value statement.
                if (s[0] == 'h') { 
                    s = strtok_r(NULL, "=", &save_param);
                    UPARSER_EXIT_IF(!__uparser_value_isvalid(s),
                                    "argument value '%s' is not valid", s);
                    if (__uparser_str_cmp(s, "true") == 0) {
                        uparser_usage(); 
                        break; 
                    }
                }

                UPARSER_EXIT_IF((n=urb_tree_find(&up->short_lookup, 
                                (void*)&s[0], 
                                __uparser_char_cmp)) == &urb_sentinel, 
                                "key '%c' is not recognized", s[0]);
                s = strtok_r(NULL, "=", &save_param);
                UPARSER_EXIT_IF(!__uparser_value_isvalid(s),
                                "argument value '%s' is not valid", s);
                saved_value = &((uparser_arg_t*)n->value)->value;
                if (strlen(s) > strlen(*saved_value)) {
                    free(*saved_value);
                    *saved_value = (char*)malloc(sizeof(char)*strlen(s));
                }
                sprintf(*saved_value, "%s", s);
            } else {
                if (__uparser_str_cmp(s, UPARSER_FILE_KEYWORD) == 0) {
                    s = strtok_r(NULL, "=", &save_param);
                    UPARSER_EXIT_IF(!__uparser_value_isvalid(s), 
                                    "argument value '%s' is not valid", s);
                    uparser_load(s);
                } else if (__uparser_str_cmp(s, "help") == 0) {
                    s = strtok_r(NULL, "=", &save_param);
                    UPARSER_EXIT_IF(!__uparser_value_isvalid(s),
                                    "argument value '%s' is not valid", s);
                    if (__uparser_str_cmp(s, "true") == 0) {
                        uparser_usage(); 
                        break; 
                    }
                } else {
                    UPARSER_EXIT_IF((n=urb_tree_find(&up->long_lookup, 
                                    (void*)s,
                                    __uparser_str_cmp)) == &urb_sentinel,
                                    "key '%s' is not recognized", s);
                    /// this should be a long_key=value statement.
                    s = strtok_r(NULL, "=", &save_param);
                    UPARSER_EXIT_IF(!__uparser_value_isvalid(s), 
                                    "argument value '%s' is not valid", s);
                    saved_value = &((uparser_arg_t*)n->value)->value;
                    if (strlen(s) > strlen(*saved_value)) {
                        free(*saved_value);
                        *saved_value = (char*)malloc(sizeof(char)*strlen(s));
                    }
                    sprintf(*saved_value, "%s", s);
                }
            }
        }
        free(file_content);
    }
}

void uparser_usage() {
    if (up != NULL) {
        UPARSER_PRINT("");
        UPARSER_PRINT("USAGE  : %s [options]", up->exe_name);
        UPARSER_PRINT("");
        UPARSER_PRINT("OPTIONS:");
        UPARSER_PRINT("--%-12s%s%-10s %s",
                      "help", ", -h ", " ", "show this help message");
        UPARSER_PRINT("--%-12s%-10s %s",
                      UPARSER_FILE_KEYWORD, 
                      "     = [value] ", "load parameters from file");
        urb_tree_walk(&up->long_lookup, NULL, __uparser_arg_print);
        UPARSER_PRINT("");
    }
}

void uparser_release() {
    if (up != NULL) {
        urb_tree_delete(&up->long_lookup, NULL, __uparser_arg_del);
        free(up->exe_name); free(up); up = NULL;
    }
}
