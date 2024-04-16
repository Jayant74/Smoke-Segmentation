cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(showImage VERSION 1.0)

find_package( OpenCV REQUIRED )
find_package(Armadillo REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${Armadillo_INCLUDE_DIRS})

add_library(QuadTree STATIC Blocker/QuadTree.cpp)
add_library(GaussCompute STATIC GaussToolKit/GaussCompute.cpp)

add_executable(showImage main.cpp)
target_link_libraries(showImage ${OpenCV_LIBS} QuadTree GaussCompute) # Excluding GaussCompute
target_include_directories(QuadTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Blocker/include)
target_include_directories(GaussCompute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GaussToolKit/include)
