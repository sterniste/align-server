#!/bin/bash
BOOST_SRC_DIR=$1
if [ ! -d "$BOOST_SRC_DIR" ]; then
    echo "can't find source dir: $BOOST_SRC_DIR"
    exit 1
fi

export TARGET_DIR=$PWD/../prefix_w64-mingw32
export BUILD_DIR=$PWD/build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi
mkdir $BUILD_DIR

export BOOST_BUILD_USER_CONFIG=$PWD/user-config.jam
cd $BOOST_SRC_DIR
./bootstrap.sh --without-icu mingw
echo 'using gcc : 5.4 : x86_64-w64-mingw32-g++.exe ;' > $BOOST_BUILD_USER_CONFIG
./bjam --debug-config --build-dir=$BUILD_DIR toolset=gcc target-os=windows variant=release --prefix=$TARGET_DIR threadapi=win32 threading=multi link=static address-model=64 --layout=tagged --with-test --with-atomic --with-chrono --with-date_time --with-random --with-regex --with-coroutine --with-context --with-log --with-program_options --with-system --with-thread -j2 stage install
