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
#ifdef __UPARSER_MPI
#include <uparser/mpi_stub.h>
#endif // __UPARSER_MPI

///
/// @brief
///
///
/// @param
/// @return
///
int uparser_single_init(int argc, char** argv) {
    int i, j, idx;
    char *key, *value;
    uparser_handler_t *file_parser = NULL;
    bool param_file_checked; 
    pool.nb_hdlrs           = 0;
    pool.cmd_psr.nb_params  = 0;
    if (argc >= PARSER_MAX_PARAMS)
        PARSER_FAIL(error_msg, "can't handle more then %d arguments",
                    PARSER_MAX_PARAMS);

    if (NULL != file_keyword) param_file_checked = false;
    else param_file_checked = true;

    for (i=0; i<argc; ++i) {
        PARSER_CHECK_PARAM_VALID(argv[i], error_msg);
        key   = strtok(argv[i], "=");
        value = strtok(NULL, "=");
        if (parser_append_param(NULL, key, 
                                value, file_keyword, error_msg) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int parser_init_mpi(int argc, char** argv, char* file_keyword,
                    int rank, int communicator, char* error_msg) {
    mpi_rank         = rank;
    mpi_communicator = communicator;
    mpi_enabled      = true;
    mpi_bcast_on     = true;
    if (rank == 0) {
        return parser_init(argc, argv, file_keyword, error_msg);
    } else {
        return SUCCESS;
    }
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

void parser_enable_bcast() {
    mpi_bcast_on = true;
}

void parser_disable_bcast() {
    mpi_bcast_on = false;
}

bool parser_exist(const char* filename, char *key, char *key2) {
    if (mpi_enabled)
        return parser_exist_mpi(filename, key, key2);
    else
        return parser_exist_seq(filename, key, key2);
}

void parser_get_bool(const char* filename,
                     char *key, bool *value,
                     bool default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_bool_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_bool_seq(filename, key, value, default_value, key2);
}

void parser_get_char(const char* filename,
                     char *key, char *value,
                     char default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_char_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_char_seq(filename, key, value, default_value, key2);
}

void parser_get_string(const char* filename,
                      char *key, char *value,
                      char *default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_string_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_string_seq(filename, key, value, default_value, key2);
}

void parser_get_int32(const char* filename,
                      char *key, int *value,
                      int default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_int32_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_int32_seq(filename, key, value, default_value, key2);
}

void parser_get_int64(const char* filename,
                      char *key, int64_t *value,
                      int64_t default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_int64_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_int64_seq(filename, key, value, default_value, key2);
}

void parser_get_float(const char* filename,
                      char *key, float *value,
                      float default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_float_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_float_seq(filename, key, value, default_value, key2);
}

void parser_get_double(const char* filename,
                       char *key, double *value,
                       double default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_double_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_double_seq(filename, key, value, default_value, key2);
}

void parser_getlist_bool(const char* filename,
                     char *key, bool *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_bool_mpi(filename, key, value, key2);
    else
        return parser_getlist_bool_seq(filename, key, value, key2);
}

void parser_getlist_char(const char* filename,
                     char *key, char *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_char_mpi(filename, key, value, key2);
    else
        return parser_getlist_char_seq(filename, key, value, key2);
}

void parser_getlist_string(const char* filename,
                      char *key, char **value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_string_mpi(filename, key, value, key2);
    else
        return parser_getlist_string_seq(filename, key, value, key2);
}

void parser_getlist_int32(const char* filename,
                      char *key, int *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_int32_mpi(filename, key, value, key2);
    else
        return parser_getlist_int32_seq(filename, key, value, key2);
}

void parser_getlist_int64(const char* filename,
                      char *key, int64_t *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_int64_mpi(filename, key, value, key2);
    else
        return parser_getlist_int64_seq(filename, key, value, key2);
}

void parser_getlist_float(const char* filename,
                      char *key, float *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_float_mpi(filename, key, value, key2);
    else
        return parser_getlist_float_seq(filename, key, value, key2);
}

void parser_getlist_double(const char* filename,
                       char *key, double *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_double_mpi(filename, key, value, key2);
    else
        return parser_getlist_double_seq(filename, key, value, key2);
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


void parser_get_bool_seq(const char* filename,
                         char *key, bool *value,
                         bool default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
            ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        (*value) = default_value;
        return;
    }
    
    if (strcmp(p->params[i].value, "true") == 0) {
        (*value) = true;
    } else if (strcmp(p->params[i].value, "false") == 0) {
        (*value) = false;
    } else {
        (*value) = default_value;
    }
}

void parser_get_bool_mpi(const char* filename,
                         char *key, bool *value, 
                         bool default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_bool_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_C_BOOL, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser error: bcast failed\n");
            exit(-1);
        }
    }
}

void parser_get_char_seq(const char* filename,
                         char *key, char *value,
                         char default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        value[0] = default_value;
    else
        value[0] = p->params[i].value[0];
}

void parser_get_char_mpi(const char* filename,
                         char *key, char *value,
                         char default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_char_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_CHAR, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char failed\n");
            exit(-1);
        }
    }
}

void parser_get_string_seq(const char* filename,
                           char *key, char *value,
                           char *default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        sprintf(value, "%s\0", default_value);
    else
        sprintf(value, "%s\0", p->params[i].value);
}

void parser_get_string_mpi(const char* filename,
                           char *key, char *value,
                           char *default_value, char *key2) {
    int len;
    if (mpi_rank == 0) {
        parser_get_string_seq(filename, key, value, default_value, key2);
        len = strlen(value);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&len, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr,
                    "fatal parser MPI error: bcast string length failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, len, MPI_CHAR, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast string failed\n");
            exit(-1);
        }
        value[len]='\0';
    }
}

void parser_get_int32_seq(const char* filename,
                          char *key, int *value,
                          int default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        (*value) = default_value;
    } else {
        (*value) = atoi(p->params[i].value);
    }
}

void parser_get_int32_mpi(const char* filename,
                          char *key, int *value,
                          int default_value, char *key2) {
    if (mpi_rank == 0) {
        parser_get_int32_seq(filename, key, value, default_value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast int32 failed\n");
            exit(-1);
        }
    }
}

void parser_get_int64_seq(const char* filename,
                          char *key, int64_t *value,
                          int64_t default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        (*value) = default_value;
    else
        (*value) = atol(p->params[i].value);
}

void parser_get_int64_mpi(const char* filename,
                          char *key, int64_t *value,
                          int64_t default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_int64_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_LONG, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast int64 failed\n");
            exit(-1);
        }
    }
}

void parser_get_float_seq(const char* filename,
                          char *key, float *value,
                          float default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        (*value) = default_value;
    else
        (*value) = atof(p->params[i].value);
}

void parser_get_float_mpi(const char* filename,
                          char *key, float *value,
                          float default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_float_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_FLOAT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast float failed\n");
            exit(-1);
        }
    }
}

void parser_get_double_seq(const char* filename,
                           char *key, double *value,
                           double default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        (*value) = default_value;
    else
        (*value) = atof(p->params[i].value);
}

void parser_get_double_mpi(const char* filename,
                           char *key, double *value,
                           double default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_double_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_DOUBLE, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast double failed\n");
            exit(-1);
        }
    }
}

int parser_list_count(const char *filename, char *key, char *key2) {
    int i, j = 0, count = 1; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        return 0;
    for (j=0; j<strlen(p->params[i].value) ; ++j)
        if (p->params[i].value[j] == ',') count++;
    return count;
}

void parser_list_to_bool(char *value, bool *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        if (strcmp(pch, "true") == 0) {
            list[i] = true;
        } else if (strcmp(pch, "false") == 0) {
            list[i] = false;
        } else {
            fprintf(stderr, "fatal parser error: bool is true or false\n");
            exit(-1);
        }
        i++;
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_char(char *value, char *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = pch[0];
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_string(char *value, char **list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        sprintf(list[i++], "%s\0", pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_int32(char *value, int *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atoi(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_int64(char *value, int64_t *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atol(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_float(char *value, float *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atof(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_double(char *value, double *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atof(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_getlist_bool_seq(const char* filename,
                             char *key, bool *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_bool(p->params[i].value, value);
}

void parser_getlist_bool_mpi(const char* filename,
                             char *key, bool *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_bool_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_C_BOOL, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast bool list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_char_seq(const char* filename,
                             char *key, char *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_char(p->params[i].value, value);
}

void parser_getlist_char_mpi(const char* filename,
                             char *key, char *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_char_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_CHAR, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_string_seq(const char* filename,
                               char *key, char **value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_string(p->params[i].value, value);
}

void parser_getlist_string_mpi(const char* filename,
                               char *key, char **value, char *key2) {
    int count, len, i;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_string_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        for (i=0; i<count; ++i) {
            if (mpi_rank == 0) len = strlen(value[i]);
            if (MPI_Bcast((void*)&len, 1, MPI_INT, 0, mpi_communicator)) {
                fprintf(stderr, "fatal parser MPI error: bcast len failed\n");
                exit(-1);
            }
            if (MPI_Bcast((void*)value[i],
                          len, MPI_CHAR, 0, mpi_communicator)) {
                fprintf(stderr,
                        "fatal parser MPI error: bcast char list failed\n");
                exit(-1);
            }
        }
    }
}

void parser_getlist_int32_seq(const char* filename,
                              char *key, int *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_int32(p->params[i].value, value);
}

void parser_getlist_int32_mpi(const char* filename,
                              char *key, int *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_int32_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_int64_seq(const char* filename,
                              char *key, int64_t *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_int64(p->params[i].value, value);
}

void parser_getlist_int64_mpi(const char* filename,
                              char *key, int64_t *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_int64_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_LONG, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_float_seq(const char* filename,
                              char *key, float *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_float(p->params[i].value, value);
}

void parser_getlist_float_mpi(const char* filename,
                              char *key, float *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_float_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_FLOAT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_double_seq(const char* filename,
                               char *key, double *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_double(p->params[i].value, value);
}

void parser_getlist_double_mpi(const char* filename,
                               char *key, double *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_double_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_DOUBLE, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

bool parser_exist_seq(const char *filename, char *key, char *key2) {
    parser *p = NULL;
    return parser_find_param(filename, key, &p, NULL) != FAILURE;
}

bool parser_exist_mpi(const char *filename, char *key, char *key2) {
    bool res;
    if (mpi_rank == 0)
        res = parser_exist_seq(filename, key, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&res, 1, MPI_C_BOOL, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast bool failed\n");
            exit(-1);
        }
    }
    return res;
}
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
/// @file src/uparser_base.c
/// @author Issam SAID
/// @brief
///
#include <uparser/base.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __UPARSER_MPI
#include <uparser/mpi_stub.h>
#endif // __UPARSER_MPI

/// Parser internal macros.
#define PARSER_FAIL(error_msg, msg, ...)                        \
    {                                                           \
        if (error_msg != NULL)                                  \
            sprintf(error_msg, "parser error: "msg" @%s:%d\0",  \
                    ##__VA_ARGS__, __FILE__, __LINE__);         \
        return FAILURE;                                         \
    }

#define PARSER_CHECK_PARAM_VALID(str, error_msg)                        \
    if (strstr(str, "=") == NULL)                                       \
        PARSER_FAIL(error_msg, "invalid param '%s' (= not found)", str);

/// Static functions headers.
static inline 
int parser_append_handler(const char *filename, char *error_msg);

static inline 
int parser_append_param(parser *p, char *key, char *value, 
                        const char* file_keyword, char *error_msg);
static inline 
int parser_find_param(const char *filename, char* key, 
                      parser **p, char *error_msg);
static inline
void parser_get_bool_seq(const char* filename,
                         char *key, bool *value,
                         bool default_value, char *key2);
static inline 
void parser_get_bool_mpi(const char* filename,
                         char *key, bool *value,
                         bool default_value, char *key2);
static inline
void parser_get_char_seq(const char* filename,
                         char *key, char *value,
                         char default_value, char *key2);
static inline 
void parser_get_char_mpi(const char* filename,
                         char *key, char *value,
                         char default_value, char *key2);
static inline 
void parser_get_string_seq(const char* filename,
                           char *key, char *value,
                           char *default_value, char *key2);
static inline 
void parser_get_string_mpi(const char* filename,
                           char *key, char *value,
                           char *default_value, char *key2);
static inline 
void parser_get_int32_seq(const char* filename,
                          char *key, int *value,
                          int default_value, char *key2);
static inline 
void parser_get_int32_mpi(const char* filename,
                          char *key, int *value,
                          int default_value, char *key2);
static inline 
void parser_get_int64_seq(const char* filename,
                          char *key, int64_t *value,
                          int64_t default_value, char *key2);
static inline 
void parser_get_int64_mpi(const char* filename,
                          char *key, int64_t *value,
                          int64_t default_value, char *key2);
static inline 
void parser_get_float_seq(const char* filename,
                          char *key, float *value,
                          float default_value, char *key2);
static inline 
void parser_get_float_mpi(const char* filename,
                          char *key, float *value,
                          float default_value, char *key2);
static inline 
void parser_get_double_seq(const char* filename,
                           char *key, double *value,
                           double default_value, char *key2);
static inline 
void parser_get_double_mpi(const char* filename,
                           char *key, double *value,
                           double default_value, char *key2);

static inline void parser_list_to_bool(char *value, bool *list);
static inline void parser_list_to_char(char *value, char *list);
static inline void parser_list_to_string(char *value, char **list);
static inline void parser_list_to_int32(char *value, int *list);
static inline void parser_list_to_int64(char *value, int64_t *list);
static inline void parser_list_to_float(char *value, float *list);
static inline void parser_list_to_double(char *value, double *list);

static inline void parser_getlist_bool_seq(const char* filename,
                                           char *key, bool *value, char *key2);
static inline void parser_getlist_bool_mpi(const char* filename,
                                           char *key, bool *value, char *key2);
static inline void parser_getlist_char_seq(const char* filename,
                                           char *key, char *value, char *key2);
static inline void parser_getlist_char_mpi(const char* filename,
                                           char *key, char *value, char *key2);
static inline void parser_getlist_string_seq(const char* filename,
                                             char *key,
                                             char **value,char *key2);
static inline void parser_getlist_string_mpi(const char* filename,
                                             char *key,
                                             char **value,char *key2);
static inline void parser_getlist_int32_seq(const char* filename,
                                            char *key, int *value, char *key2);
static inline void parser_getlist_int32_mpi(const char* filename,
                                            char *key, int *value, char *key2);
static inline void parser_getlist_int64_seq(const char* filename, char *key, 
                                            int64_t *value, char *key2);
static inline void parser_getlist_int64_mpi(const char* filename, char *key,
                                            int64_t *value, char *key2);
static inline void parser_getlist_float_seq(const char* filename, char *key,
                                            float *value, char *key2);
static inline void parser_getlist_float_mpi(const char* filename, char *key,
                                            float *value, char *key2);
static inline void parser_getlist_double_seq(const char* filename, char *key,
                                             double *value, char *key2);
static inline void parser_getlist_double_mpi(const char* filename, char *key,
                                             double *value, char *key2);

static inline bool parser_exist_seq(const char *filename,
                                    char *key, char *key2);
static inline bool parser_exist_mpi(const char *filename,
                                    char *key, char *key2);

/// Static parsers.
static parser_pool pool;
static int         mpi_rank;
static int         mpi_communicator;
static bool        mpi_enabled  = false;
static bool        mpi_bcast_on = false;

/// Functions implementations.
int parser_init(int argc, char** argv,
                char* file_keyword, char* error_msg) {
    int i, j, idx;
    char *key, *value;
    parser_handler *file_parser = NULL;
    bool param_file_checked; 
    pool.nb_hdlrs           = 0;
    pool.cmd_psr.nb_params  = 0;
    if (argc >= PARSER_MAX_PARAMS)
        PARSER_FAIL(error_msg, "can't handle more then %d arguments",
                    PARSER_MAX_PARAMS);

    if (NULL != file_keyword) param_file_checked = false;
    else param_file_checked = true;

    for (i=0; i<argc; ++i) {
        PARSER_CHECK_PARAM_VALID(argv[i], error_msg);
        key   = strtok(argv[i], "=");
        value = strtok(NULL, "=");
        if (parser_append_param(NULL, key, 
                                value, file_keyword, error_msg) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int parser_init_mpi(int argc, char** argv, char* file_keyword,
                    int rank, int communicator, char* error_msg) {
    mpi_rank         = rank;
    mpi_communicator = communicator;
    mpi_enabled      = true;
    mpi_bcast_on     = true;
    if (rank == 0) {
        return parser_init(argc, argv, file_keyword, error_msg);
    } else {
        return SUCCESS;
    }
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

void parser_enable_bcast() {
    mpi_bcast_on = true;
}

void parser_disable_bcast() {
    mpi_bcast_on = false;
}

bool parser_exist(const char* filename, char *key, char *key2) {
    if (mpi_enabled)
        return parser_exist_mpi(filename, key, key2);
    else
        return parser_exist_seq(filename, key, key2);
}

void parser_get_bool(const char* filename,
                     char *key, bool *value,
                     bool default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_bool_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_bool_seq(filename, key, value, default_value, key2);
}

void parser_get_char(const char* filename,
                     char *key, char *value,
                     char default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_char_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_char_seq(filename, key, value, default_value, key2);
}

void parser_get_string(const char* filename,
                      char *key, char *value,
                      char *default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_string_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_string_seq(filename, key, value, default_value, key2);
}

void parser_get_int32(const char* filename,
                      char *key, int *value,
                      int default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_int32_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_int32_seq(filename, key, value, default_value, key2);
}

void parser_get_int64(const char* filename,
                      char *key, int64_t *value,
                      int64_t default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_int64_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_int64_seq(filename, key, value, default_value, key2);
}

void parser_get_float(const char* filename,
                      char *key, float *value,
                      float default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_float_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_float_seq(filename, key, value, default_value, key2);
}

void parser_get_double(const char* filename,
                       char *key, double *value,
                       double default_value, char *key2) {
    if (mpi_enabled)
        return parser_get_double_mpi(filename, key, value, default_value, key2);
    else
        return parser_get_double_seq(filename, key, value, default_value, key2);
}

void parser_getlist_bool(const char* filename,
                     char *key, bool *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_bool_mpi(filename, key, value, key2);
    else
        return parser_getlist_bool_seq(filename, key, value, key2);
}

void parser_getlist_char(const char* filename,
                     char *key, char *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_char_mpi(filename, key, value, key2);
    else
        return parser_getlist_char_seq(filename, key, value, key2);
}

void parser_getlist_string(const char* filename,
                      char *key, char **value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_string_mpi(filename, key, value, key2);
    else
        return parser_getlist_string_seq(filename, key, value, key2);
}

void parser_getlist_int32(const char* filename,
                      char *key, int *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_int32_mpi(filename, key, value, key2);
    else
        return parser_getlist_int32_seq(filename, key, value, key2);
}

void parser_getlist_int64(const char* filename,
                      char *key, int64_t *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_int64_mpi(filename, key, value, key2);
    else
        return parser_getlist_int64_seq(filename, key, value, key2);
}

void parser_getlist_float(const char* filename,
                      char *key, float *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_float_mpi(filename, key, value, key2);
    else
        return parser_getlist_float_seq(filename, key, value, key2);
}

void parser_getlist_double(const char* filename,
                       char *key, double *value, char *key2) {
    if (mpi_enabled)
        return parser_getlist_double_mpi(filename, key, value, key2);
    else
        return parser_getlist_double_seq(filename, key, value, key2);
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


void parser_get_bool_seq(const char* filename,
                         char *key, bool *value,
                         bool default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
            ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        (*value) = default_value;
        return;
    }
    
    if (strcmp(p->params[i].value, "true") == 0) {
        (*value) = true;
    } else if (strcmp(p->params[i].value, "false") == 0) {
        (*value) = false;
    } else {
        (*value) = default_value;
    }
}

void parser_get_bool_mpi(const char* filename,
                         char *key, bool *value, 
                         bool default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_bool_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_C_BOOL, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser error: bcast failed\n");
            exit(-1);
        }
    }
}

void parser_get_char_seq(const char* filename,
                         char *key, char *value,
                         char default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        value[0] = default_value;
    else
        value[0] = p->params[i].value[0];
}

void parser_get_char_mpi(const char* filename,
                         char *key, char *value,
                         char default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_char_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_CHAR, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char failed\n");
            exit(-1);
        }
    }
}

void parser_get_string_seq(const char* filename,
                           char *key, char *value,
                           char *default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        sprintf(value, "%s\0", default_value);
    else
        sprintf(value, "%s\0", p->params[i].value);
}

void parser_get_string_mpi(const char* filename,
                           char *key, char *value,
                           char *default_value, char *key2) {
    int len;
    if (mpi_rank == 0) {
        parser_get_string_seq(filename, key, value, default_value, key2);
        len = strlen(value);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&len, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr,
                    "fatal parser MPI error: bcast string length failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, len, MPI_CHAR, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast string failed\n");
            exit(-1);
        }
        value[len]='\0';
    }
}

void parser_get_int32_seq(const char* filename,
                          char *key, int *value,
                          int default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        (*value) = default_value;
    } else {
        (*value) = atoi(p->params[i].value);
    }
}

void parser_get_int32_mpi(const char* filename,
                          char *key, int *value,
                          int default_value, char *key2) {
    if (mpi_rank == 0) {
        parser_get_int32_seq(filename, key, value, default_value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast int32 failed\n");
            exit(-1);
        }
    }
}

void parser_get_int64_seq(const char* filename,
                          char *key, int64_t *value,
                          int64_t default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        (*value) = default_value;
    else
        (*value) = atol(p->params[i].value);
}

void parser_get_int64_mpi(const char* filename,
                          char *key, int64_t *value,
                          int64_t default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_int64_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_LONG, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast int64 failed\n");
            exit(-1);
        }
    }
}

void parser_get_float_seq(const char* filename,
                          char *key, float *value,
                          float default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        (*value) = default_value;
    else
        (*value) = atof(p->params[i].value);
}

void parser_get_float_mpi(const char* filename,
                          char *key, float *value,
                          float default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_float_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_FLOAT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast float failed\n");
            exit(-1);
        }
    }
}

void parser_get_double_seq(const char* filename,
                           char *key, double *value,
                           double default_value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        (*value) = default_value;
    else
        (*value) = atof(p->params[i].value);
}

void parser_get_double_mpi(const char* filename,
                           char *key, double *value,
                           double default_value, char *key2) {
    if (mpi_rank == 0)
        parser_get_double_seq(filename, key, value, default_value, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)value, 1, MPI_DOUBLE, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast double failed\n");
            exit(-1);
        }
    }
}

int parser_list_count(const char *filename, char *key, char *key2) {
    int i, j = 0, count = 1; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE))
        return 0;
    for (j=0; j<strlen(p->params[i].value) ; ++j)
        if (p->params[i].value[j] == ',') count++;
    return count;
}

void parser_list_to_bool(char *value, bool *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        if (strcmp(pch, "true") == 0) {
            list[i] = true;
        } else if (strcmp(pch, "false") == 0) {
            list[i] = false;
        } else {
            fprintf(stderr, "fatal parser error: bool is true or false\n");
            exit(-1);
        }
        i++;
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_char(char *value, char *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = pch[0];
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_string(char *value, char **list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        sprintf(list[i++], "%s\0", pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_int32(char *value, int *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atoi(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_int64(char *value, int64_t *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atol(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_float(char *value, float *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atof(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_list_to_double(char *value, double *list) {
    int i = 0; char *pch = strtok(value, ",");
    while (pch != NULL) {
        list[i++] = atof(pch);
        pch = strtok(NULL, ",");
    }
}

void parser_getlist_bool_seq(const char* filename,
                             char *key, bool *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_bool(p->params[i].value, value);
}

void parser_getlist_bool_mpi(const char* filename,
                             char *key, bool *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_bool_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_C_BOOL, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast bool list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_char_seq(const char* filename,
                             char *key, char *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_char(p->params[i].value, value);
}

void parser_getlist_char_mpi(const char* filename,
                             char *key, char *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_char_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_CHAR, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_string_seq(const char* filename,
                               char *key, char **value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_string(p->params[i].value, value);
}

void parser_getlist_string_mpi(const char* filename,
                               char *key, char **value, char *key2) {
    int count, len, i;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_string_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        for (i=0; i<count; ++i) {
            if (mpi_rank == 0) len = strlen(value[i]);
            if (MPI_Bcast((void*)&len, 1, MPI_INT, 0, mpi_communicator)) {
                fprintf(stderr, "fatal parser MPI error: bcast len failed\n");
                exit(-1);
            }
            if (MPI_Bcast((void*)value[i],
                          len, MPI_CHAR, 0, mpi_communicator)) {
                fprintf(stderr,
                        "fatal parser MPI error: bcast char list failed\n");
                exit(-1);
            }
        }
    }
}

void parser_getlist_int32_seq(const char* filename,
                              char *key, int *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_int32(p->params[i].value, value);
}

void parser_getlist_int32_mpi(const char* filename,
                              char *key, int *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_int32_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_int64_seq(const char* filename,
                              char *key, int64_t *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_int64(p->params[i].value, value);
}

void parser_getlist_int64_mpi(const char* filename,
                              char *key, int64_t *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_int64_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_LONG, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_float_seq(const char* filename,
                              char *key, float *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_float(p->params[i].value, value);
}

void parser_getlist_float_mpi(const char* filename,
                              char *key, float *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_float_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_FLOAT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

void parser_getlist_double_seq(const char* filename,
                               char *key, double *value, char *key2) {
    int i; parser *p = NULL;
    if (((i = parser_find_param(filename, key, &p, NULL)) == FAILURE) && 
        ((i = parser_find_param(filename, key2, &p, NULL)) == FAILURE)) {
        value = NULL;
        return;
    }
    return parser_list_to_double(p->params[i].value, value);
}

void parser_getlist_double_mpi(const char* filename,
                               char *key, double *value, char *key2) {
    int count;
    if (mpi_rank == 0) {
        count = parser_list_count(filename, key, key2);
        parser_getlist_double_seq(filename, key, value, key2);
    }
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&count, 1, MPI_INT, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast count failed\n");
            exit(-1);
        }
        if (MPI_Bcast((void*)value, count, MPI_DOUBLE, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast char list failed\n");
            exit(-1);
        }
    }
}

bool parser_exist_seq(const char *filename, char *key, char *key2) {
    parser *p = NULL;
    return parser_find_param(filename, key, &p, NULL) != FAILURE;
}

bool parser_exist_mpi(const char *filename, char *key, char *key2) {
    bool res;
    if (mpi_rank == 0)
        res = parser_exist_seq(filename, key, key2);
    if (mpi_bcast_on) {
        if (MPI_Bcast((void*)&res, 1, MPI_C_BOOL, 0, mpi_communicator)) {
            fprintf(stderr, "fatal parser MPI error: bcast bool failed\n");
            exit(-1);
        }
    }
    return res;
}
