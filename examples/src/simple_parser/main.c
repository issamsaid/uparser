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
    int i;
    int64_t I;
    bool b = false;
    char s[64]; 
    fprintf(stdout, "... start of the simple parser info example\n");

    ///< Initialize uparser.
    uparser_init(argc, argv);

    ///< Populate the parser.
    uparser_put('i', "int32",  "2", "this is a 32 bits integer");
    uparser_put('I', "int64", "-9", "this is a 64 bits integer");
    uparser_put('b', "boolean", "false", "this is a boolean");
    uparser_put('s', "string",  "foo", "this is a string");

    ///< Parse the command line arguments.
    uparser_parse();

    ///< Get values.
    uparser_get_int32("i",      &i);
    uparser_get_int32("int32",  &i);
    uparser_get_int64("I",      &I);
    uparser_get_int64("int64",  &I);
    uparser_get_bool("boolean", &b);
    uparser_get_string("string", s);

    fprintf(stdout, "... param int32 value is   '%d'\n", i);
    fprintf(stdout, "... param int64 value is   '%ld'\n", I);
    fprintf(stdout, "... param boolean value is '%s'\n", b ? "true" : "false");
    fprintf(stdout, "... param string value is  '%s'\n", s);

    ///< Release uparser.
    uparser_release();
    fprintf(stdout, "... end   of the simple parser info example\n");
    return EXIT_SUCCESS;
}
