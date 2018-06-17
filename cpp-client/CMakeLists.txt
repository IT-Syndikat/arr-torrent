protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../common/commands.proto)

add_executable(arr-torrent
	main.cpp
	${PROTO_SRCS} ${PROTO_HDRS}
)

target_include_directories(arr-torrent
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/common
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(arr-torrent
	PRIVATE
	${Boost_LIBRARIES}
	${Protobuf_LIBRARIES}
)

install(TARGETS arr-torrent RUNTIME DESTINATION bin)