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
/// @file src/single/base.c
/// @author Issam SAID
/// @brief
///
#include <uparser/single/base.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uparser/error.h>

///
/// @brief
///
///
/// @param
/// @return
///
int uparser_single_init(int argc, char** argv, char* file_keyword) {
    int i, j, idx;
    char *key, *value;
    parser_handler *file_parser = NULL;
    bool param_file_checked; 
    pool.nb_hdlrs           = 0;
    pool.cmd_psr.nb_params  = 0;
    UPARSER_EXIT_IF(argc >= PARSER_MAX_PARAMS, 
                    "can't handle more then %d arguments", UPARSER_MAX_PARAMS);

    param_file_checked = (NULL != file_keyword);

    for (i=0; i<argc; ++i) {
        UPARSER_CHECK_PARAM_VALID(argv[i]);
        key   = strtok(argv[i], "=");
        value = strtok(NULL, "=");
        UPARSER_EXIT_IF(parser_append_param(NULL, key, value, file_keyword),
                        "failed to append a uparser argument to the list");
    }
    return EXIT_SUCCESS;
}

void parser_info() {
    int i, h;
    fprintf(stdout, "parser info:\n");
    fprintf(stdout, "-> cmdline parser:\n");
    for (i=0; i < pool.cmd_psr.nb_params; ++i) {
        fprintf(stdout, "\t%2d: %-15s = %-15s\n",
                i, pool.cmd_psr.params[i].key, pool.cmd_psr.params[i].value);
    }
    for (h=0; h < pool.nb_hdlrs; ++h) {
        fprintf(stdout, "-> handler for '%s':\n", pool.hdlrs[h].filename);
        for (i=0; i < pool.hdlrs[h].psr.nb_params; ++i) {
            fprintf(stdout, "\t%2d: %-15s = %-15s\n",
                    i, pool.hdlrs[h].psr.params[i].key,
                    pool.hdlrs[h].psr.params[i].value);
        }
    }
}


///
/// Static functions implementations.
///
int parser_find_param(const char* filename, 
                      char* key, parser **p, char *error_msg) {
    int ip, i;
    parser *iter = &pool.cmd_psr;
    if ((NULL == key) || (strlen(key)==0))
        PARSER_FAIL(error_msg, "invalid key");
    if ((NULL != filename) && (strlen(filename) != 0)) {
        for (ip=0; ip < pool.nb_hdlrs; ++ip)
            if (strcmp(pool.hdlrs[ip].filename, filename) == 0) {
                iter = &pool.hdlrs[ip].psr;
                for (i=0; i < iter->nb_params; ++i) {
                    if(strcmp(iter->params[i].key, key) == 0) {
                        *p = iter;
                        return i;
                    }
                }
            }
        PARSER_FAIL(error_msg, "handler for '%s' not found", filename);
    } else {
        for (i=0; i < iter->nb_params; ++i) {
            if(strcmp(iter->params[i].key, key) == 0) {
                *p = iter;
                return i;
            }       
        }
        for (ip=pool.nb_hdlrs-1; ip >= 0; --ip) {
            iter = &pool.hdlrs[ip].psr;
            for (i=0; i < iter->nb_params; ++i) {
                if(strcmp(iter->params[i].key, key) == 0) {
                    *p = iter;
                    return i;
                }
            }
        }
    }
    PARSER_FAIL(error_msg, "param '%s' not found", key);
}

int parser_append_handler(const char *filename, char *error_msg) {
    int j = 0;
    if ((NULL == filename) || (strlen(filename) == 0))
        PARSER_FAIL(error_msg, "invalid filename");
    for (j=0; j<pool.nb_hdlrs; j++)
        if (strcmp(pool.hdlrs[j].filename, filename) == 0) break;
    if (j >= PARSER_MAX_HANDLERS)
        PARSER_FAIL(error_msg, "too many handlers");
    sprintf(pool.hdlrs[j].filename, "%s", filename);
    pool.hdlrs[j].psr.nb_params = 0;
    if (j == pool.nb_hdlrs) pool.nb_hdlrs++; 
    return j;
}

#define PARSER_TRIM_LINE(line)                        \
    int i;                                            \
    while(isspace(*line)) line++;                     \
    for(i = strlen(line)-1; (isspace(line[i])); i--); \
    line[i+1] = '\0';

// line should be trimmed before 
#define PARSER_LINE_IS_COMMENT(line) \
    (line[0]=='#') 

#define PARSER_LINE_IS_EMPTY(line)  \
    ((NULL == line) || (strlen(line) == 0)) ? 1 : 0    

int parser_append_param(parser *p, char *key, char *value,
                        const char *file_keyword,  char *error_msg) {    
    int j;
    if (NULL == p) p = &pool.cmd_psr;
    if ((NULL == key) || (strlen(key) == 0) ||
        (NULL == value) || (strlen(value) == 0)) {
        PARSER_FAIL(error_msg, "invalid key (%s) or value (%s)", key, value);
    }
    if ((strlen(key) >= PARSER_MAX_STR) || (strlen(value) >= PARSER_MAX_STR))
        PARSER_FAIL(error_msg, "key (%s) or value (%s) too big", key, value);
    if ((NULL != file_keyword) && (strcmp(key, file_keyword) == 0))
        return parser_append_file(file_keyword, value, error_msg);
    for (j=0; j<p->nb_params; ++j)
        if (strcmp(p->params[j].key, key) == 0) break;
    if (j >= PARSER_MAX_PARAMS)
        PARSER_FAIL(error_msg, "too many parameters");
    sprintf(p->params[j].key, "%s\0", key);
    sprintf(p->params[j].value, "%s\0", value);
    if (j == p->nb_params) p->nb_params++;
    return SUCCESS;
}

int parser_append_file(const char *file_keyword, 
                       const char *filename, char *error_msg) {    
    int i, idx;
    FILE *fp;
    char *ch, *line, *save_line, *save_param;
    size_t file_size;
    char *file_content;
    char *file_key, *file_value;
    parser *file_p;
    if ((NULL != filename) && (strlen(filename) > 0)) {
        if ((idx = parser_append_handler(filename, error_msg)) != FAILURE) {
            file_p = &pool.hdlrs[idx].psr;
            if ((fp = fopen(filename, "rb")) == NULL)
                PARSER_FAIL(error_msg, "file '%s' not found", filename);
            fseek(fp, 0, SEEK_END);
            file_size = ftell(fp);
            rewind(fp);
            file_content = (char*)malloc(file_size*sizeof(char));
            if (fread(file_content, 1, file_size, fp) < file_size)
                PARSER_FAIL(error_msg, "failed to read file '%s'", filename);
            fclose(fp);
            file_content[file_size-1] = '\0';
            for(ch = file_content; ;ch = NULL) {
                line = strtok_r(ch, "\n", &save_line);
                if (line == NULL) break;
                PARSER_TRIM_LINE(line);
                if ((PARSER_LINE_IS_EMPTY(line)) || 
                    (PARSER_LINE_IS_COMMENT(line))) continue;
                PARSER_CHECK_PARAM_VALID(line, error_msg);
                file_key   = strtok_r(line, "=", &save_param);
                file_value = strtok_r(NULL, "=", &save_param);

                parser_append_param(file_p, file_key, 
                                    file_value, file_keyword, error_msg);   
            }
            free(file_content);
        } return SUCCESS;
    } else {
        PARSER_FAIL(error_msg, "failed to append file '%s'", filename);
    }
}
