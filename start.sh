#!/bin/sh

cmake .
make
rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake Makefile 
