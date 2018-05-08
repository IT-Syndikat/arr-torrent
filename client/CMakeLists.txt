protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../common/commands.proto)

add_executable(arr-client
	main.cpp
	${PROTO_SRCS} ${PROTO_HDRS}
)

target_include_directories(arr-client
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/common
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(arr-client
	PRIVATE
	${Boost_LIBRARIES}
	${Protobuf_LIBRARIES}
)
