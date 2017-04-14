Building json
=============

Clone the Git json sources (https://github.com/nlohmann/json.git),
into some directory somewhere (just underneath this directory, for instance),
then run the command:

$ bash build_linux-x64.bash SRCDIR

Where SRCDIR is the directory in which the json Git repo was just cloned.

Afterwards, verify that the json header files have been installed in ../prefix_linux-x64/include.