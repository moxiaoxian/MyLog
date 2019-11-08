# cmake_minimum_required(VERSION <specify CMake version here>)
project(MyLog)

#头文件
include_directories(${PROJECT_SOURCE_DIR}/src/include)
#源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src/main dir_srcs)
#库文件
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)

add_executable(Test src/main/main.cpp src/sources/MyLog.cpp src/include/MyLog.h)