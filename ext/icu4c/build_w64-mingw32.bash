#!/bin/bash
ICU4C_SRC_DIR=$1
if [ ! -d "$ICU4C_SRC_DIR" -o ! -d "$ICU4C_SRC_DIR"/source ]; then
    echo "can't find release dir: $ICU4C_SRC_DIR"
    exit 1
fi
ABS_ICU_CONFIG_PATCH=$PWD/icu-config.patch

TARGET_DIR=$PWD/../prefix_w64-mingw32

cd $ICU4C_SRC_DIR/source
CC=/usr/bin/x86_64-w64-mingw32-gcc CXX=/usr/bin/x86_64-w64-mingw32-g++ ./configure --prefix=$TARGET_DIR --disable-renaming --disable-shared --enable-static --disable-strict --disable-threads --disable-samples --disable-tests \
&& sed -i -e '/$(LINK.cc)/s/$/ \/cygdrive\/c\/Windows\/System32\/msvcr100.dll/' tools/*/Makefile extra/*/Makefile \
&& sed -i -e '/ -s $(CURDIR)\/out\/build\/$(ICUDATA_PLATFORM_NAME)/s// -s `cygpath -w $(CURDIR)\/out\/build\/$(ICUDATA_PLATFORM_NAME)`/' data/Makefile \
&& make install LDFLAGS="-static-libstdc++ -static-libgcc -static" \
&& (cd $TARGET_DIR/bin; patch -p1) < $ABS_ICU_CONFIG_PATCH \
&& (cd $TARGET_DIR/lib; ln -s libsicuuc.a libicuuc.a; ln -s libsicudata.a libicudata.a; ln -s libsicui18n.a libicui18n.a)

