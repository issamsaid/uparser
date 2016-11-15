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
/// @file test/src/Put_test.cc
/// @author Issam SAID
/// @brief Unit testing file for the uparser Put routine.
/// 
#include <gtest/gtest.h>
#include <uparser/uparser.h>

namespace {

    class PutTest : public ::testing::Test {
    protected:
        int    argc;
        char **argv; 
        virtual void SetUp() {
            int i;
            argc = 13;
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

            uparser_init(argc, argv);
            uparser_put('b', "boolean", "false", "boolean argument");
            uparser_put( 0 , "fake_boolean", "false", "fake boolean argument");
            uparser_put('i', "int32",     "-1", "integer argument");
            uparser_put( 0 , "fake_int32", "-1", "integer argument");
            uparser_put('c', "char",       "B", "char argument");
            uparser_put( 0 , "fake_char",  "B", "char argument");
            uparser_put('s', "string",   "bar", "string argument");
            uparser_put( 0 , "fake_string",   "bar", "fake string argument");
            uparser_put( 0 , "vchar", "X,X,X", "vchar argument");
            uparser_put( 0 , "fake_vchar",    "X,X,X", "vchar argument");
            uparser_put( 0 , "vint32", "-1,-1,-1", "vint32 argument");
            uparser_put( 0 , "fake_vint32", "-1,-1,-1", "fake vint32 argument");
            uparser_put('I', "int64", "-1", "int64 argument");
            uparser_put( 0 , "fake_int64", "-1", "fake int64 argument");
            uparser_put( 0 , "vint64",   "-1,-1,-1", "vint64 argument");
            uparser_put( 0 , "fake_vint64", "-1,-1,-1", "fake vint64 argument");
            uparser_put('f', "float",    "-1", "float argument");
            uparser_put( 0 , "fake_float",    "-1", "fake float argument");
            uparser_put('d', "double",   "-1", "double argument");
            uparser_put( 0 , "fake_double", "-1", "fake double argument");
            uparser_put( 0 , "vfloat",   "-1,-1,-1", "vfloat argument");
            uparser_put( 0 , "fake_vfloat", "-1,-1,-1", "fake vfloat argument");
            uparser_put( 0 , "vdouble",  "-1,-1,-1", "vdouble argument");
            uparser_put( 0 , "fake_vdouble", "-1,-1,-1", "fake vdouble arg");
            uparser_parse();
        }
        virtual void TearDown() { 
            int i;
            uparser_release();
            for (i=0; i<argc; i++) free(argv[i]);
            free(argv);
        }
    };

    TEST_F(PutTest, add_argument) {
        int i;
        ASSERT_DEATH(uparser_put('b', "other_boolean", "false", 
                                 "other boolean argument"), ".*");
        uparser_put('z', "zint32", "123", "other int argument");
        uparser_get_int32("z", &i);
        ASSERT_EQ(i, 123);
        uparser_parse();
        uparser_get_int32("z", &i);
        ASSERT_EQ(i, 123);
    }

}  // namespace