#!/usr/bin/env bash

if [ "$1" = "" ]
then
    echo "ERROR: specify the build path as the first argument"
    echo "Exiting..."
    exit -1
else
    BUILD_PATH="$1"
fi

run-clang-tidy \
    -j 4 \
    -p $BUILD_PATH \
    -header-filter=^include/stuff/.* \
    tests \
    src
