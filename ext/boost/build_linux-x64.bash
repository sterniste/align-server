#!/bin/bash
BOOST_SRC_DIR=$1
if [ ! -d "$BOOST_SRC_DIR" ]; then
    echo "can't find source dir: $BOOST_SRC_DIR"
    exit 1
fi

export TARGET_DIR=$PWD/../prefix_linux-x64
export BUILD_DIR=$PWD/build
if [ -d $BUILD_DIR ]; then
   rm -rf $BUILD_DIR
fi

mkdir $BUILD_DIR

cd $BOOST_SRC_DIR
./bootstrap.sh --prefix=$TARGET_DIR --without-icu
LD_LIBRARY_PATH="$TARGET_DIR/lib:$LD_LIBRARY_PATH" ./bjam --debug-config --build-dir=$BUILD_DIR toolset=gcc segmented-stacks=on target-os=linux variant=release --prefix=$TARGET_DIR include=$TARGET_DIR/include linkflags=-L$TARGET_DIR/lib threading=multi link=shared address-model=64 --layout=tagged --with-log --with-program_options --with-filesystem --with-system --with-random --with-regex --with-date_time --with-chrono --with-atomic --with-thread -j2 stage install
