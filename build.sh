#/bin/bash

BUILD_DIR="build/"

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake .. && make
