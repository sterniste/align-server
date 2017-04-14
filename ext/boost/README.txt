Building Boost
==============

Download the Boost sources (http://www.boost.org/users/download/, I used version 1.63.b1),
unpack them into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_{{PREFIX}}.bash {{SRCDIR}}

Where {{PREFIX}} represents your target platform (either "unix-x64", or "w64-mingw32"),
and {{SRCDIR}} is the directory in which the Boost sources were just unpacked.

Afterwards, verify that the Boost static libraries have been installed in
../prefix_{{PREFIX}}/lib, and the Boost header files in ../prefix_{{PREFIX}}/include.
