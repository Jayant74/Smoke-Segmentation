cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GaussCompute VERSION 1.0)

set(GCC_COMPILE_OPTIONS "-lgslcblas -lm -lgsl")
set(GSL_ROOT_DIR "/usr/local/lib/")

find_package( OpenCV REQUIRED )
find_package( GSL REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GSL_INCLUDE_DIR}/gsl)

add_library(GaussCompute STATIC GaussCompute.cpp)
target_include_directories(GaussCompute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(GaussCompute PUBLIC ${OpenCV_LIBS} ${GSL_LIBRARIES})
set_target_properties(GaussCompute PROPERTIES INSTALL_RPATH "/usr/local/lib/lib")
target_compile_options(GaussCompute PUBLIC "${GCC_COMPILE_OPTIONS}")

message(STATUS "GSL found: ${GSL_FOUND}")
message(STATUS "GSL LIB LOCATION:" "${GSL_LIBRARY}")
message(STATUS "GSL LIB LOCATION:" "${GSL_INCLUDE_DIRS}/gsl")
# "/usr/local/lib/lib/libgsl.so" "/usr/local/lib/lib/libgslcblas.so"