cmake_minimum_required(VERSION 3.28.0)
project(DllBtree VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_GENERATOR "MinGW Makefiles")
set(PNAME "DllBtree")

#定义各种路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#生成可执行文件
add_executable(${PNAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

#生成动态链接库
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*)
# 遍历所有子目录
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/${SUBDIR})
        # 获取子目录中的源代码文件
        file(GLOB LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/${SUBDIR}/*.cpp)
        # 生成动态库
        add_library(${SUBDIR} SHARED ${LIB_SOURCES})
        #头文件查找目录
        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/${SUBDIR})
        # 将动态库链接到可执行文件
        target_link_libraries(${PNAME} PRIVATE ${SUBDIR})
    endif()
endforeach()