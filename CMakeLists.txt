cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(showImage VERSION 1.0)
set(GSL_ROOT_DIR "/usr/local/lib/")

find_package( OpenCV REQUIRED )
find_package( GSL REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(QuadTree SHARED Blocker/QuadTree.cpp)
add_library(GaussCompute SHARED GaussToolKit/GaussCompute.cpp)

add_executable(showImage main.cpp)
target_link_libraries(showImage ${OpenCV_LIBS} QuadTree ) # Excluding GaussCompute
target_include_directories(QuadTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Blocker/include)
target_include_directories(GaussCompute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GaussToolKit/include)
set_target_properties(showImage PROPERTIES INSTALL_RPATH "/usr/local/lib/lib")

message(STATUS "GSL found: ${GSL_FOUND}")
message(STATUS "GSL LIB LOCATION:" "${GSL_LIBRARY}")
message(STATUS "GSL LIB LOCATION:" "${GSL_INCLUDE_DIRS}/gsl")
