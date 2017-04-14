#!/bin/bash

if [ $# -gt 1 -o \( $# -eq 1 -a "$1" != "linux-x64" -a "$1" != "w64-mingw32" \) ]; then
    echo "usage: $0 linux-x64"
    echo "or   : $0 w64-mingw32"
    exit 1
fi
if [ $# -eq 0 ]; then
    if [[ "$(uname -s)" =~ ^CYGWIN* ]]; then
        PREFIX=w64-mingw32
    else
        PREFIX=linux-x64
    fi
else
    PREFIX=$1
    shift
fi

rm -rf prefix_$PREFIX

#icu4c
rm -rf icu4c
git checkout icu4c
pushd icu4c
curl -L http://download.icu-project.org/files/icu4c/58.2/icu4c-58_2-src.tgz | tar xzf -
echo building icu4c ...
time ./build_$PREFIX.bash icu > build.log 2>&1 build.log
echo icu4c built "(logs in $PWD/build.log)"
popd

#boost
rm -rf boost
git checkout boost
pushd boost
curl -L https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2/download -o boost_1_63_0.tbz && tar xjf boost_1_63_0.tbz
echo building boost ...
time ./build_$PREFIX.bash boost_1_63_0 > build.log 2>&1 build.log
echo boost built "(logs in $PWD/build.log)"
popd

#openssl
rm -rf openssl
git checkout openssl
pushd openssl
curl -L https://www.openssl.org/source/openssl-1.1.0e.tar.gz | tar xzf -
echo building openssl ...
time ./build_$PREFIX.bash openssl-1.1.0e > build.log 2>&1 build.log
echo openssl built "(logs in $PWD/build.log)"
popd

#json
rm -rf json
git checkout json
pushd json
git clone https://github.com/nlohmann/json.git
echo building json ...
time ./build_$PREFIX.bash json > build.log 2>&1 build.log
echo json built "(logs in $PWD/build.log)"
popd

#cpp-netlib
rm -rf cpp-netlib
git checkout cpp-netlib
pushd cpp-netlib
git clone https://github.com/cpp-netlib/cpp-netlib.git -b 0.13-release
echo building cpp-netlib ...
time ./build_$PREFIX.bash cpp-netlib > build.log 2>&1 build.log
echo cpp-netlib built "(logs in $PWD/build.log)"
popd
