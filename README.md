# uparser
[![Build Status](https://travis-ci.org/issamsaid/uparser.svg?branch=master)](https://travis-ci.org/issamsaid/uparser)

<b>uparser</b> is a C/C++ and Fortran command line argument parser.

# Content
<!-- MarkdownTOC depth=2 -->

- [Getting started](#getting-started)
    - [Branches and cloning](#branches-and-cloning)
    - [Setting up](#setting-up)
    - [Dependencies](#dependencies)
    - [Building the C/C++ interface](#building-the-cc-interface)
    - [Building the Fortran interface](#building-the-fortran-interface)
    - [Building the unit tests](#building-the-unit-tests)
    - [Generating the documentation](#generating-the-documentation)
    - [Installing](#installing)
    - [Continuous integration](#continuous-integration)
- [Using uparser](#using-uparser)
- [How to contribute](#how-to-contribute)
- [License](#license)
- [Contact](#contact)

<!-- /MarkdownTOC -->

<a name="getting-started"></a>
# Getting started
The following section is a step by step guide that will take you from fetching
the source code from the repository branches to running your <b>uparser</b> 
first examples on your machine.

<a name="branches-and-cloning"></a>
## Branches and cloning
The project contains two git main branches: **master** and **develop**. 
The **master** branch only contains the major releases, and 
is intended to use the library as is.
We recommend to clone from this branch if you would like to use 
the latest stable version. 
The releases are tagged on the master branch and each version has a major
number and a minor number which are used as the tagging string (.e.g. the 
first release is tagged 1.0 on the master branch).
Cloning the master branch and checking out the latest release can
be done as follows:
```
git clone -b master https://github.com/issamsaid/uparser.git
```
If you wish to clone a specific release (here we use the 1.0 release as
an example) you may add:
```
pushd uparser
git checkout tags/1.0
popd
``` 
The following table summarizes the different details about all the 
releases of the <b>uparser</b> library:</br>

Release number (tag)  | Date         | Description                                    
--------------------- | ------------ | -----------------------------------------------
1.0                   | 11/01/2016   | The initial release of the <b>uparser</b> library

On the other hand, the **develop** branch contains the latest builds and is
intended to be used by the developers who are willing to contribute or improve 
the library. 
To get started, you can clone this branch as follows:
```
git clone -b develop https://github.com/issamsaid/uparser.git
```

<a name="setting-up"></a>
## Setting up
The <b>uparser</b> project has multiple components, each in a subdirectory of the
root directory (uparser):
- The [src](https://github.com/issamsaid/uparser/tree/master/src) subdirectory is the C/C++ interface.
- The [fortran_interface](https://github.com/issamsaid/uparser/tree/master/fortran_interface) subdirectory is the Fortran interface.
- The [test](https://github.com/issamsaid/uparser/tree/master/test) subdirectory contains the unit tests of the library. 
- The [doc](https://github.com/issamsaid/uparser/tree/master/doc) subdirectory is 
 where the documentation of the library is to be generated.

The project compilation framework is to be setup using the 
[cmake](https://cmake.org/) utility. Depending on your operating system
you may choose a specific [cmake generator](https://cmake.org/cmake/help/v3.0/manual/cmake-generators.7.html) to build the project.
As an example, if you wish to build <b>uparser</b> on Unix based operating
systems you can use the following (the rest of the examples in this material 
are also intended to be used on Unix based systems):
```
pushd uparser
mkdir build
pushd build
cmake -G"Unix Makefiles" ../
popd
```
The current version of <b>uparser</b> had been tested on various Linux 
distributions with the GNU, Cray and Intel compilers. 
Nevertheless, if you face issues with other compilers you are kindly invited to report them.
Note that if you are using Cray compilers you have to specify where the 
Fortran compiler is wrapped. For example if you are using `ftn` you have to add:
```
pushd uparser
mkdir build
pushd build
cmake -DCMAKE_Fortran_COMPILER=ftn -G"Unix Makefiles" ../
popd
```

<a name="dependencies"></a>
## Dependencies
<b>uparser</b> uses internally the 
[urb_tree](https://github.com/issamsaid/urb_tree/tree/master) libraries (
a red-black trees generic libraries) in order to track and efficiently 
manipulate some internal data structures. It also relies on the 
[googletest](https://github.com/google/googletest/) framework for unit 
testing.
Those libraries are automatically downloaded, compiled and installed when
building <b>uparser</b>. Alternatively you can set the path to those libraries
if they are already installed on your system as follows:
```
export URB_TREE_DIR="YOUR_PATH_TO_URB_TREE"
export GTEST_DIR="YOUR_PATH_TO_GTEST"
```

<a name="building-the-cc-interface"></a>
## Building the C/C++ interface
To build the <b>uparser</b> C static library you can run the default Makefile 
target as follows:
```
pushd build
make uparser 
popd 
```
This Makefile target will build the static library `libuparser.a` from the C/C++ 
source files in the [src](https://github.com/issamsaid/uparser/tree/master/src)
subdirectory. 
Since this is the default target you can also build the static C library
as follows:
```
pushd build
make  
popd 
```

<a name="building-the-fortran-interface"></a>
## Building the Fortran interface
If you would like to build the Fortran interface additionally, 
you can do so as follows:
```
pushd build
make uparser_fortran
popd
```
This target will build another static library `libuparser_fortran.a` from the
Fortran source files present in the 
[fortran_interface](https://github.com/issamsaid/uparser/tree/master/fortran_interface) subdirectory. Note that the Fortran interface is only
an additional layer based on the Fortran 2003 standard (ISO/IEC 1539-1:2004(E)),
which generates procedure and derived-type declarations and global variables that are interoperable with C. Therefor, if the C/C++ interface is not built this target will build it as well.

<a name="building-the-unit-tests"></a>
## Building the unit tests
The library comes with a set of unit tests and performance 
tests to validate the new features. You can check the unit testing 
directory [here](https://github.com/issamsaid/uparser/tree/master/test).
The testing framework is used to thoroughly test <b>uparser</b> in C/C++ 
([test/src](https://github.com/issamsaid/uparser/tree/master/test/src)) and 
Fortran ([test/fortran](https://github.com/issamsaid/uparser/tree/master/test/fortran_interface)). The C/C++ interface unit tests are based on top of the 
[googletest](https://github.com/google/googletest/) Framework). To build
all the unit tests, C/C++ and Fortran included, you can invoke the 
following target:
```
pushd build
make build_tests
popd
```
Alternatively `make uparser_test` will only build the test suit for the C/C++ interface, and `make uparser_test_fortran` will build the unit tests for the
Fortran interface.
Tests should be written for any new code, and changes should be verified to not 
break existing tests before they are submitted for review. 

<a name="generating-the-documentation"></a>
## Generating the documentation
The documentation of the library can be generated, in the [doc](https://github.com/issamsaid/uparser/tree/master/doc) subdirectory,
with the help of [doxygen](http://www.stack.nl/~dimitri/doxygen/) by simply running:
```
pushd build
make doc
popd
```

<a name="installing"></a>
## Installing 
In order to install the <b>uparser</b> project you can invoke the classic 
Makefile install target:
```
pushd build
make install
popd
```
This target mainly installs the <b>uparser</b> C/C++ static library in the `lib` subdirectory on the project root directory. If the Fortran static library, the unit tests binaries and the examples binaries are built, they will be installed 
respectively in the `lib`, `test/bin` and `examples/bin` subdirectories.

<a name="continuous-integration"></a>
## Continuous integration
We use [Travis CI](https://travis-ci.org/issamsaid/uparser) for the continuous 
integration of the <b>uparser</b> library. The image on the top of the page is a
link to the latest build of each branch.
A build is launched after each pull request with respect to the Travis CI 
configuration file (.travis.yml). (We still trying to find out a way to emulate
GPUs on travis since  it does not feature GPUs for the time being).


<a name="using-uparser"></a>
# Using uparser
In order to use the <b>uparser</b> C/C++ link your code against libuparser.a 
(by adding `-luparser` to your linker options), 
however if your code is based on Fortran the 
latter should linked against both the C/C++ library and the Fortran interface (
with the help of the options `-luparser_fortran -luparser`).<br/>

To perform the unit tests you can run:
```
pushd test
./bin/uparser_test         // for C/C++
./bin/uparser_test_fortran // for Fortran
popd
```
It is now up to you to read the documentation in order 
to use <b>uparser</b> to write your own codes for various purposes.

<a name="how-to-contribute"></a>
# How to contribute
We believe that <b>uparser</b> can be used by scientific programmers very 
efficiently. We tend to extend the functionalities of the library. For this to 
do we need your feedbacks and proposals of features and use cases.
If you are willing to contribute please visit the contributors guide
[CONTRIBUTING](https://github.com/issamsaid/uparser/tree/master/CONTRIBUTING.md),
or feel free to contact us.

<a name="license"></a>
# License
<b>uparser</b> is a free software licensed under 
[BSD](https://github.com/issamsaid/uparser/tree/master/LICENSE.md).


<a name="contact"></a>
# Contact
For bug report, feature requests or if you willing to contribute please 
feel free to contact Issam SAID by dropping a line to said.issam@gmail.com.
