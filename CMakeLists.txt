project(base16-builder)
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -std=c++1y")

find_package(Boost REQUIRED COMPONENTS filesystem system)

include_directories(
  ${libgit2_SOURCE_DIR}/include
  ${mstch_INCLUDE_DIR})

add_subdirectory(vendor/libgit2)
add_subdirectory(vendor/mstch)

add_executable(${CMAKE_PROJECT_NAME} src/base16_builder.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} git2 mstch)

