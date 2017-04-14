Building OpenSSL
================

Download the OpenSSL sources (http://www.openssl.org/source/, I used version 1.1.0c),
unpack them into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_linux-x64.bash SRCDIR

Where SRCDIR is the directory in which the OpenSSL sources were just unpacked.

Afterwards, verify that the OpenSSL shared libraries have been installed in ../prefix_linux-x64/lib
and the OpenSSL header files in ../prefix_linux-x64/include.

