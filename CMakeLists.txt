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

# 添加第三方的库
set(INC_DIR /usr/local/include/)
set(LINK_DIR /usr/local/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(hiredis)
link_libraries(json_linux-gcc-4.9.3_libmt)



# 指定生成目标
add_executable(app ${DIR_SRCS})

# 将第三方的库链接到可执行文件
target_link_libraries(app hiredis)
target_link_libraries(app json_linux-gcc-4.9.3_libmt.a)
