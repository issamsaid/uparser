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
/// @file test/src/core_test.cc
/// @author Issam SAID
/// @brief Unit testing file for the uparser core routines.
/// 
#include <gtest/gtest.h>
#include <uparser/uparser.h>

namespace {

    class CoreTest : public ::testing::Test {
    protected:
        int    argc;
        char **argv; 
        virtual void SetUp() {
            int i;
            argc = 5;
            argv = (char**)malloc(sizeof(char*)*argc);
            for (i=0; i<argc; i++) argv[i] = (char*)malloc(sizeof(char)*16);
            sprintf(argv[0], "%s", "uparser_test");
            sprintf(argv[1], "%s", "b=false");
            sprintf(argv[2], "%s", "i=1");
            sprintf(argv[3], "%s", "c=V");
            sprintf(argv[4], "%s", "string=foo");
        }
        virtual void TearDown() { 
            int i;
            for (i=0; i<argc; i++) free(argv[i]);
            free(argv);
        }
    };

    TEST_F(CoreTest, init_release) {
        uparser_init(argc, argv);
        uparser_usage();
        uparser_release();
    }
    
}  // namespace