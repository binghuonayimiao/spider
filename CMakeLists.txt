# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (Spider)

# 支持c++11编译
SET(CMAKE_C_COMPILER "/usr/local/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
add_definitions(-std=c++11)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(app ${DIR_SRCS})
