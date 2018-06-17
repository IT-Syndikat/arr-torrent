protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../common/commands.proto)

add_executable(arr-torrentd
	main.cpp
	command_server.cpp
	${PROTO_SRCS} ${PROTO_HDRS}
)

target_compile_definitions(arr-torrentd
	PRIVATE
	${LibtorrentRasterbar_DEFINITIONS}
)

target_include_directories(arr-torrentd
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/common
	${Boost_INCLUDE_DIRS}
	${LibtorrentRasterbar_INCLUDE_DIRS}
	${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(arr-torrentd
	${Boost_LIBRARIES}
	${LibtorrentRasterbar_LIBRARIES}
	${Protobuf_LIBRARIES}
)

install(TARGETS arr-torrentd RUNTIME DESTINATION bin)