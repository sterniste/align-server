Building Boost
==============

Download the Boost sources (http://www.boost.org/users/download/, I used version 1.63.b1),
unpack them into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_linux-x64.bash SRCDIR

Where SRCDIR is the directory in which the Boost sources were just unpacked.

Afterwards, verify that the Boost shared libraries have been installed in ../prefix_linux-x64/lib
and the Boost header files in ../prefix_linux-x64/include.

