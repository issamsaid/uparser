    ///
/// @copyright Copyright (c)2016-, Issam SAID <said.issam@gmail.com>
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
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
/// HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file test/src/arg_test.cc
/// @author Issam SAID
/// @brief Unit testing file for the uparser_arg routine.
/// 
#include <gtest/gtest.h>
#include <uparser/uparser.h>

namespace {

    class ArgTest : public ::testing::Test {
    protected:
        int    argc;
        char **argv; 
        virtual void SetUp() {
            int i;
            argc = 16;
            argv = (char**)malloc(sizeof(char*)*argc);
            for (i=0; i<argc; i++) argv[i] = (char*)malloc(sizeof(char)*64);
            sprintf(argv[0],  "%s", "uparser_test");
            sprintf(argv[1],  "%s", "-b");
            sprintf(argv[2],  "%s", "--char=V");
            sprintf(argv[3],  "%s", "--string=foo");
            sprintf(argv[5],  "%s", "--vchar=A,B,C");
            sprintf(argv[7],  "%s", "--int32=1");
            sprintf(argv[8],  "%s", "--vint32=1,2,3");
            sprintf(argv[9],  "%s", "--int64=9");
            sprintf(argv[10], "%s", "--vint64=9,10,11");
            sprintf(argv[11], "%s", "-f=1.34");
            sprintf(argv[12], "%s", "--vfloat=1.34,2.52,3.14");
            sprintf(argv[4],  "%s", "--double=1.34");
            sprintf(argv[6],  "%s", "--vdouble=1.34,2.52,3.14");
            sprintf(argv[13], "%s", "501");
            sprintf(argv[14], "%s", "502");
            sprintf(argv[15], "%s", "503");

            uparser_init(argc, argv);
            uparser_opt('b', "boolean", "false", "boolean option");
            uparser_opt( 0 , "fake_boolean", "false", "fake boolean option");
            uparser_opt('i', "int32",     "-1", "integer option");
            uparser_opt( 0 , "fake_int32", "-1", "integer option");
            uparser_opt('c', "char",       "B", "char option");
            uparser_opt( 0 , "fake_char",  "B", "char option");
            uparser_opt('s', "string",   "bar", "string option");
            uparser_opt( 0 , "fake_string",   "bar", "fake string option");
            uparser_opt( 0 , "vchar", "X,X,X", "vchar option");
            uparser_opt( 0 , "fake_vchar",    "X,X,X", "vchar option");
            uparser_opt( 0 , "vint32", "-1,-1,-1", "vint32 option");
            uparser_opt( 0 , "fake_vint32", "-1,-1,-1", "fake vint32 option");
            uparser_opt('I', "int64", "-1", "int64 option");
            uparser_opt( 0 , "fake_int64", "-1", "fake int64 option");
            uparser_opt( 0 , "vint64",   "-1,-1,-1", "vint64 option");
            uparser_opt( 0 , "fake_vint64", "-1,-1,-1", "fake vint64 option");
            uparser_opt('f', "float",    "-1", "float option");
            uparser_opt( 0 , "fake_float",    "-1", "fake float option");
            uparser_opt('d', "double",   "-1", "double option");
            uparser_opt( 0 , "fake_double", "-1", "fake double option");
            uparser_opt( 0 , "vfloat",   "-1,-1,-1", "vfloat option");
            uparser_opt( 0 , "fake_vfloat", "-1,-1,-1", "fake vfloat option");
            uparser_opt( 0 , "vdouble",  "-1,-1,-1", "vdouble option");
            uparser_opt( 0 , "fake_vdouble", "-1,-1,-1", "fake vdouble arg");
        }
        virtual void TearDown() { 
            int i;
            uparser_release();
            for (i=0; i<argc; i++) free(argv[i]);
            free(argv);
        }
    };

    TEST_F(ArgTest, add_arguments) {
        int i;
        // ASSERT_DEATH(uparser_opt('b', "other_boolean", "false", 
        //                          "other boolean option"), ".*");
        uparser_arg("first_argument",  "first int argument");
        uparser_arg("second_argument", "second int argument");
        uparser_arg("third_argument",  "third int argument");
        uparser_parse();
        uparser_usage();
        // uparser_get_int32("z", &i);
        // ASSERT_EQ(i, 123);
    }

}  // namespace