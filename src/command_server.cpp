#include "command_server.hpp"

#include <iostream>
#include <utility>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "commands.pb.h"

using namespace boost::asio;

namespace arr
{

const std::size_t MAX_MESSAGE_SIZE = 4096;

session::session(protocol::socket socket, server &server)
    : m_socket(std::move(socket)), m_server(server)
{
}

void session::start()
{
	read_msg_size();
}

void session::read_msg_size()
{
	auto self(shared_from_this());

	auto cb = [this, self](boost::system::error_code ec, std::size_t length) {
		if (ec || length != sizeof(m_msg_size)) {
			std::cerr << "Error: Unable to read message size\n";
			return;
		}

		m_msg_size = ntohl(m_msg_size);

		if (m_msg_size > MAX_MESSAGE_SIZE) {
			std::cerr << "Error: Message exceeds " << MAX_MESSAGE_SIZE << "\n";
			return;
		}

		m_msg_buffer.resize(m_msg_size);

		read_msg();
	};

	m_socket.async_read_some(buffer(&m_msg_size, sizeof(m_msg_size)), cb);
}

void session::read_msg()
{
	auto self(shared_from_this());

	auto cb = [this, self](boost::system::error_code ec, std::size_t length) {
		if (ec || length != m_msg_buffer.size()) {
			std::cerr << "Error: Unable to read message\n";
			return;
		}

		// decode received message
		commands::Command cmd;
		{
			using namespace boost::iostreams;
			stream<array_source> bs(m_msg_buffer.data(), m_msg_buffer.size());
			if (!cmd.ParseFromIstream(&bs)) {
				std::cerr << "Error: Failed to parse command\n";
				return;
			}
		}

		// handle it
		if (cmd.has_quit()) {
			std::cout << "Quit received\n";
			m_server.quit();
		} else {
			std::cerr << "Error: Unhandled command\n";
		}

		// next
		read_msg_size();
	};

	m_socket.async_read_some(buffer(m_msg_buffer), cb);
}

server::server(io_service &io_service, protocol::endpoint endpoint)
    : m_socket(io_service), m_acceptor(io_service, endpoint)
{
	accept();
}

void server::quit()
{
	m_socket.get_io_service().stop();
}

void server::wait_until_quit()
{
	m_socket.get_io_service().run();
}

void server::accept()
{
	auto cb = [this](boost::system::error_code ec) {
		if (!ec) {
			std::make_shared<session>(std::move(m_socket), *this)->start();
		}

		accept();
	};

	m_acceptor.async_accept(m_socket, cb);
}

} // end namespace arr
