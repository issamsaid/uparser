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
/// @file src/uparser_put.c
/// @author Issam SAID
/// @brief Implementation of the core uparser put function 
///        which inserts a key value pair into the internal 
///        uparser lookup structures.
///
#include <uparser/put.h>
#include <__uparser/types-inl.h>
#include <__uparser/util-inl.h>
#include <__uparser/error-inl.h>

extern uparser_t *up;

void uparser_put(const char short_key,
                 const char *long_key, 
                 const char *default_value, const char *help_message) {
    uparser_arg_t *arg; 
    if (up != NULL) {
        UPARSER_EXIT_IF(long_key == NULL || strlen(long_key) == 0, 
                        "the long key can not be empty");
        UPARSER_EXIT_IF(default_value == NULL || strlen(default_value) == 0, 
                        "the default value can not be empty");
        UPARSER_EXIT_IF(help_message == NULL || strlen(help_message) == 0, 
                        "the help message can not be empty");
        UPARSER_EXIT_IF((urb_tree_find(&up->long_lookup, 
                        (void*)long_key, __uparser_str_cmp) != &urb_sentinel), 
                        "long key '%s' is already taken", long_key);
        UPARSER_EXIT_IF((short_key != 0) && (urb_tree_find(&up->short_lookup, 
                        (void*)&short_key,__uparser_char_cmp) != &urb_sentinel), 
                        "short key '%c' is already taken", short_key);
 
        arg               = (uparser_arg_t*) malloc(sizeof(uparser_arg_t));
        arg->short_key    = short_key;
        arg->long_key     = (char*)malloc(sizeof(char)*strlen(long_key));
        sprintf(arg->long_key, "%s", long_key);
        arg->value        = (char*)malloc(sizeof(char)*strlen(default_value));
        sprintf(arg->value, "%s", default_value);
        arg->boolean      = ((strcmp(arg->value,  "true")==0) || 
                             (strcmp(arg->value, "false")==0)) ? true : false;
        arg->help_message = (char*)malloc(sizeof(char)*strlen(help_message));
        sprintf(arg->help_message, "%s", help_message);

        if (short_key != 0) {
            urb_tree_put(&up->short_lookup, 
                         urb_tree_create(&arg->short_key, 
                                        (void*)arg), __uparser_char_cmp);
        }
        urb_tree_put(&up->long_lookup, 
                     urb_tree_create(arg->long_key, 
                                    (void*)arg), __uparser_str_cmp);

    }
}
