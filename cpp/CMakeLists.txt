cmake_minimum_required(VERSION 3.20.0)

project(milvus-storage VERSION 0.1.0)

option(WITH_UT "Build the testing tree." ON)
option(WITH_ASAN "Build with address sanitizer." OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED)
find_package(Arrow REQUIRED)
find_package(protobuf REQUIRED)
find_package(glog REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.cc)
message(STATUS "SRC_FILES: ${SRC_FILES}")
add_library(milvus-storage ${SRC_FILES})
target_include_directories(milvus-storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/milvus-storage ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(milvus-storage PUBLIC arrow::libarrow arrow::libparquet Boost::boost protobuf::protobuf)
target_link_libraries(milvus-storage PUBLIC glog::glog)

if (WITH_UT)
  enable_testing()
  add_subdirectory(test)
endif()
