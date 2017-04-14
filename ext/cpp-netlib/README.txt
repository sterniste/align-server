Building cpp-netlib
===================

Clone the Git cpp-netlib sources (I used: git clone https://github.com/cpp-netlib/cpp-netlib.git -b 0.13-release),
into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_{{PREFIX}}.bash {{SRCDIR}}

Where {{PREFIX}} represents your target platform (either "unix-x64", or "w64-mingw32"),
and {{SRCDIR}} is the directory in which the cpp-netlib Git repo was just cloned.

Afterwards, verify that the cpp-netlib static libraries have been installed in
../prefix_{{PREFIX}}/lib, and the cpp-netlib header files in ../prefix_{{PREFIX}}/include/boot/network.
