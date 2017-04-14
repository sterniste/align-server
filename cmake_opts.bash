#!/bin/bash
if [ $# -ne 1 -o ! -d $1 ]; then
  echo usage: $0 top_dir
  exit 1
fi
top_dir=`realpath -e $1`
shift

if [ -z "${PREFIX+set}" ]; then
  if [[ "$(uname -s)" =~ ^CYGWIN* ]]; then
    PREFIX=w64-mingw32
  else
    PREFIX=linux-x64
  fi
fi
if [ "$PREFIX" = w64-mingw32 -a -z "${CMAKE_TOOLCHAIN_FILE+set}" ]; then
  CMAKE_TOOLCHAIN_FILE=$top_dir/cmake/toolchain_w64-mingw32.cmake
fi

declare -a opts
if [ -n "${CMAKE_TOOLCHAIN_FILE+set}" ]; then
  opts+=("-DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE")
fi
if [ -n "${CMAKE_CXX_COMPILER+set}" ]; then
  opts+=("-DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER")
fi
if [ -n "${CMAKE_C_COMPILER+set}" ]; then
  opts+=("-DCMAKE_C_COMPILER=$CMAKE_C_COMPILER")
fi
opts+=("-DICU4C_LIB_DIR=$top_dir/ext/prefix_$PREFIX/lib")
opts+=("-DBOOST_INCLUDE_DIR=$top_dir/ext/prefix_$PREFIX/include")
opts+=("-DBOOST_LIB_DIR=$top_dir/ext/prefix_$PREFIX/lib")
opts+=("-DOPENSSL_INCLUDE_DIR=$top_dir/ext/prefix_linux-64x/include")
opts+=("-DOPENSSL_LIB_DIR=$top_dir/ext/prefix_$PREFIX/lib")
opts+=("-DJSON_INCLUDE_DIR=$top_dir/ext/prefix_$PREFIX/include")
opts+=("-DJSON_LIB_DIR=$top_dir/ext/prefix_$PREFIX/lib")
opts+=("-DCPP_NETLIB_INCLUDE_DIR=$top_dir/ext/prefix_$PREFIX/include")
opts+=("-DCPP_NETLIB_LIB_DIR=$top_dir/ext/prefix_$PREFIX/lib")
opts+=("-G 'Unix Makefiles'")
opts+=("$top_dir")

echo ${opts[*]}
