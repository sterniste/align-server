#!/bin/bash
OPENSSL_SRC_DIR=$1
if [ ! -d "$OPENSSL_SRC_DIR" ]; then
    echo "can't find source dir: $OPENSSL_SRC_DIR"
    exit 1
fi

export TARGET_DIR=$PWD/../prefix_linux-x64
export BUILD_DIR=$PWD/build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi
cp -r $OPENSSL_SRC_DIR $BUILD_DIR

cd $BUILD_DIR
./config shared --prefix=$TARGET_DIR && make && make install
