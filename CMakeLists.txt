cmake_minimum_required(VERSION 3.5)
project(arr-torrent LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMake Build Type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED)
find_package(LibtorrentRasterbar REQUIRED)

add_executable(arr src/main.cpp)
target_compile_definitions(arr PRIVATE ${LibtorrentRasterbar_DEFINITIONS})
target_include_directories(arr PRIVATE ${Boost_INCLUDE_DIRS} ${LibtorrentRasterbar_INCLUDE_DIRS})
target_link_libraries(arr ${Boost_LIBRARIES} ${LibtorrentRasterbar_LIBRARIES})
