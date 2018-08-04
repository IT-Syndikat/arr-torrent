bin_PROGRAMS += arr-torrentd
arr_torrentd_SOURCES = \
	daemon/main.cpp \
	daemon/command_server.cpp

arr_torrentd_LDADD = \
	$(BOOST_ASIO_LIB) \
	$(libtorrent_LIBS)

arr_torrentd_CPPFLAGS = \
	$(BOOST_ASIO_CPPFLAGS) \
	$(libtorrent_CFLAGS)

arr_torrentd_LDFLAGS = \
	$(BOOST_ASIO_LDFLAGS)
