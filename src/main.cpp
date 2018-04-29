#include <iostream>

#include <cstdlib>

#include <boost/asio.hpp>

#include <libtorrent/session.hpp>

#include "command_server.hpp"
#include "version.hpp"

using namespace boost::asio::ip;

namespace lt = libtorrent;

void print_usage(const char *prog_name)
{
	std::cout << "usage: " << prog_name << "\n"
	          << "version: " << ARR_TORRENT_VERSION << "\n";
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	lt::settings_pack settings;
	settings.set_str(lt::settings_pack::listen_interfaces, "0.0.0.0:6881");

	lt::session session(settings);

	// run command server
	try {
		boost::asio::io_service io_service;
		arr::server server(io_service, 1337);
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
