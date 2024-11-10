cmake_minimum_required(VERSION 3.5)
<<<<<<< HEAD
project(armor_detect)
=======
>>>>>>> a748d59 (detect)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 项目名称
project(light)

# 设置可执行文件和库输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 查找所需库
find_package(OpenCV REQUIRED)

# 查找 MvCameraControl 库
find_library(MVCAMERA_LIB MvCameraControl PATHS /opt/MVS/lib/64)

# 设置包含目录
include_directories(
    ${OpenCV_INCLUDE_DIRS}   # OpenCV头文件目录
    include                  # 项目中的自定义头文件目录
)

# 将 src 目录中的所有源文件添加到 SRC 变量中
aux_source_directory(src SRC)

# 创建可执行文件，名为 light
add_executable(light main.cpp ${SRC})

# 如果找到相机SDK库，将它链接到项目中
if (MVCAMERA_LIB)
    message(STATUS "Found MvCameraControl library: ${MVCAMERA_LIB}")
    target_link_libraries(light 
        ${OpenCV_LIBS}        # 链接 OpenCV
        ${MVCAMERA_LIB}       # 链接相机SDK库
    )
else()
    message(FATAL_ERROR "Could not find MvCameraControl library")
endif()

# 编译选项
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -flto -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-flto=auto")

# 添加库的路径以便链接时能找到相关依赖
link_directories(/opt/MVS/lib/64)
