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
/// @file simple_parser/main.c
/// @author Issam SAID
/// @brief An example of simple parser based on the uparser C/C++ interface.
///
#include <stdio.h>
#include <stdlib.h>
#include <uparser/uparser.h>

///
/// @brief The main program of the simple parser example.
///
/// This is the main routine that shows how to use the uparser C/C++ interface 
/// to implement a simple program.
/// @return Error code if any.
///
int main(int argc, char **argv) {
    int i, vect_i[3];
    int64_t I, vect_I[3];
    bool b = false;
    char s[64];
    float f, vect_f[3];
    double d, vect_d[3];

    fprintf(stdout, "... start of the simple parser info example\n");

    ///< Initialize uparser.
    uparser_init(argc, argv);

    ///< Populate the parser.
    uparser_opt('i', "int32",   "2",     "this is a 32 bits integer");
    uparser_opt('I', "int64",   "-9",    "this is a 64 bits integer");
    uparser_opt('b', "boolean", "false", "this is a boolean");
    uparser_opt('s', "string",  "foo",   "this is a string");
    uparser_opt('f', "float",   "1.33",  "this is a float");
    uparser_opt('d', "double",  "9.77",  "this is a double");

    uparser_opt(0, "vint32",           "1,2,3", "this is a 32bits integer tab");
    uparser_opt(0, "vint64",           "4,5,6", "this is a 64bits integer tab");
    uparser_opt(0, "vfloat",  "1.22,2,33,4,55", "this is a float tab");
    uparser_opt(0, "vdouble", "9.77,8,66,7,66", "this is a double tab");

    ///< Parse the command line arguments.
    uparser_parse();

    ///< Show the uparser help.
    uparser_usage();

    ///< Get values.
    uparser_get_int32("i",       &i);
    uparser_get_int32("int32",   &i);
    uparser_get_int64("I",       &I);
    uparser_get_int64("int64",   &I);
    uparser_get_bool("boolean",  &b);
    uparser_get_string("string",  s);
    uparser_get_float("float",   &f);
    uparser_get_double("double", &d);

    uparser_get_int32("vint32", vect_i);
    uparser_get_int64("vint64", vect_I);
    uparser_get_float("vfloat", vect_f);
    uparser_get_double("vdouble", vect_d);

    fprintf(stdout, "... param int32   value is '%d'\n", i);
    fprintf(stdout, "... param int64   value is '%ld'\n", I);
    fprintf(stdout, "... param boolean value is '%s'\n", b ? "true" : "false");
    fprintf(stdout, "... param string  value is '%s'\n", s);
    fprintf(stdout, "... param float   value is '%f'\n", f);
    fprintf(stdout, "... param double  value is '%f'\n", d);  

    fprintf(stdout, "... param vint32  value is '%d,%d,%d'\n", 
            vect_i[0], vect_i[1], vect_i[2]);  
    fprintf(stdout, "... param vint64  value is '%ld,%ld,%ld'\n", 
            vect_I[0], vect_I[1], vect_I[2]);  
    fprintf(stdout, "... param vfloat  value is '%f,%f,%f'\n", 
            vect_f[0], vect_f[1], vect_f[2]);  
    fprintf(stdout, "... param vdouble value is '%f,%f,%f'\n",
            vect_d[0], vect_d[1], vect_d[2]);  
 
    ///< Release uparser.
    uparser_release();
    fprintf(stdout, "... end   of the simple parser info example\n");
    return EXIT_SUCCESS;
}
