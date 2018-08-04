#include <config.h>

#include <iostream>
#include <string>

#include <cstdlib>

#include <boost/asio.hpp>
#include <json.hpp>

using protocol = boost::asio::local::stream_protocol;
using json = nlohmann::json;

const auto UNIX_SOCKET_PATH = "/tmp/arr-torrent-cmd-srv.sock";

namespace arr
{

class client
{
  public:
	client(boost::asio::io_service &io_service, protocol::endpoint endpoint)
	    : m_socket(io_service)
	{
		m_socket.connect(endpoint);
	}

	void send_quit()
	{
		send({ {"cmd", "quit"} });
	}

  private:
	void send(const json cmd)
	{
		auto msg = json::to_cbor(cmd);
		auto msg_size = htonl(msg.size());

		m_socket.write_some(boost::asio::buffer(&msg_size, sizeof(msg_size)));
		m_socket.write_some(boost::asio::buffer(msg));
	}

	protocol::socket m_socket;
};

} // end namespace arr

void print_usage(const char *prog_name)
{
	std::cout << "usage: " << prog_name << " <command>\n"
	          << "version: " << PACKAGE_VERSION << "\n"
	          << "command:\n"
	          << "    quit        send quit signal to daemon\n";
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	boost::asio::io_service io_service;
	protocol::endpoint endpoint(UNIX_SOCKET_PATH);
	arr::client client(io_service, endpoint);

	if (std::string(argv[1]) == "quit") {
		client.send_quit();
	} else {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
