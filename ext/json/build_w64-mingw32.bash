#!/bin/bash
JSON_SRC_DIR=$1
if [ ! -d "$JSON_SRC_DIR" ]; then
    echo "can't find source dir: $JSON_SRC_DIR"
    exit 1
fi

export TARGET_DIR=$PWD/../prefix_w64-mingw32
export BUILD_DIR=build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi
mkdir $BUILD_DIR

cd $BUILD_DIR
cmake3 -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_INSTALL_PREFIX=$TARGET_DIR ../$JSON_SRC_DIR && make && make install
