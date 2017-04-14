#!/bin/bash
ICU4C_SRC_DIR=$1
if [ ! -d "$ICU4C_SRC_DIR" -o ! -d "$ICU4C_SRC_DIR"/source ]; then
    echo "can't find release dir: $ICU4C_SRC_DIR"
    exit 1
fi

TARGET_DIR=$PWD/../prefix_linux-x64

# disable-shared causes boost build to fail has_icu!

cd $ICU4C_SRC_DIR/source
./configure --prefix=$TARGET_DIR --disable-renaming --enable-static --disable-samples --disable-tests \
&& make install
