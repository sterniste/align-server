#!/bin/bash
BOOST_SRC_DIR=$1
if [ ! -d "$BOOST_SRC_DIR" ]; then
    echo "can't find source dir: $BOOST_SRC_DIR"
    exit 1
fi
ABS_BOOST_SRC_DIR=`realpath -e $BOOST_SRC_DIR`

TARGET_DIR=$PWD/../prefix_w64-mingw32
BUILD_DIR=$PWD/build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi
mkdir $BUILD_DIR

cd $BOOST_SRC_DIR
./bootstrap.sh --prefix=$TARGET_DIR --with-icu=$TARGET_DIR \
&& printf 'using gcc\n: icu\n: x86_64-w64-mingw32-g++.exe\n: <cxxflags>-DU_DISABLE_RENAMING\n;' > $ABS_BOOST_SRC_DIR/tools/build/src/user-config.jam \
&& ./bjam --build-dir=$BUILD_DIR toolset=gcc-icu link=static segmented-stacks=on target-os=windows variant=release threadapi=win32 threading=multi address-model=64 --prefix=$TARGET_DIR --layout=tagged --with-atomic --with-chrono --with-date_time --with-random --with-regex --with-coroutine --with-context --with-log --with-program_options --with-filesystem --with-system --with-thread -j2 stage install

(cd $TARGET_DIR/lib; ln -s libboost_thread_win32-mt.a libboost_thread-mt.a)
