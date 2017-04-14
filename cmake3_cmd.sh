#!/bin/sh
echo cmake3 \\
if [ -n "${CMAKE_CXX_COMPILER+set}" ]; then
  echo -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER \\
fi
if [ -n "${CMAKE_C_COMPILER+set}" ]; then
  echo -DCMAKE_C_COMPILER=$CMAKE_C_COMPILER \\
fi
echo "\
-DBOOST_INCLUDE_DIR=$PWD/ext/prefix_linux-x64/include \
-DBOOST_LIB_DIR=$PWD/ext/prefix_linux-x64/lib \
-DOPENSSL_INCLUDE_DIR=$PWD/ext/prefix_linux-x64/include \
-DOPENSSL_LIB_DIR=$PWD/ext/prefix_linux-x64/lib \
-DJSON_INCLUDE_DIR=$PWD/ext/prefix_linux-x64/include" \\
echo $*
