#!/bin/bash
OPENSSL_SRC_DIR=$1
if [ ! -d "$OPENSSL_SRC_DIR" ]; then
    echo "can't find source dir: $OPENSSL_SRC_DIR"
    exit 1
fi

export TARGET_DIR=$PWD/../prefix_w64-mingw32
export BUILD_DIR=$PWD/build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi
cp -r $OPENSSL_SRC_DIR $BUILD_DIR

cd $BUILD_DIR
sed -i '/:\.dll\.a/s//-Wl,--export-all -shared:.dll.a/' ./Configure 
./Configure mingw64 no-shared --cross-compile-prefix=x86_64-w64-mingw32- --prefix=$TARGET_DIR && make && make install
