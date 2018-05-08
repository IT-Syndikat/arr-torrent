#include <iostream>
#include <string>

#include <cstdlib>

#include <boost/asio.hpp>

#include "commands.pb.h"

using protocol = boost::asio::local::stream_protocol;

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
		commands::Command cmd;
		cmd.mutable_quit();

		send(cmd);
	}

  private:
	void send(const commands::Command &cmd)
	{
		std::string msg_buffer;
		cmd.SerializeToString(&msg_buffer);

		auto msg_size = htonl(msg_buffer.size());

		m_socket.write_some(boost::asio::buffer(&msg_size, sizeof(msg_size)));
		m_socket.write_some(boost::asio::buffer(msg_buffer));
	}

	protocol::socket m_socket;
};

} // end namespace arr

void print_usage(const char *prog_name)
{
	std::cout << "usage: " << prog_name << " <command>\n"
	          << "command:\n"
	          << "    quit        send quit signal to daemon\n";
}

int main(int argc, char *argv[])
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

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

	google::protobuf::ShutdownProtobufLibrary();

	return EXIT_SUCCESS;
}
