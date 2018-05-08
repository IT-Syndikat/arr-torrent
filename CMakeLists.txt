cmake_minimum_required(VERSION 3.5)
project(arr-torrent VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(defaults)

add_definitions(-DARR_TORRENT_VERSION="${PROJECT_VERSION}")

find_package(Boost REQUIRED)
find_package(LibtorrentRasterbar REQUIRED)
find_package(Protobuf REQUIRED)

add_subdirectory(client)
add_subdirectory(daemon)
