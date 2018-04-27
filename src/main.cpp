#include <iostream>

#include <cstdlib>

#include <boost/make_shared.hpp>

#include <libtorrent/bencode.hpp>
#include <libtorrent/entry.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>

namespace lt = libtorrent;

void print_usage(const char *prog_name)
{
	std::cout << "usage: " << prog_name << " <torrent-file>\n"
	          << "version: " << ARR_TORRENT_VERSION << "\n";
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	auto settings = lt::default_settings();
	settings.set_str(lt::settings_pack::listen_interfaces, "0.0.0.0:6881");

	lt::error_code ec;

	lt::add_torrent_params params;
	params.save_path = "./";
	params.ti = boost::make_shared<lt::torrent_info>(argv[1], ec);
	if (ec) {
		std::cerr << ec.message() << "\n";
		return EXIT_FAILURE;
	}

	lt::session session(settings);
	session.add_torrent(params, ec);
	if (ec) {
		std::cerr << ec.message() << "\n";
		return EXIT_FAILURE;
	}

	// wait for the user to end
	std::getchar();

	return EXIT_SUCCESS;
}
