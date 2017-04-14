#!/bin/bash
BOOST_SRC_DIR=$1
if [ ! -d "$BOOST_SRC_DIR" ]; then
    echo "can't find source dir: $BOOST_SRC_DIR"
    exit 1
fi
ABS_BOOST_SRC_DIR=`realpath -e $BOOST_SRC_DIR`

TARGET_DIR=$PWD/../prefix_linux-x64
BUILD_DIR=$PWD/build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi

mkdir $BUILD_DIR

cd $BOOST_SRC_DIR
./bootstrap.sh --prefix=$TARGET_DIR --with-icu=$TARGET_DIR \
&& printf 'using gcc\n: icu\n: g++\n: <cxxflags>-DU_DISABLE_RENAMING\n;' > $ABS_BOOST_SRC_DIR/tools/build/src/user-config.jam \
&& LD_LIBRARY_PATH="$TARGET_DIR/lib:$LD_LIBRARY_PATH" ./bjam --build-dir=$BUILD_DIR toolset=gcc-icu link=static segmented-stacks=on target-os=linux variant=release --prefix=$TARGET_DIR include=$TARGET_DIR/include linkflags=-L$TARGET_DIR/lib threading=multi address-model=64 --layout=tagged --with-atomic --with-chrono --with-date_time --with-random --with-regex --with-coroutine --with-context --with-log --with-program_options --with-filesystem --with-system --with-thread -j2 stage install
