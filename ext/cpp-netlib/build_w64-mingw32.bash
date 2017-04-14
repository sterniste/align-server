#!/bin/bash
CPP_NETLIB_SRC_DIR=$1
if [ ! -d "$CPP_NETLIB_SRC_DIR" ]; then
    echo "can't find source dir: $CPP_NETLIB_SRC_DIR"
    exit 1
fi
ABS_CPP_NETLIB_SRC_DIR=`readlink -e $CPP_NETLIB_SRC_DIR`

TARGET_DIR=$PWD/../prefix_w64-mingw32
BUILD_DIR=build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi
mkdir $BUILD_DIR

cd $BUILD_DIR
cmake3 -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=0 -DCPP-NETLIB_BUILD_TESTS=OFF -DCPP-NETLIB_BUILD_EXAMPLES=OFF -DUri_BUILD_TESTS=OFF -DUri_BUILD_DOCS=OFF \
       -DCPP-NETLIB_STATIC_OPENSSL=ON -DOPENSSL_INCLUDE_DIR=$TARGET_DIR/include -DOPENSSL_SSL_LIBRARY=$TARGET_DIR/lib/libssl.a -DOPENSSL_CRYPTO_LIBRARY=$TARGET_DIR/lib/libcrypto.a \
       -DCPP-NETLIB_STATIC_BOOST=ON -DBOOST_INCLUDEDIR=$TARGET_DIR/include -DBoost_USE_MULTITHREADED=ON \
       -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_INSTALL_PREFIX=$TARGET_DIR \
       $ABS_CPP_NETLIB_SRC_DIR \
&& make install
