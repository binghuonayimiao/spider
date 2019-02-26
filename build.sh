#!/bin/sh

cd build
cmake ..
make -j4
cd ../src
rm -rf CMakeFiles  cmake_install.cmake Makefile
cd ../redis
rm -rf CMakeFiles  cmake_install.cmake Makefile

