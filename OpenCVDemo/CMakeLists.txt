cmake_minimum_required(VERSION 3.0.0)

project(opencvDemoLIB)
set( OpenCV_DIR "D:\\opencv\\opencv\\build")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

aux_source_directory(. DIR_LIB_SRCS)
add_library(opencvDemoLIB ${DIR_LIB_SRCS})
target_link_libraries( opencvDemoLIB ${OpenCV_LIBS} )