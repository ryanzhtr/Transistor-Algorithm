cmake_minimum_required(VERSION 3.28.3)
project(number_recognition)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/libtorch/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR /lib/x86_64-linux-gnu/cmake/opencv4)
find_package(OpenCV 4.6.0 REQUIRED)
find_package(Torch REQUIRED)

if(NOT Torch_FOUND)
    message(FATAL_ERROR "Torch not found")
endif()

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found")
endif()

# 打印OpenCV库信息，用于调试
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(train src/main.cpp)

# 使用target_link_libraries的现代方式
target_link_libraries(train 
    PRIVATE
    ${TORCH_LIBRARIES}
    ${OpenCV_LIBS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)