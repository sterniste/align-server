Building OpenSSL
================

Download the OpenSSL sources (http://www.openssl.org/source/, I used version 1.1.0c),
unpack them into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_{{PREFIX}}.bash {{SRCDIR}}

Where {{PREFIX}} represents your target platform (either "unix-x64", or "w64-mingw32"),
and {{SRCDIR}} is the directory in which the OpenSSL sources were just unpacked.

Afterwards, verify that the OpenSSL static libraries have been installed in
../prefix_{{PREFIX}}/lib, and the OpenSSL header files in ../prefix_{{PREFIX}}/include.
