cmake_minimum_required(VERSION 3.5)
project(arr-torrent VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(defaults)

add_definitions(-DARR_TORRENT_VERSION="${PROJECT_VERSION}")

find_package(Boost REQUIRED)
find_package(LibtorrentRasterbar REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/commands.proto)

add_executable(arr
	src/main.cpp
	src/command_server.cpp
	${PROTO_SRCS} ${PROTO_HDRS}
)

target_compile_definitions(arr
	PRIVATE
	${LibtorrentRasterbar_DEFINITIONS}
)

target_include_directories(arr
	PRIVATE
	${PROJECT_BINARY_DIR}
	${Boost_INCLUDE_DIRS}
	${LibtorrentRasterbar_INCLUDE_DIRS}
	${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(arr
	${Boost_LIBRARIES}
	${LibtorrentRasterbar_LIBRARIES}
	${Protobuf_LIBRARIES}
)

add_subdirectory(client)
