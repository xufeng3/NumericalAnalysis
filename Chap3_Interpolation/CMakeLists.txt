cmake_minimum_required(VERSION 3.21)
project(cm3)

set(CMAKE_CXX_STANDARD 14)

add_executable(cm3 poly.h main.cpp test3.h interpolation.h)

##指定库路径
#file(GLOB_RECURSE PYTHON2.7_LIB "/usr/lib/python2.7/config-x86_64-linux-gnu/*.so")
##指定头文件路径
#set(PYTHON2.7_INLCUDE_DIRS "/usr/include/python2.7")
##添加头文件到工程
#include_directories(include
#        ${PYTHON2.7_INLCUDE_DIRS}
#        )
##这样配置可以使得matplotlib.h中找到python.h文件，通常这样设置就可以。
#add_executable(ProjectName ${DIRS_SRCS})
##添加库文件到工程
#target_link_libraries(ProjectName ${PYTHON2.7_LIB})