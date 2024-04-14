cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(QuadTree VERSION 1.0)

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(QuadTree SHARED QuadTree.cpp)
target_include_directories(QuadTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(QuadTree ${OpenCV_LIBS})