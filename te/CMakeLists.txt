cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(armor_detect)

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 查找所需库
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)

# 查找 MvCameraControl 库
find_library(MVCAMERA_LIB MvCameraControl PATHS /opt/MVS/lib/64)

# 设置包含目录
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    include
)

# 添加源文件
aux_source_directory(src SRC)

# 创建可执行文件
add_executable(armor_detect main.cpp ${SRC})

# 链接库
if (MVCAMERA_LIB)
    target_link_libraries(armor_detect 
        PRIVATE
        ${OpenCV_LIBS}
        ${MVCAMERA_LIB}
        Eigen3::Eigen
        pthread
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

# 添加库搜索路径
link_directories(/opt/MVS/lib/64)