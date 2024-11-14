cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(armor_detect)

# 设置可执行文件和库输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 查找所需库
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)  # 添加对pthread的支持

# 查找 MvCameraControl 库
find_library(MVCAMERA_LIB MvCameraControl PATHS /opt/MVS/lib/64)

# 设置包含目录
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    /opt/MVS/include            # 添加相机SDK的头文件目录
)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# 创建可执行文件
add_executable(armor_detect 
    main.cpp 
    ${SOURCES}
)

# 链接库
target_link_libraries(armor_detect 
    ${OpenCV_LIBS}
    ${MVCAMERA_LIB}
    Eigen3::Eigen
    pthread                     # 添加pthread库
)

# 编译选项
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -flto -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-flto=auto")

# 添加库的路径
link_directories(/opt/MVS/lib/64)

# 设置安装规则
install(TARGETS armor_detect
    RUNTIME DESTINATION bin
)