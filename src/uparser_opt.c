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
/// @file src/uparser_opt.c
/// @author Issam SAID
/// @brief Implementation of the core uparser put function 
///        which inserts a key value pair (an option) into 
///        the internal uparser lookup table. An option may 
///        or may not be set by the user.
///
#include <uparser/opt.h>
#include <__uparser/types-inl.h>
#include <__uparser/util-inl.h>
#include <__uparser/error-inl.h>

extern __uparser_t *up;

void uparser_opt(const char short_key,
                 const char *long_key, 
                 const char *default_value, const char *help_message) {
    __uparser_map_t *opt; 
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
 
        opt               = (__uparser_map_t*) malloc(sizeof(__uparser_map_t));
        opt->short_key    = short_key;
        opt->long_key     = (char*)malloc(sizeof(char)*strlen(long_key));
        sprintf(opt->long_key, "%s", long_key);
        opt->value        = (char*)malloc(sizeof(char)*strlen(default_value));
        sprintf(opt->value, "%s", default_value);
        opt->flags        = __UPARSER_OPT | (((strcmp(opt->value,  "true")==0) 
                                          || (strcmp(opt->value, "false")==0)) ? 
                                          __UPARSER_BOOL : 0x0);
        opt->help_message = (char*)malloc(sizeof(char)*strlen(help_message));
        sprintf(opt->help_message, "%s", help_message);

        if (short_key != 0) {
            urb_tree_put(&up->short_lookup, 
                         urb_tree_create(&opt->short_key, 
                                        (void*)opt), __uparser_char_cmp);
        }
        urb_tree_put(&up->long_lookup, 
                     urb_tree_create(opt->long_key, 
                                    (void*)opt), __uparser_str_cmp);
        up->nb_opts++;
    }
}
