Building ICU4C
==============

Download the ICU4C sources (http://site.icu-project.org/download/, I used version 58-1),
unpack them into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_{{PREFIX}}.bash {{SRCDIR}}

Where {{PREFIX}} represents your target platform (either "unix-x64", or "w64-mingw32"),
and {{SRCDIR}} is the directory in which the ICU4C sources were just unpacked.

Afterwards, verify that the ICU4C static libraries have been installed in
../prefix_{{PREFIX}}/lib, and the ICU4C header files in ../prefix_{{PREFIX}}/include.
