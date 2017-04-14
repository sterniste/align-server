Building json
=============

Clone the Git json sources (I used: git clone https://github.com/nlohmann/json.git)
into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_{{PREFIX}}.bash {{SRCDIR}}

Where {{PREFIX}} represents your target platform (either "unix-x64", or "w64-mingw32"),
and {{SRCDIR}} is the directory in which the json Git repo was just cloned.

Afterwards, verify that the json header files have been installed in
../prefix_{{PREFIX}}/include.
