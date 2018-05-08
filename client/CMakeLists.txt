add_executable(arr-client
	main.cpp
	${PROTO_SRCS} ${PROTO_HDRS}
)

target_include_directories(arr-client
	PRIVATE
	${Boost_INCLUDE_DIRS}
	${PROJECT_BINARY_DIR}
)

target_link_libraries(arr-client
	PRIVATE
	${Boost_LIBRARIES}
	${Protobuf_LIBRARIES}
)
