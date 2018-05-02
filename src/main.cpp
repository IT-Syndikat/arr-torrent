#include <iostream>

#include <cstdio>
#include <cstdlib>

#include <boost/asio.hpp>

#include <libtorrent/session.hpp>

#include "command_server.hpp"
#include "commands.pb.h"
#include "version.hpp"

using namespace boost::asio::ip;

namespace lt = libtorrent;

const auto UNIX_SOCKET_PATH = "/tmp/arr-torrent-cmd-srv.sock";

void print_usage(const char *prog_name)
{
	std::cout << "usage: " << prog_name << "\n"
	          << "version: " << ARR_TORRENT_VERSION << "\n";
}

int main(int argc, char *argv[])
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc > 1) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	{
		lt::settings_pack settings;
		settings.set_str(lt::settings_pack::listen_interfaces, "0.0.0.0:6881");

		lt::session session(settings);

		// run command server
		boost::asio::io_service io_service;
		std::remove(UNIX_SOCKET_PATH);
		arr::protocol::endpoint endpoint(UNIX_SOCKET_PATH);
		arr::server server(io_service, endpoint);
		server.wait_until_quit();
	}

	google::protobuf::ShutdownProtobufLibrary();

	return EXIT_SUCCESS;
}
